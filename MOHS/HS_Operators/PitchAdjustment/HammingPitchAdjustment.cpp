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

#include <stdint.h>

#include "Variable/BinaryVariable.h"
#include "VariableBuilder/BinaryVariableBuilder.h"
#include "HS_Operators/PitchAdjustment/HammingPitchAdjustment.h"
#include "Variable/IntegerVariable.h"

HammingPitchAdjustment::HammingPitchAdjustment() {

}

HammingPitchAdjustment::~HammingPitchAdjustment() {

}

BinaryVariable *HammingPitchAdjustment::adjust(Problem *problem, int variable, Variable* value, Random* random) {
    /* Resulting variable */
    BinaryVariable *result = NULL;

    /* Get fret width for the variable */
    IntegerVariable *fw = (IntegerVariable *) problem->getFretWidth(variable);

    /* Count the number of bits that the variable can have */
    BinaryVariable *max = (BinaryVariable *) problem->getMaximum(variable);
    unsigned int length = max->countBitsSet();

    /* Decide how many bits will be flipped */
    unsigned int hammingDistance = random->boundedIntegerRandom(1, fw->getValue()+1);

    /* 
     * Randomly decide which bits will flip building a mask that has 1 in
     * positions where the variable bit will flip.
     */
    unsigned int count = 0;
    BinaryVariableBuilder *builder = (BinaryVariableBuilder *) problem->getVariableBuilder();
    BinaryVariable *mask = builder->createVariable(length);
    while (count < hammingDistance) {
        unsigned int pos = random->boundedIntegerRandom(0, length);

        /*
         * Check not to select an already selected bit.
         */
        if (!mask->getBit(pos)) {
            mask->setBit(1, pos);
            count++;
        }
    }

    result = builder->mutateVariable((BinaryVariable *) value, mask);

    delete mask;
    return result;
}

const char *HammingPitchAdjustment::getName() {
    return "HammingPitchAdjustment";
}
