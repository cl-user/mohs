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

#include "Variable/RealVariable.h"

RealVariable::RealVariable(double value) {
    this->value = value;
}

RealVariable::~RealVariable() {

}

void RealVariable::print(FILE *output) {
    fprintf(output, "%e", value);
}

Variable *RealVariable::distanceTo(const Variable *other) {
    RealVariable *var = (RealVariable *) other;
    return new RealVariable(fabs(var->value - this->value));
}

int RealVariable::compare(const Variable *other) {
    RealVariable *rv = (RealVariable *) other;
    if (value < rv->value)
        return -1;
    else if (value > rv->value)
        return 1;
    else
        return 0;
}

double RealVariable::getValue(void) {
    return value;
}

const char *RealVariable::getName() {
    return "RealVariable";
}
