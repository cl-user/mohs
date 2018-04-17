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

#include "VariableBuilder/IntegerVariableBuilder.h"
#include "Variable/IntegerVariable.h"

IntegerVariableBuilder::IntegerVariableBuilder() {

}

IntegerVariableBuilder::~IntegerVariableBuilder() {
    
}

Variable *IntegerVariableBuilder::createVariable(int value) {
    return new IntegerVariable(value);
}

Variable *IntegerVariableBuilder::createVariable(Variable *min, Variable *max, Random *random) {
    IntegerVariable *auxMin = (IntegerVariable *) min;
    IntegerVariable *auxMax = (IntegerVariable *) max;
    int aux = random->boundedIntegerRandom(auxMin->getValue(), auxMax->getValue());

    Variable *result = this->createVariable(aux);
    return result;
}

Variable *IntegerVariableBuilder::createVariable(Variable *value) {
    IntegerVariable *rv = (IntegerVariable *) value;

    Variable *result = this->createVariable(rv->getValue());
    return result;
}

Variable *IntegerVariableBuilder::addVariables(Variable *a, Variable *b) {
    IntegerVariable *rv1 = (IntegerVariable *) a;
    IntegerVariable *rv2 = (IntegerVariable *) b;

    Variable *result = this->createVariable(rv1->getValue() + rv2->getValue());
    return result;
}

Variable *IntegerVariableBuilder::substractVariables(Variable *a, Variable *b) {
    IntegerVariable *rv1 = (IntegerVariable *) a;
    IntegerVariable *rv2 = (IntegerVariable *) b;

    Variable *result = this->createVariable(rv1->getValue() - rv2->getValue());
    return result;
}

const char *IntegerVariableBuilder::getName() {
    return "IntegerVariableBuilder";
}
