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

#include "HS_Structures/Memory/BinaryModalMemory.h"
#include "Variable/BinaryVariable.h"
#include "VariableBuilder/BinaryVariableBuilder.h"

BinaryModalMemory::BinaryModalMemory(int size, Problem *problem) : 
    ModalMemory(size, problem) {

    /* Build each histogram */
    for (int i=0; i < this->histogramCount; i++) {
        int barsCount = ((BinaryVariable *) this->problem->getMaximum(i))->getLength() + 1;
        this->histogram[i].barsCount = barsCount;
        this->histogram[i].bars = new histogram_bar_t[barsCount];
        this->histogram[i].orderedBars = new histogram_bar_t*[barsCount];

        for (int j=0; j < this->histogram[i].barsCount; j++) {
            this->histogram[i].bars[j].bits  = j;
            this->histogram[i].bars[j].count = 0;
        }
    }
}

BinaryModalMemory::~BinaryModalMemory() {
    
}

void BinaryModalMemory::calculateMode() {
    /* Build the histogram */
    for (int i=0; i < this->histogramCount; i++) {
        for (int j=0; j < this->getSize(); j++) {
            Solution *sol = this->getSolution(j);
            int value = ((BinaryVariable *) sol->getVariable(i))->countBitsSet();
            histogram[i].bars[value].count += 1;
        }
    }

    /* Sort the histogram */
    sortHistogram();
}

Variable *BinaryModalMemory::getMode(int variable) {
    /* Mode position */
    int last = histogram[variable].barsCount - 1;

    /* Bit number of the mode */
    int bitsCount = histogram[variable].bars[last].bits;

    /* Variable length */
    Solution *sol = this->getSolution(0);
    int length = ((BinaryVariable *) sol->getVariable(variable))->getLength();

    /* Calculate mode */
    BinaryVariableBuilder *builder = (BinaryVariableBuilder *) this->problem->getVariableBuilder();
    BinaryVariable *mode = builder->createVariable(length);
    for (int i=0; i < bitsCount; i++)
        mode->setBit(1, i);

    return mode;
}

int BinaryModalMemory::findBarPos(int variable, Variable* value) {
    int pos = ((BinaryVariable *) value)->countBitsSet();
    return pos;
}
