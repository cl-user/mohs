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

#include "VariableBuilder/RealVariableBuilder.h"
#include "Variable/RealVariable.h"

RealVariableBuilder::RealVariableBuilder() {

}

RealVariableBuilder::~RealVariableBuilder() {
    
}

Variable *RealVariableBuilder::createVariable(double value) {
    return new RealVariable(value);
}

Variable *RealVariableBuilder::createVariable(Variable *min, Variable *max, Random *random) {
    RealVariable *auxMin = (RealVariable *) min;
    RealVariable *auxMax = (RealVariable *) max;
    double aux = random->boundedRandom(auxMin->getValue(), auxMax->getValue());

    Variable *result = this->createVariable(aux);
    return result;
}

Variable *RealVariableBuilder::createVariable(Variable *value) {
    RealVariable *rv = (RealVariable *) value;

    Variable *result = this->createVariable(rv->getValue());
    return result;
}

Variable *RealVariableBuilder::addVariables(Variable *a, Variable *b) {
    RealVariable *rv1 = (RealVariable *) a;
    RealVariable *rv2 = (RealVariable *) b;

    Variable *result = this->createVariable(rv1->getValue() + rv2->getValue());
    return result;
}

Variable *RealVariableBuilder::substractVariables(Variable *a, Variable *b) {
    RealVariable *rv1 = (RealVariable *) a;
    RealVariable *rv2 = (RealVariable *) b;

    Variable *result = this->createVariable(rv1->getValue() - rv2->getValue());
    return result;
}

const char *RealVariableBuilder::getName() {
    return "RealVariableBuilder";
}
