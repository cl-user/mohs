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

#include "HS_Operators/MemoryConsideration/BinaryModalMemoryConsideration.h"
#include "Variable/BitFieldVariable.h"
#include "VariableBuilder/BitFieldVariableBuilder.h"
#include "Variable/IntegerVariable.h"

BinaryModalMemoryConsideration::BinaryModalMemoryConsideration() {

}

BinaryModalMemoryConsideration::~BinaryModalMemoryConsideration() {

}

/* Histogram datatype */
typedef struct {
    int bits;
    int count;
} histogram_t;

Variable *BinaryModalMemoryConsideration::calculateMode(Problem *problem,
        Memory *memory, int variable, Random *random) {

    /* Histogram to compute the mode */
    Solution *solution = memory->getSolution(0);
    const int size = ((BitFieldVariable *) solution->getVariable(variable))->getLength() + 1;
    histogram_t *histogram = new histogram_t[size];

    /* Building the histogram */
    for (int i=0; i < size; i++) {
        histogram[i].bits  = i;
        histogram[i].count = 0;
    }

    /* Building the histogram */
    for (int i=0; i < memory->getSize(); i++) {
        Solution *sol = memory->getSolution(i);
        int var = ((BitFieldVariable *) sol->getVariable(variable))->countBitsSet();
        for (int j=0; j < size; j++) {
            if (var == histogram[j].bits) {
                histogram[j].count += 1;
                break;
            }
        }
    }

    /* Find the biggest histogram */
    int max = histogram[0].count;
    int pos = 0;
    for (int i=1; i < size; i++) {
        if (histogram[i].count > max) {
            max = histogram[i].count;
            pos = i;
        }
        else if (histogram[i].count == max && random->boundedIntegerRandom(0, 2)) {
            max = histogram[i].count;
            pos = i;
        }
    }

    /* Compute the mode */
    int bitsCount = histogram[pos].bits;
    delete[] histogram;

    BitFieldVariable *mode = new BitFieldVariable(size - 1);
    for (int i=0; i < bitsCount; i++)
        mode->setBit(1, i);

    return mode;
}

Variable *BinaryModalMemoryConsideration::selectVariable(Problem *problem,
        Memory *memory, int variable, Random *random) {

    /* Choose two random positions from memory */
    int pos1, pos2;
    pos1 = random->boundedIntegerRandom(0, memory->getSize());
    do {
        pos2 = random->boundedIntegerRandom(0, memory->getSize());
    } while (pos1 == pos2);

    /* Choose candidate variables */
    Variable *var1 = memory->getSolution(pos1)->getVariable(variable);
    Variable *var2 = memory->getSolution(pos2)->getVariable(variable);

    /* Compute the mode */
    Variable *mode = calculateMode(problem, memory, variable, random);

    /* Compute the distance of each variable to the mode */
    int dist1 = ((IntegerVariable *) var1->distanceTo(mode))->getValue();
    int dist2 = ((IntegerVariable *) var2->distanceTo(mode))->getValue();

    /* Choose furthest variable from the mode */
    if (dist1 > dist2)
        return problem->getVariableBuilder()->createVariable(var1);
    else
        return problem->getVariableBuilder()->createVariable(var2);
}

const char *BinaryModalMemoryConsideration::getName() {
    return "BinaryBTMemoryConsideration";
}
