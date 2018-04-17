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

#include "Problem/ZDT/ZDT5.h"
#include "Variable/BinaryVariable.h"
#include "VariableBuilder/BinaryVariableBuilder.h"
#include "VariableBuilder/IntegerVariableBuilder.h"
#include "HS_Structures/Pareto/ParetoSet.h"
#include "Variable/Variable.h"
#include <cmath>
#include <stdint.h>
#include <cstdlib>
#include <string.h>

ZDT5::ZDT5(const char *path, HS_Params *hsParams,
        VariableBuilder *varBuilder) : Problem(varBuilder) {
    FILE *file;
    int32_t min, max;
    int fw;

    if ((file = fopen(path, "r")) == NULL) {
        fprintf(stderr, "Error opening file '%s' in read mode\n", path);
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", &objectives);
    fscanf(file, "%d", &size);
    fscanf(file, "%d", &pfsize);
    minimum = new Variable*[size];
    maximum = new Variable*[size];
    fretWidth = new Variable*[size];

    IntegerVariableBuilder *fwBuilder = new IntegerVariableBuilder();

    /* Read parameters for the first variable */
    fscanf(file, "%x", &min);
    fscanf(file, "%x", &max);
    fscanf(file, "%d", &fw);

    minimum[0] = ((BinaryVariableBuilder *) varBuilder)->createVariable(30);
    maximum[0] = ((BinaryVariableBuilder *) varBuilder)->createVariable(30);
    fretWidth[0] = fwBuilder->createVariable(fw);
    for (unsigned int pos = 0; pos < 30; pos++) {
        char minBit = (min & (1 << pos)) != 0 ? 1 : 0;
        char maxBit = (max & (1 << pos)) != 0 ? 1 : 0;

        ((BinaryVariable *) minimum[0])->setBit(minBit, pos);
        ((BinaryVariable *) maximum[0])->setBit(maxBit, pos);
    }

    /* Read parameters for the other variables */
    for (int i = 1; i < size; i++) {
        fscanf(file, "%x", &min);
        fscanf(file, "%x", &max);
        fscanf(file, "%d", &fw);
        minimum[i] = ((BinaryVariableBuilder *) varBuilder)->createVariable(5);
        maximum[i] = ((BinaryVariableBuilder *) varBuilder)->createVariable(5);
        fretWidth[i] = fwBuilder->createVariable(fw);
        for (unsigned int pos = 0; pos < 5; pos++) {
            char minBit = (min & (1 << pos)) != 0 ? 1 : 0;
            char maxBit = (max & (1 << pos)) != 0 ? 1 : 0;
            ((BinaryVariable *) minimum[i])->setBit(minBit, pos);
            ((BinaryVariable *) maximum[i])->setBit(maxBit, pos);
        }
    }

    fclose(file);

    if (hsParams->getSetFW() == 1) {
        int width = ((int) hsParams->getBinFW()) * 30 / 100;
        fretWidth[0] = fwBuilder->createVariable(width);

        for (int i = 1; i < size; i++) {
            int width = ((int) hsParams->getBinFW()) * 30 / 100;
            fretWidth[i] = fwBuilder->createVariable(width);
        }
    }

    delete fwBuilder;
}

ZDT5::~ZDT5() {
    for (int i = 0; i < size; i++) {
        delete minimum[i];
        delete maximum[i];
        delete fretWidth[i];
    }
    
    delete[] minimum;
    delete[] maximum;
    delete[] fretWidth;
}

double ZDT5::paretoOrdinate(double f1) {
    return 10.0 / f1;
}

ParetoSet *ZDT5::optimalParetoFront(void) {
    /*
     * The abscissa value of Pareto front in problem ZDT5 is equal to
     * the number of 1-bits of the first variable, plus one.
     */
    unsigned int f1min = 0;
    unsigned int f1max = 0;
    unsigned int epsilon;

    f1min = ((BinaryVariable *) minimum[0])->countBitsSet() + 1;
    f1max = ((BinaryVariable *) maximum[0])->countBitsSet() + 1;

    if (pfsize > f1max - f1min)
        epsilon = 1;
    else if (pfsize == 0)
        epsilon = f1max - f1min;
    else
        epsilon = (f1max - f1min) / pfsize;

    return optimalParetoFront2D((double) f1min, (double) f1max, (double) epsilon);
}

void ZDT5::evaluate(Solution *sol) {
    double g, h, f1, f2;

    int *u = new int[size];
    int *v = new int[size];
    memset(u, 0, size * sizeof(int));
    memset(v, 0, size * sizeof(int));

    for (int i=0; i < size; i++) {
        BinaryVariable *binVar = (BinaryVariable *) sol->getVariable(i);
	u[i] = binVar->countBitsSet();
    }

    for (int i=1; i < size; i++)
        if (u[i] < 5)
            v[i] = u[i] + 2;
        else
            v[i] = 1;

    double sumv = 0;
    for (int i=1; i < size; i++)
        sumv += v[i];

    f1 = 1.0 + u[0];
    g = sumv;
    h = 1.0 / f1;
    f2 = g * h;

    delete[] u;
    delete[] v;
    
    sol->setObjectiveValue(0, f1);
    sol->setObjectiveValue(1, f2);
}

double ZDT5::getMaxDistance() const {

}

const char *ZDT5::getName(void) {
    return "ZDT5";
}
