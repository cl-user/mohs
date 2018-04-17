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

#include <stdlib.h>

#include "Variable/IntegerVariable.h"

IntegerVariable::IntegerVariable(int value) {
    this->value = value;
}

IntegerVariable::~IntegerVariable() {

}

void IntegerVariable::print(FILE *output) {
    fprintf(output, "%e", value);
}

Variable *IntegerVariable::distanceTo(const Variable *other) {
    IntegerVariable *var = (IntegerVariable *) other;
    return new IntegerVariable(abs(var->value - this->value));
}

int IntegerVariable::compare(const Variable *other) {
    IntegerVariable *rv = (IntegerVariable *) other;
    if (value < rv->value)
        return -1;
    else if (value > rv->value)
        return 1;
    else
        return 0;
}

int IntegerVariable::getValue(void) {
    return value;
}

const char *IntegerVariable::getName() {
    return "IntegerVariable";
}
