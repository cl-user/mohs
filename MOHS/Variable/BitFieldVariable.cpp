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

#include "Variable/BitFieldVariable.h"
#include "Variable/IntegerVariable.h"

BitFieldVariable::BitFieldVariable(int32_t value, unsigned int length) : BinaryVariable(length) {
    this->value = value;
}

BitFieldVariable::BitFieldVariable(unsigned int length) : BinaryVariable(length) {
    this->value = 0;
}

BitFieldVariable::~BitFieldVariable() {

}

void BitFieldVariable::print(FILE *output) {
    fprintf(output, "%8x", value);
}

Variable *BitFieldVariable::distanceTo(const Variable *other) {
    int32_t val  = this->value ^ ((BitFieldVariable *) other)->getValue();
    int32_t dist = 0;

    while (val) {
        dist++;
        val &= val - 1;
    }

    return new IntegerVariable(dist);
}

int BitFieldVariable::compare(const Variable *other) {
    BitFieldVariable *binOther = (BitFieldVariable *) other;
    int32_t valOther = binOther->getValue();

    if (value > valOther)
	return 1;
    else if (value < valOther)
	return -1;
    else
	return 0;
}

int32_t BitFieldVariable::getValue(void) {
    return value;
}

const char *BitFieldVariable::getName() {
    return "BitFieldVariable";
}

char BitFieldVariable::getBit(unsigned int position) {
    return (this->value & (1 << position)) != 0 ? 1 : 0;
}

void BitFieldVariable::setBit(char bit, unsigned int position) {
    if (bit)
        this->value |= 1 << position;
    else
        this->value &= (~0 - 1) << position;
}

unsigned int BitFieldVariable::countBitsSet(void) {
    /*
     * Successively set to 0 the rightmost bit until the original number
     * turns 0. Counting the times that this operation is performed.
     */
    int32_t val = this->value;
    unsigned int count = 0;

    while(val) {
        count++;
        val &= val - 1;
    }

    return count;
}
