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

#ifndef HARMONYSEARCH1_H
#define	HARMONYSEARCH1_H

#include "HS/HarmonySearch.h"

class HarmonySearch1 : public HarmonySearch {
private:
    /* Pareto set truncation set-up */
    bool truncateParetoSet;

public:
    /** Constructor. */
    HarmonySearch1(Problem *problem, HS_Params *hsParams, MemoryBuilder *memoryBuilder,
	    MemoryInit *memoryInit, MemoryConsideration *memoryConsideration,
            PitchAdjustment *pitchAdjustment, MemoryUpdate *memoryUpdate,
            ParetoRanking *paretoRanking, bool calculateAndPrintMetrics, bool doSampling,
            bool truncateParetoSet);

    /** Destructor. */
    ~HarmonySearch1();

    /** Algorithm running. */
    void run();

    /** Returns the algorithm name. */
    const char *getName();
};

#endif	/* HARMONYSEARCH1_H */
