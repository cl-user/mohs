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

#include "HS_Structures/Memory/RealModalMemory.h"
#include "Variable/RealVariable.h"
#include "VariableBuilder/RealVariableBuilder.h"
#include <cmath>

RealModalMemory::RealModalMemory(int size, Problem *problem) : 
    ModalMemory(size, problem) {

    /* Builds limits of the histogram */
    for (int i=0; i < this->histogramCount; i++) {

        /* Values to build histogram */
        double minValue = ((RealVariable *) this->problem->getMinimum(i))->getValue();
        double maxValue = ((RealVariable *) this->problem->getMaximum(i))->getValue();
        double fwValue  = ((RealVariable *) this->problem->getFretWidth(i))->getValue();

        /* Histogram for calculate the mode of a given variable */
        int barsCount = (int) ceil((maxValue - minValue) / fwValue);
        this->histogram[i].barsCount = barsCount;
        this->histogram[i].bars = new histogram_bar_t[barsCount];
        this->histogram[i].orderedBars = new histogram_bar_t*[barsCount];

        /* Builds limits of each variable histogram */
        this->histogram[i].bars[0].min = minValue;
        this->histogram[i].bars[0].max = minValue + fwValue;
        this->histogram[i].bars[0].count = 0;
        for (int j=1; j < this->histogram[i].barsCount; j++) {
            this->histogram[i].bars[j].min = this->histogram[i].bars[j - 1].max;
            this->histogram[i].bars[j].max = this->histogram[i].bars[j].min + fwValue;
            this->histogram[i].bars[j].count = 0;
        }
    }
}

RealModalMemory::~RealModalMemory() {
    
}

void RealModalMemory::calculateMode() {
    /* Builds the histogram */
    for (int i=0; i < this->histogramCount; i++) {
        for (int j=0; j < this->getSize(); j++) {
            Solution *sol = this->getSolution(j);
            int pos = this->findBarPos(i, sol->getVariable(i));
            this->histogram[i].bars[pos].count += 1;
        }
    }

    /* Sort the histogram */
    sortHistogram();
}

Variable *RealModalMemory::getMode(int variable) {
    /* Selected bar width */
    double fwValue = ((RealVariable *) problem->getFretWidth(variable))->getValue();

    /* Mode position */
    int last = histogram[variable].barsCount - 1;

    /* Calculate the mode */
    double value = histogram[variable].orderedBars[last]->min + fwValue / 2.0;

    RealVariableBuilder *builder = (RealVariableBuilder *) this->problem->getVariableBuilder();
    return builder->createVariable(value);
}

int RealModalMemory::findBarPos(int variable, Variable* value) {
    /* Get values */
    double val = ((RealVariable *) value)->getValue();
    double min = ((RealVariable *) this->problem->getMinimum(variable))->getValue();
    double max = ((RealVariable *) this->problem->getMaximum(variable))->getValue();
    int N = histogram[variable].barsCount - 1;

    /* Location function (hashing) */
    int pos = (int) round(N * (val - min) / (max - min));
    return pos;
}
