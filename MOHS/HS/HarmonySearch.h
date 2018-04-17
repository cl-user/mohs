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

#ifndef HARMONYSEARCH_H
#define	HARMONYSEARCH_H

#include "Problem/Problem.h"
#include "HS/HS_Params.h"
#include "HS_Structures/Solution.h"
#include "Utils/Random.h"
#include "HS_Structures/Memory/Memory.h"
#include "Utils/Timer.h"
#include "HS_Structures/Pareto/ParetoSet.h"
#include "HS_Operators/PitchAdjustment/PitchAdjustment.h"
#include "HS_Operators/MemoryConsideration/MemoryConsideration.h"
#include "HS_Operators/MemoryUpdate/MemoryUpdate.h"
#include "HS_Operators/ParetoRanking/ParetoRanking.h"
#include "HS_Structures/Memory/MemoryBuilder/MemoryBuilder.h"
#include "HS_Operators/MemoryInit/MemoryInit.h"
#include "HS_Structures/NonDominatedSet.h"

#include <list>
using namespace std;

class HarmonySearch {
protected:
    /* Problem to be solved */
    Problem *problem;

    /* Algorithm set-up */
    HS_Params *hsParams;

    /* Memory builder algorithm */
    MemoryBuilder *memoryBuilder;

    /* Memory initialization algorithm */
    MemoryInit *memoryInit;

    /* Memory update algorithm */
    MemoryUpdate *memoryUpdate;

    /* Memory consideration algoritm */
    MemoryConsideration *memoryConsideration;
    
    /* Pitch Adjustment algorithm */
    PitchAdjustment *pitchAdjustment;

    /* Pareto ranking computation algorithm */
    ParetoRanking *paretoRanking;

    /* Algorithm Pareto set */
    ParetoSet *paretoSet;

    /* Algorithm Memory */
    Memory *mainMemory;

    /* Problem optimal Front */
    ParetoSet *yTrue;

    /* Metrics computation set-up */
    bool calculateAndPrintMetrics;

    /* Sampling performing set-up */
    bool doSampling;

    /* Date/time of execution */
    char date[20];

    /* Builds a new solution performing improvisation  */
    Solution *buildSolution(Random *random);

    /* Checks stopping criteria */
    bool stoppingCondition(int cycle, int iterations, Timer *timer);

    /* Checks interval condition */
    bool intervalCondition(int iterations, Timer *timer);

    /* Random selection */
    Variable *randomSelection(int variable, Random *random);

    /* 
     * Get an alphanumeric representation of current
     * date, in YYYY.MM.DD.HH24.MI.SS format.
     * The buffer passed as parameter must have at
     * least a size of 20 characters.
     */
    void getDate(char *buffer);

    /* Datatype for metrics */
    typedef struct {
        double absM1;   // Distance between calculated and optimal Pareto fronts
        double absM2;   // Distribution of calculated Pareto front
        double absM3;   // Extension of calculated Pareto front
        double normM1;  // Normalized M1
        double normM2;  // Normalized M2
        double normM3;  // Normalized M3
        double error;   // Percentage of solutions of calculated front that are not in optimal front
        double igd;     // Inverted Generational Distance (inverted M1)
        int solutions;  // Number of solutions of calculated Pareto front
    } metrics_t;

    void calculateMetrics(metrics_t *metrics, ParetoSet *yTrue);

    /* Sampling */
    void sampling(NonDominatedSet *points, int iterations,
        Timer *globalTimer, FILE *samplingOutput);

    /* Sampling print */
    void printSampling(NonDominatedSet *points, int iterations,
        Timer *globalTimer, FILE *samplingOutput);

    /* Prints the results */
    void printResults(Timer *totalTimer, Timer *globalTimer, int iterations,
        int maxPareto, metrics_t *metrics);

    /* Pareto set initialization */
    void initParetoSet();

    /*
     * Copies all memory solutions to Pareto set,
     * removing non-dominated ones.
     */
    void copyMemoryToParetoSet();

public:
    /** Constructor. */
    HarmonySearch(Problem *problem, HS_Params *hsParams, MemoryBuilder *memoryBuilder,
            MemoryInit *memoryInit, MemoryConsideration *memoryConsideration,
            PitchAdjustment *pitchAdjustment, MemoryUpdate *memoryUpdate,
            ParetoRanking *paretoRanking, bool calculateAndPrintMetrics, bool doSampling);

    /** Destructor. */
    virtual ~HarmonySearch() = 0;

    /** Algorithm execution. */
    virtual void run() = 0;

    /** Get the algorithm name. */
    virtual const char *getName() = 0;
};

#endif	/* HARMONYSEARCH_H */
