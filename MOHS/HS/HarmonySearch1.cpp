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

#include "HS/HarmonySearch1.h"
#include <cstdlib>
#include <cstdio>

HarmonySearch1::HarmonySearch1(Problem *problem, HS_Params *hsParams,
	MemoryBuilder *memoryBuilder, MemoryInit *memoryInit, MemoryConsideration *memoryConsideration,
        PitchAdjustment *pitchAdjustment, MemoryUpdate *memoryUpdate,
        ParetoRanking *paretoRanking, bool calculateAndPrintMetrics, bool doSampling,
	bool truncateParetoSet) : HarmonySearch(problem, hsParams, memoryBuilder, memoryInit, 
        memoryConsideration, pitchAdjustment, memoryUpdate, paretoRanking,
        calculateAndPrintMetrics, doSampling) {
    
    this->truncateParetoSet = truncateParetoSet;
}

HarmonySearch1::~HarmonySearch1() {
    
}

void HarmonySearch1::run() {
    /* Random number generator */
    Random *random = new Random();

    /* Program total timer */
    Timer *totalTimer = new Timer();

    /* Algorithm global timer */
    Timer *globalTimer = new Timer();

    /* Iterations timer */
    Timer *iterTimer = new Timer();

    /* File where samples are written */
    FILE *samplingOutput;

    /* Gets date/time of execution */
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

    /* Compute ranking of memory solutions */
    paretoRanking->rank(mainMemory);

    /* Pareto set initialization */
    initParetoSet();

    if (hsParams->getDebug()) {
        mainMemory->print(stdout, true, true);
        fprintf(stdout, "--------------\n");
        paretoSet->print(stdout, true, true);
        fprintf(stdout, "--------------\n");
    }

    /* Pareto set maximun solutions */
    int maxPareto = paretoSet->getSize();

    /* Iterations counter */
    int cycles = 0;
    int iterations = 0;
    int truncates  = 0;

    /* Timers */
    totalTimer->start();
    globalTimer->start();
    iterTimer->start();

    /* Main loop */
    printf("Improvisation begins...\n");
    while (cycles < hsParams->getCycles()) {
        while (!stoppingCondition(cycles + 1, iterations, iterTimer)) {

            /* Build new solution */
            Solution *xNew = buildSolution(random);

            /* Evaluate solution */
            problem->evaluate(xNew);

            /* Compute ranking for new solution */
            paretoRanking->rank(mainMemory, xNew);

            /* Update memory */
            memoryUpdate->update(problem, mainMemory, xNew);

            /* Memory ranking re-computation */
            //paretoRanking->rank(mainMemory); // It is not necessary

            /* Update Pareto set */
            Solution *p = xNew->clone(problem->getVariableBuilder());
            paretoSet->nonDominatedAdd(p);

            /* Truncate Pareto set, if it exceeds limit */
            if (truncateParetoSet) {
                if (paretoSet->getSize() > hsParams->getParetoSetMaxGrowth()) {
                    paretoSet->truncate(hsParams->getParetoSetMaxSize());
                    ++truncates;
                }
            }

            if (hsParams->getDebug()) {
                xNew->print(stdout, true);
                fprintf(stdout, "--------------\n");
            }
            delete xNew;
            ++iterations;

            /* Calculate maximun number of Pareto solutions */
            if (paretoSet->getSize() > maxPareto)
                maxPareto = paretoSet->getSize();
        }

        /* Sampling */
        sampling(paretoSet, iterations, globalTimer, samplingOutput);

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

    /* Truncate Pareto set */
    if (truncateParetoSet) {
        paretoSet->truncate(hsParams->getParetoSetMaxSize());
        ++truncates;

        fprintf(stdout, "Truncates %d...\n", truncates);
    }

    /* Calculate metrics */
    metrics_t metrics;
    if (calculateAndPrintMetrics) {
        printf("Calculating metrics...\n");
        calculateMetrics(&metrics, paretoSet);
    }

    /* Print results */
    printf("Printing results...\n");
    printResults(totalTimer, globalTimer, iterations, maxPareto, &metrics);

    delete random;
    delete totalTimer;
    delete globalTimer;
    delete iterTimer;
}

const char *HarmonySearch1::getName() {
    return "HarmonySearch1";
}
