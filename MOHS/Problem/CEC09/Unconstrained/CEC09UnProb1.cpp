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

#include "Problem/CEC09/Unconstrained/CEC09UnProb1.h"
#include "Variable/RealVariable.h"
#include <cmath>
using namespace std;

CEC09UnProb1::CEC09UnProb1(const char *path, HS_Params *hsParams,
        VariableBuilder *varBuilder) : CEC09UnProb1to7(path, hsParams, varBuilder) {
    
}

CEC09UnProb1::~CEC09UnProb1() {
    
}

double CEC09UnProb1::paretoOrdinate(double f1) {
    return 1.0 - sqrt(f1);
}

void CEC09UnProb1::evaluate(Solution *sol) {
    /* Set J1 and set J2 sizes */
    int J1size = J1.size();
    int J2size = J2.size();

    /* Sum for F1 */
    double sum1 = 0;
    for (int i=0; i < J1size; i++) {
        int j = J1[i];
        double xj  = ((RealVariable *) sol->getVariable(j - 1))->getValue();
        double x1  = ((RealVariable *) sol->getVariable(0))->getValue();
        double aux = xj - sin(6 * PI * x1 + (j * PI) / size);
        sum1 += aux * aux;
    }

    /* Sum for F2 */
    double sum2 = 0;
    for (int i=0; i < J2size; i++) {
        int j = J2[i];
        double xj  = ((RealVariable *) sol->getVariable(j - 1))->getValue();
        double x1  = ((RealVariable *) sol->getVariable(0))->getValue();
        double aux = xj - sin(6 * PI * x1 + (j * PI) / size);
        sum2 += aux * aux;
    }

    /* Calculate F1 and F2 */
    double x1  = ((RealVariable *) sol->getVariable(0))->getValue();
    double f1  = x1 + (2.0 / J1size) * sum1;
    double f2  = 1 - sqrt(x1) + (2.0 / J2size) * sum2;

    sol->setObjectiveValue(0, f1);
    sol->setObjectiveValue(1, f2);
}

double CEC09UnProb1::getMaxDistance() const {
    return sqrt(2);
}

const char *CEC09UnProb1::getName() {
    return "CEC09_UnconstrainedProblem1";
}
