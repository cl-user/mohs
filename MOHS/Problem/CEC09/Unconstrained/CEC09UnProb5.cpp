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

#include "Problem/CEC09/Unconstrained/CEC09UnProb5.h"
#include "Variable/RealVariable.h"
#include <cstdlib>
#include <cmath>

CEC09UnProb5::CEC09UnProb5(const char *path, HS_Params *hsParams,
        VariableBuilder *varBuilder) : CEC09UnProb1to7(path, hsParams, varBuilder) {

    FILE *file;

    if ((file = fopen(path, "r")) == NULL) {
        fprintf(stderr, "Error opening file '%s' in read mode\n", path);
        exit(EXIT_FAILURE);
    }

    double aux;
    fscanf(file, "%d", &aux);
    fscanf(file, "%d", &aux);
    fscanf(file, "%d", &aux);

    for (int i=0; i < size; i++) {
        fscanf(file, "%lf", &aux);
        fscanf(file, "%lf", &aux);
        fscanf(file, "%lf", &aux);
    }

    /* Problem additional parameters */
    fscanf(file, "%lf", &N);
    fscanf(file, "%lf", &epsilon);

    fclose(file);
}

CEC09UnProb5::~CEC09UnProb5() {
    
}

double CEC09UnProb5::paretoOrdinate(double f1) {
    return 1.0 - f1;
}

ParetoSet *CEC09UnProb5::optimalParetoFront(void) {
    double epsilon;

    if (pfsize > 2 * N)
        epsilon = 1.0 / (2.0 * (double) N);
    else if (pfsize == 0)
        epsilon = 1.0;
    else
        epsilon = (double) (2 * N / pfsize) / (2.0 * (double) N);

    return optimalParetoFront2D(0.0, 1.0, epsilon);
}

void CEC09UnProb5::evaluate(Solution *sol) {
    /* Set J1 and set J2 sizes */
    int J1size = J1.size();
    int J2size = J2.size();

    /* Sum for F1 */
    double sum1 = 0;
    for (int i=0; i < J1size; i++) {
        int j = J1[i];
        double xj = ((RealVariable *) sol->getVariable(j - 1))->getValue();
        double x1 = ((RealVariable *) sol->getVariable(0))->getValue();
        double yval = y(xj, j, x1);
        double hval = h(yval);
        sum1 += hval;
    }

    /* Sum for F2 */
    double sum2 = 0;
    for (int i=0; i < J2size; i++) {
        int j = J2[i];
        double xj = ((RealVariable *) sol->getVariable(j - 1))->getValue();
        double x1 = ((RealVariable *) sol->getVariable(0))->getValue();
        double yval = y(xj, j, x1);
        double hval = h(yval);
        sum2 += hval;
    }

    /* Calculate F1 and F2 */
    double x1  = ((RealVariable *) sol->getVariable(0))->getValue();
    double aux = (1 / (2 * N) + epsilon) * fabs(sin(2 * N * PI * x1));
    double f1  = x1 + aux + (2.0 / J1size) * sum1;
    double f2  = 1 - x1 + aux + (2.0 / J2size) * sum2;

    sol->setObjectiveValue(0, f1);
    sol->setObjectiveValue(1, f2);
}

double CEC09UnProb5::getMaxDistance() const {

}

double CEC09UnProb5::y(double xj, int j, double x1) {
    return xj - sin(6 * PI * x1 + (j * PI) / size);
}

double CEC09UnProb5::h(double t) {
    return 2 * t * t - cos(4 * PI * t) + 1;
}

const char *CEC09UnProb5::getName() {
    return "CEC09_UnconstrainedProblem5";
}
