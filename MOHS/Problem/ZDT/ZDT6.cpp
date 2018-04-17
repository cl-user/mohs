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

#include "Problem/ZDT/ZDT6.h"
#include "Variable/RealVariable.h"
#include <cmath>

ZDT6::ZDT6(const char *path, HS_Params *hsParams,
        VariableBuilder *varBuilder) : RealProblem(path, hsParams, varBuilder) {
    
}

ZDT6::~ZDT6() {
    
}

double ZDT6::paretoOrdinate(double f1) {
    return 1 - pow(f1, 2);
}

ParetoSet *ZDT6::optimalParetoFront(void) {
    double f1min, f1max, f1;
    double x1min = ((RealVariable *) minimum[0])->getValue();
    double x1max = ((RealVariable *) maximum[0])->getValue();

    /* Use double precision */
    double e = pow((x1max-x1min)/(double) pfsize, 2);

    f1min = f1max = evaluateF1(x1min);
    for (double x1 = x1min + e; x1 <= x1max; x1 += e) {
        f1 = evaluateF1(x1);
        if (f1 < f1min)
            f1min = f1;
        if (f1 > f1max)
            f1max = f1;
    }

    return optimalParetoFront2D(f1min, f1max, (f1max - f1min) / (double) pfsize);
}

double ZDT6::evaluateF1(double x1) {
    return 1 - exp(-4*x1) * pow((sin(6*PI*x1)), 6);
}

void ZDT6::evaluate(Solution *sol) {
    double f1, f2, g, h, sum;
    int n = sol->getSize();
    
    sum = 0;
    for (int i=1; i < sol->getSize(); i++)
    	sum += ((RealVariable *) sol->getVariable(i))->getValue();

    double x1 = ((RealVariable *) sol->getVariable(0))->getValue();
    f1 = evaluateF1(x1);
    g = 1 + 9 * pow(sum / (n - 1), 0.25);
    h = 1 - pow(f1/g, 2);
    f2 = g * h;

    sol->setObjectiveValue(0, f1);
    sol->setObjectiveValue(1, f2);
}

double ZDT6::getMaxDistance() const {

}

const char *ZDT6::getName() {
    return "ZDT6";
}
