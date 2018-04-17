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

#include "Problem/ZDT/ZDT4.h"
#include "Variable/RealVariable.h"
#include <cmath>

ZDT4::ZDT4(const char *path, HS_Params *hsParams,
        VariableBuilder *varBuilder) : RealProblem(path, hsParams, varBuilder) {
    
}

ZDT4::~ZDT4() {
    
}

double ZDT4::paretoOrdinate(double f1) {
    return 1 - sqrt(f1);
}

void ZDT4::evaluate(Solution *sol) {
    double f1, f2, g, h, sum;
    int n = sol->getSize();
    
    sum = 0;
    for (int i=1; i < sol->getSize(); i++) {
        double xi = ((RealVariable *) sol->getVariable(i))->getValue();
        sum += xi*xi - 10*cos(4*PI*xi);
    }

    f1 = ((RealVariable *) sol->getVariable(0))->getValue(); // x1
    g = 1 + 10 * (n - 1) + sum;
    h = 1 - sqrt(f1/g);
    f2 = g * h;

    sol->setObjectiveValue(0, f1);
    sol->setObjectiveValue(1, f2);
}

double ZDT4::getMaxDistance() const {

}

const char *ZDT4::getName() {
    return "ZDT4";
}
