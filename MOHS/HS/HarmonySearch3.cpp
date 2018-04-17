/*  This file is part of mohs.

    Copyright (C) 2011 Germán Hüttemann <ghuttemann@gmail.com>
    Copyright (C) 2011 Juan Ricart <juangabriel.ricart@gmail.com>

    mohs is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    mohs is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with mohs.  If not, see <http://www.gnu.org/licenses/>. */

#include "HS/HarmonySearch3.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cassert>

HarmonySearch3::HarmonySearch3(Problem *problem, HS_Params *hsParams, MemoryBuilder *memoryBuilder,
        MemoryInit *memoryInit, MemoryConsideration *memoryConsideration,
        PitchAdjustment *pitchAdjustment, MemoryUpdate *memoryUpdate,
        ParetoRanking *paretoRanking, bool calculateAndPrintMetrics, bool doSampling) :
        HarmonySearch(problem, hsParams, memoryBuilder, memoryInit,
        memoryConsideration, pitchAdjustment, memoryUpdate, paretoRanking,
        calculateAndPrintMetrics, doSampling) {
    
}

HarmonySearch3::~HarmonySearch3() {
    
}

void HarmonySearch3::run() {
    /* Random number generator */
    Random *random = new Random();

    /* Program total timer */
    Timer *totalTimer = new Timer();

    /* Algorithm global timer */
    Timer *globalTimer = new Timer();

    /* Iterations timer */
    Timer *iterTimer = new Timer();

    /* File where the samples are written */
    FILE *samplingOutput;

    /* Get date/time of execution */
    getDate(this->date);

    if (doSampling) {
        char buffer[50];

        sprintf(buffer, "sampling%s.txt", date);
        if ((samplingOutput = fopen(buffer, "w")) == NULL) {
            fprintf(stderr, "Error opening file '%s' in write mode", buffer);
            exit(EXIT_FAILURE);
        }
    }

    /* Print algorithm and problem */
    printf("%s(%s)\n", this->getName(), problem->getName());

    /* Memory initialization */
    printf("Initializing...\n");
    memoryInit->initialize(mainMemory, problem, random);

    /* Ranking computation of memory solutions */
    paretoRanking->rank(mainMemory);

    if (hsParams->getDebug()) {
        mainMemory->print(stdout, true, true);
        fprintf(stdout, "--------------\n");
    }

    /* Complementary memories */
    Memory *mergedMemory = memoryBuilder->createMemory(hsParams->getHMS() +
						       hsParams->getTmpHMS(), problem);
    Memory *tmpMemory = memoryBuilder->createMemory(hsParams->getTmpHMS(), problem);

    /* Iterations counter */
    int cycles = 0;
    int iterations = 0;

    /* Timers */
    totalTimer->start();
    globalTimer->start();
    iterTimer->start();

    /* Main loop */
    printf("Improvisation begins...\n");
    while (cycles < hsParams->getCycles()) {
        while (!stoppingCondition(cycles + 1, iterations, iterTimer)) {

            /* Generate HMS solutions for temporal memory */
            for (int i=0; i < tmpMemory->getSize(); i++) {
                /* Build new solution */
                Solution *xNew = buildSolution(random);

                /* Evaluate solution */
                problem->evaluate(xNew);

                /* Add solution to temporal memory */
                tmpMemory->setSolution(i, xNew);

                if (hsParams->getDebug()) {
                    xNew->print(stdout, true);
                    fprintf(stdout, "--------------\n");
                }
            }

            /* Join both memories */
            mergeMemories(mainMemory, tmpMemory, mergedMemory);

            /* Ranking computation of new memory */
            paretoRanking->rank(mergedMemory);

            /* Maintains better solutions in main memory */
            getBestSolutions(mergedMemory, mainMemory);

            /* Ranking re-computation of memory */
            //paretoRanking->rank(mainMemory); -- It is not necessary

            ++iterations;
        }

        /* Sampling */
        sampling(mainMemory, iterations, globalTimer, samplingOutput);

        /* Increment cycles */
        ++cycles;

        /* Sampling timer reset */
        iterTimer->start();
    }

    /* Get finalization time */
    globalTimer->split();
    printf("Improvisation finishes...\n");

    if (doSampling) {
        fclose(samplingOutput);
    }

    /* Get non-dominated solutions out of memory */
    printf("Getting optimal solutions...\n");
    delete paretoSet;
    paretoSet = new ParetoSet();
    copyMemoryToParetoSet();

    /* Metrics computation */
    metrics_t metrics;
    if (calculateAndPrintMetrics) {
        printf("Calculating metrics...\n");
        calculateMetrics(&metrics, paretoSet);
    }

    /* Printing results */
    printf("Printing results...\n");
    printResults(totalTimer, globalTimer, iterations, paretoSet->getSize(), &metrics);
    
    delete random;
    delete totalTimer;
    delete globalTimer;
    delete iterTimer;
    delete tmpMemory;
    delete mergedMemory;
}

void HarmonySearch3::mergeMemories(Memory *inMemory1, Memory *inMemory2,
        Memory *outMemory) {
    
    int k = 0;
    
    for (int i=0; i < inMemory1->getSize(); i++)
        outMemory->setSolution(k++, inMemory1->detach(i));
    
    for (int i=0; i < inMemory2->getSize(); i++)
        outMemory->setSolution(k++, inMemory2->detach(i));
}

int solCmp(const void *a, const void *b) {
    Solution *s1 = *((Solution **) a);
    Solution *s2 = *((Solution **) b);

    switch (s1->compare(s2)) {
        case WORSE: return 1;
        case EQUAL: return 0;
        case BETTER: return -1;
    }
}

void HarmonySearch3::getBestSolutions(Memory *inMemory, Memory *outMemory) {
    /* Complete memory size */
    int solArraySize = inMemory->getSize();

    /* Build solution array, moving from complete memory */
    Solution **solArray = new Solution*[solArraySize];
    for (int i=0; i < solArraySize; i++)
        solArray[i] = inMemory->detach(i);

    /* Sort solutions */
    qsort(solArray, solArraySize, sizeof(Solution *), solCmp);

    /* Out-memory cannot be greater than in-memory */
    assert(outMemory->getSize() <= inMemory->getSize());

    /* Number of solutions to be process so far */
    int remainingSolutions = outMemory->getSize();

    /* Main process */
    int i = 0;
    while (remainingSolutions > 0) {
        /* Currently processed ranking */
        int ranking = solArray[i]->getRanking();

        /* Find solutions with same ranking */
        int j = i + 1;
        while (j < solArraySize && solArray[j]->getRanking() == ranking)
            j = j + 1;

        /* Compute number of solutions with same ranking */
        int total = j - i;

        if (total <= remainingSolutions) {
            /* Move first "total" solutions to new memory */
            for (int k=i; k < j; k++) {
                outMemory->setSolution(k, solArray[k]);
                solArray[k] = NULL;
            }

            /* Update counter and index */
            remainingSolutions = remainingSolutions - total;
            i = j;
        }
        else {
            /*
             * Move "remainingSolutions" solutions to new memory...
             */
            ParetoSet *tmpSet = new ParetoSet();
            for (int k=i; k < j; k++) {
                tmpSet->add(solArray[k]);
                solArray[k] = NULL;
            }

            /*
             * ...filtering through niching operator
             */
            tmpSet->truncate(remainingSolutions);
            
            /*
             * Begin iteration through solutions
             */
            tmpSet->begin();
            for (int k=i; tmpSet->hasNext(); k++)
                outMemory->setSolution(k, (Solution *) tmpSet->getNext());
            tmpSet->detachPoints();
            delete tmpSet;

            break;
        }
    }

    /* Remove remaining solutions */
    for (int k=0; k < solArraySize; k++)
        delete solArray[k];
    delete[] solArray;

    /* "outMemory" is already ranked */
}

const char *HarmonySearch3::getName() {
    return "HarmonySearch3";
}
