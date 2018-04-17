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

#include "HS_Operators/MemoryConsideration/RealModalMemoryConsideration.h"
#include "Variable/RealVariable.h"
#include "VariableBuilder/RealVariableBuilder.h"

RealModalMemoryConsideration::RealModalMemoryConsideration() {

}

RealModalMemoryConsideration::~RealModalMemoryConsideration() {

}

/* Histogram datatype */
typedef struct {
    double min, max;
    int count;
} histogram_t;

Variable *RealModalMemoryConsideration::calculateMode(Problem *problem,
        Memory *memory, int variable, Random *random) {

    /* Values to build the histogram */
    double minValue = ((RealVariable *) problem->getMinimum(variable))->getValue();
    double maxValue = ((RealVariable *) problem->getMaximum(variable))->getValue();
    double fwValue  = ((RealVariable *) problem->getFretWidth(variable))->getValue();

    /* Histogram to calculate the mode */
    const int size = (int) ((maxValue - minValue) / fwValue);
    histogram_t *histogram = new histogram_t[size];

    /* Build limits for the histogram */
    histogram[0].min = minValue;
    histogram[0].max = histogram[0].min + fwValue;
    histogram[0].count = 0;
    for (int i=1; i < size; i++) {
        histogram[i].min = histogram[i - 1].max;
        histogram[i].max = histogram[i].min + fwValue;
        histogram[i].count = 0;
    }

    /* Build the histogram */
    for (int i=0; i < memory->getSize(); i++) {
        Solution *sol = memory->getSolution(i);
        double var = ((RealVariable *) sol->getVariable(variable))->getValue();
        for (int j=0; j < size; j++) {
            if (j == 0 && var < histogram[j].max)
                histogram[j].count += 1;
            else if (j == size - 1 && var >= histogram[j].min)
                histogram[j].count += 1;
            else if (var >= histogram[j].min && var < histogram[j].max)
                histogram[j].count += 1;
        }
    }

    /* Search for the biggest histogram */
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
    double mode = histogram[pos].min + fwValue / 2.0;
    delete[] histogram;

    return ((RealVariableBuilder *) problem->getVariableBuilder())->createVariable(mode);
}

Variable *RealModalMemoryConsideration::selectVariable(Problem *problem,
        Memory *memory, int variable, Random *random) {

    /* Randomly choose two slots from memory */
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

    /* Compute distance of each variable to the mode */
    double dist1 = ((RealVariable *) var1->distanceTo(mode))->getValue();
    double dist2 = ((RealVariable *) var2->distanceTo(mode))->getValue();

    /* Choose the furthest variable to the mode */
    if (dist1 > dist2)
        return problem->getVariableBuilder()->createVariable(var1);
    else
        return problem->getVariableBuilder()->createVariable(var2);
}

const char *RealModalMemoryConsideration::getName() {
    return "RealBTMemoryConsideration";
}
