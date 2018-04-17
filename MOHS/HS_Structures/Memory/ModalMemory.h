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

#ifndef MODALMEMORY_H
#define	MODALMEMORY_H

#include "Problem/Problem.h"
#include "HS_Structures/Memory/Memory.h"
#include "Variable/Variable.h"

/** Datatype for Histogram Bar */
typedef struct {
    double min, max;
    int bits;
    int count;
    int rank;
} histogram_bar_t;

/** Datatype for Histogram data */
typedef struct {
    histogram_bar_t *bars;
    histogram_bar_t **orderedBars;
    int barsCount;
} histogram_t;

class ModalMemory : public Memory {
protected:
    /* Histogram count */
    int histogramCount;

    /* Each variable histograms */
    histogram_t *histogram;

    /* Memory associated problem */
    Problem *problem;

    /* Sorts the histogram */
    void sortHistogram();

    /* Re-sort bars when the counter of each of them is updated */
    void sortBars(int histogramPos, int barPos, bool ascending);

    /* Swap the position of two bars */
    void swapBars(int hisotramPos, int barPos, int otherPos);

    /* Location function (hashing) */
    virtual int findBarPos(int variable, Variable *value) = 0;

public:
    /** Constructor */
    ModalMemory(int size, Problem *problem);

    /** Destructor */
    virtual ~ModalMemory() = 0;

    /** Calculates the mode when the memory have been initialized */
    virtual void calculateMode() = 0;

    /** Calculates the mode of a given variable */
    virtual Variable *getMode(int variable) = 0;

    /** Updates the mode of a given variable */
    void updateMode(int variable, Variable *value, bool increment);
};

#endif	/* MODALMEMORY_H */
