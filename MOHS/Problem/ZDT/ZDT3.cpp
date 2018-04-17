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

#include "Problem/ZDT/ZDT3.h"
#include "Variable/RealVariable.h"
#include <cmath>

ZDT3::ZDT3(const char *path, HS_Params *hsParams,
        VariableBuilder *varBuilder) : RealProblem(path, hsParams, varBuilder) {
    
}

ZDT3::~ZDT3() {
    
}

double ZDT3::paretoOrdinate(double f1) {
    return 1 - sqrt(f1) - f1 * sin(10*PI*f1);
}

void ZDT3::evaluate(Solution *sol) {
    double f1, f2, g, h, sum;
    int n = sol->getSize();
    
    sum = 0;
    for (int i=1; i < sol->getSize(); i++)
    	sum += ((RealVariable *) sol->getVariable(i))->getValue();

    f1 = ((RealVariable *) sol->getVariable(0))->getValue(); // x1
    g = 1 + 9 * sum / (n - 1);
    h = 1 - sqrt(f1/g) - (f1/g) * sin(10*PI*f1);
    f2 = g * h;

    sol->setObjectiveValue(0, f1);
    sol->setObjectiveValue(1, f2);
}

double ZDT3::getMaxDistance() const {

}

const char *ZDT3::getName() {
    return "ZDT3";
}
