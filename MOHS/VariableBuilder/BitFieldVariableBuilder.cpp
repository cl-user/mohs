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

#include "Variable/BinaryVariable.h"
#include "Variable/BitFieldVariable.h"
#include "VariableBuilder/BitFieldVariableBuilder.h"

BitFieldVariableBuilder::BitFieldVariableBuilder() {
    
}

BitFieldVariableBuilder::~BitFieldVariableBuilder() {
    
}

BitFieldVariable *BitFieldVariableBuilder::createVariable(unsigned int length) {
    return new BitFieldVariable(length);
}

BitFieldVariable *BitFieldVariableBuilder::createVariable(int32_t value, unsigned int length) {
  return new BitFieldVariable(value, length);
}

BitFieldVariable *BitFieldVariableBuilder::createVariable(Variable *min, Variable *max, Random *random) {
    BitFieldVariable *auxMin = (BitFieldVariable *) min;
    BitFieldVariable *auxMax = (BitFieldVariable *) max;
    int32_t aux = random->boundedIntegerRandom((int) auxMin->getValue(), (int) auxMax->getValue());

    return this->createVariable(aux, auxMin->getLength());
}

BitFieldVariable *BitFieldVariableBuilder::createVariable(Variable *value) {
    BitFieldVariable *bv = (BitFieldVariable *) value;

    return this->createVariable(bv->getValue(), bv->getLength());
}

BitFieldVariable *BitFieldVariableBuilder::addVariables(Variable *a, Variable *b) {
    BitFieldVariable *bv1 = (BitFieldVariable *) a;
    BitFieldVariable *bv2 = (BitFieldVariable *) b;

    return this->createVariable(bv1->getValue() + bv2->getValue(), bv1->getLength());
}

BitFieldVariable *BitFieldVariableBuilder::substractVariables(Variable *a, Variable *b) {
    BitFieldVariable *bv1 = (BitFieldVariable *) a;
    BitFieldVariable *bv2 = (BitFieldVariable *) b;

    return this->createVariable(bv1->getValue() - bv2->getValue(), bv1->getLength());
}

BitFieldVariable *BitFieldVariableBuilder::mutateVariable(BinaryVariable *var, BinaryVariable *mask) {
    BitFieldVariable *bv1 = (BitFieldVariable *) var;
    BitFieldVariable *bv2 = (BitFieldVariable *) mask;

    return this->createVariable(bv1->getValue() ^ bv2->getValue(), bv1->getLength());
}

const char *BitFieldVariableBuilder::getName() {
    return "BitFieldVariableBuilder";
}
