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

#include <cstdlib>
#include <cstdio>
#include <exception>
#include <stdexcept>
#include <string.h>
#include "HS/HarmonySearch.h"
#include "HS/HarmonySearch1.h"
#include "HS/HarmonySearch2.h"
#include "HS/HarmonySearch3.h"
#include "HS/HS_Params.h"
#include "Problem/Problem.h"
#include "Problem/ZDT/ZDT1.h"
#include "Problem/ZDT/ZDT2.h"
#include "Problem/ZDT/ZDT3.h"
#include "Problem/ZDT/ZDT4.h"
#include "Problem/ZDT/ZDT5.h"
#include "Problem/ZDT/ZDT6.h"
#include "VariableBuilder/RealVariableBuilder.h"
#include "VariableBuilder/BitFieldVariableBuilder.h"
#include "HS_Operators/MemoryConsideration/SimpleMemoryConsideration.h"
#include "HS_Operators/MemoryUpdate/SimpleMemoryUpdate.h"
#include "HS_Operators/ParetoRanking/FonsecaFlemingRanking.h"
#include "HS_Operators/MemoryUpdate/RandomMemoryUpdate.h"
#include "Problem/CEC09/Unconstrained/CEC09UnProb1.h"
#include "Problem/CEC09/Unconstrained/CEC09UnProb2.h"
#include "Problem/CEC09/Unconstrained/CEC09UnProb3.h"
#include "Problem/CEC09/Unconstrained/CEC09UnProb4.h"
#include "Problem/CEC09/Unconstrained/CEC09UnProb5.h"
#include "HS_Operators/MemoryInit/MemoryInit.h"
#include "HS_Operators/MemoryInit/SimpleMemoryInit.h"
#include "HS_Operators/PitchAdjustment/BoundedPitchAdjustment.h"
#include "HS_Operators/PitchAdjustment/HammingPitchAdjustment.h"
#include "HS_Structures/Memory/MemoryBuilder/MemoryBuilder.h"
#include "HS_Structures/Memory/MemoryBuilder/SimpleMemoryBuilder.h"
#include "HS_Operators/MemoryInit/ModalMemoryInit.h"
#include "HS_Operators/MemoryConsideration/ModalMemoryConsideration.h"
#include "HS_Operators/MemoryUpdate/ModalMemoryUpdate.h"
#include "HS_Structures/Memory/MemoryBuilder/BinaryModalMemoryBuilder.h"
#include "HS_Structures/Memory/MemoryBuilder/RealModalMemoryBuilder.h"
using namespace std;

int main(int argc, char** argv) {
    try {
        if (argc != 7)
            throw invalid_argument("Use: <programFile> <hsConfigFile> <problem> "
                    "<algorithm> <calculateMetrics> <doSampling> <modalMode>");

        /* Initialize HS parameters */
        HS_Params *hsParams = new HS_Params(argv[1]);

        /* Root of data files paths */
        char path[100];
        path[0] = '\0';
        strcat(path, "../../datos/test_problems");

        /* Initialize problem parameters */
        Problem *problem = NULL;
        if (strcasecmp(argv[2], "zdt1") == 0)
            problem = new ZDT1(strcat(path, "/zdt/zdt1.txt"),
                    hsParams, new RealVariableBuilder());
        else if (strcasecmp(argv[2], "zdt2") == 0)
            problem = new ZDT2(strcat(path, "/zdt/zdt2.txt"),
                    hsParams, new RealVariableBuilder());
        else if (strcasecmp(argv[2], "zdt3") == 0)
            problem = new ZDT3(strcat(path, "/zdt/zdt3.txt"),
                    hsParams, new RealVariableBuilder());
        else if (strcasecmp(argv[2], "zdt4") == 0)
            problem = new ZDT4(strcat(path, "/zdt/zdt4.txt"),
                    hsParams, new RealVariableBuilder());
        else if (strcasecmp(argv[2], "zdt5") == 0)
            problem = new ZDT5(strcat(path, "/zdt/zdt5.txt"),
                    hsParams, new BitFieldVariableBuilder());
        else if (strcasecmp(argv[2], "zdt6") == 0)
            problem = new ZDT6(strcat(path, "/zdt/zdt6.txt"),
                    hsParams, new RealVariableBuilder());
        else if (strcasecmp(argv[2], "cec09unprob1") == 0)
            problem = new CEC09UnProb1(strcat(path, "/cec09/cec09unprob1.txt"),
                    hsParams, new RealVariableBuilder());
        else if (strcasecmp(argv[2], "cec09unprob2") == 0)
            problem = new CEC09UnProb2(strcat(path, "/cec09/cec09unprob2.txt"),
                    hsParams, new RealVariableBuilder());
        else if (strcasecmp(argv[2], "cec09unprob3") == 0)
            problem = new CEC09UnProb3(strcat(path, "/cec09/cec09unprob3.txt"),
                    hsParams, new RealVariableBuilder());
        else if (strcasecmp(argv[2], "cec09unprob4") == 0)
            problem = new CEC09UnProb4(strcat(path, "/cec09/cec09unprob4.txt"),
                    hsParams, new RealVariableBuilder());
        else if (strcasecmp(argv[2], "cec09unprob5") == 0)
            problem = new CEC09UnProb5(strcat(path, "/cec09/cec09unprob5.txt"),
                    hsParams, new RealVariableBuilder());
        else
            throw invalid_argument("Invalid problem.\n"
                    "Options: zdt1, zdt2, zdt3, zdt4, zdt5, zdt6, "
                    "cec09unprob1, cec09unprob2, cec09unprob3, cec09unprob4, cec09unprob5");

        /* Metric computation set-up */
        bool calculateMetrics;
        if (strcasecmp(argv[4], "0") == 0)
            calculateMetrics = false;
        else if (strcasecmp(argv[4], "1") == 0)
            calculateMetrics = true;
        else
            throw invalid_argument("Expected 0 or 1 to compute metrics");

        /* Sampling set-up */
        bool doSampling;
        if (strcasecmp(argv[5], "0") == 0)
            doSampling = false;
        else if (strcasecmp(argv[5], "1") == 0)
            doSampling = true;
        else
            throw invalid_argument("Expected 0 or 1 to perform sampling");

        /* Modal mode set-up */
        bool modalMode;
        if (strcasecmp(argv[6], "0") == 0)
            modalMode = false;
        else if (strcasecmp(argv[6], "1") == 0)
            modalMode = true;
        else
            throw invalid_argument("Expected 0 or 1 to apply modal mode");

        /* HS algorithm set-up */
        ParetoRanking *parRank = new FonsecaFlemingRanking();
        PitchAdjustment *pitchAdj = NULL;
        if (strcasecmp(argv[2], "zdt5") == 0)
            pitchAdj = new HammingPitchAdjustment();
        else
            pitchAdj = new BoundedPitchAdjustment();

        MemoryInit *memInit = NULL;
        MemoryConsideration *memCons = NULL;
        MemoryUpdate *memUp = NULL;
        MemoryBuilder *memBuild = NULL;
        if (modalMode) {
            memInit = new ModalMemoryInit();
            memCons = new ModalMemoryConsideration();
            memUp   = new ModalMemoryUpdate();
            if (strcasecmp(argv[2], "zdt5") == 0)
                memBuild = new BinaryModalMemoryBuilder();
            else
                memBuild = new RealModalMemoryBuilder();
        }
        else {
            memInit  = new SimpleMemoryInit();
            memCons  = new SimpleMemoryConsideration();
            memUp    = new SimpleMemoryUpdate();
            memBuild = new SimpleMemoryBuilder();
        }

        /* Build HS algorithm */
        HarmonySearch *hsAlgorithm = NULL;
        if (strcasecmp(argv[3], "hs1") == 0)
            hsAlgorithm = new HarmonySearch1(problem, hsParams, memBuild,
                memInit, memCons, pitchAdj, memUp, parRank, calculateMetrics, doSampling, true);
        else if (strcasecmp(argv[3], "hs2") == 0)
            hsAlgorithm = new HarmonySearch2(problem, hsParams, memBuild,
                memInit, memCons, pitchAdj, memUp, parRank, calculateMetrics, doSampling);
        else if (strcasecmp(argv[3], "hs3") == 0)
            hsAlgorithm = new HarmonySearch3(problem, hsParams, memBuild,
                memInit, memCons, pitchAdj, memUp, parRank, calculateMetrics, doSampling);
        else
            throw invalid_argument("Invalid algorithm.\n"
                    "Options: hs1, hs2, h3");

        /* Run HS algorithm */
        hsAlgorithm->run();

        delete memInit;
        delete memCons;
        delete memUp;
        delete memBuild;
        delete pitchAdj;
        delete parRank;
        delete problem;
        delete hsParams;
        delete hsAlgorithm;
    }
    catch(bad_alloc &e) {
        fprintf(stderr, "%s\n", e.what());
        exit(EXIT_FAILURE);
    }
    catch(exception &e) {
        fprintf(stderr, "%s\n", e.what());
        exit(EXIT_FAILURE);
    }
    
    return (EXIT_SUCCESS);
}
