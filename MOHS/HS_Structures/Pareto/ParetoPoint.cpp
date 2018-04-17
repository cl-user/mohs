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

#include "HS_Structures/Pareto/ParetoPoint.h"
#include <cmath>

ParetoPoint::ParetoPoint(int objectives) {
    objectiveValues = new double[objectives];
    for (int i=0; i < objectives; i++)
        objectiveValues[i] = 0;

    this->objectives = objectives;
    dominatedBy = 0;
    dominates = 0;
}

ParetoPoint::~ParetoPoint() {
    delete[] objectiveValues;
}

int ParetoPoint::getDominatedBy() const {
    return dominatedBy;
}

int ParetoPoint::getDominates() const {
    return dominates;
}

int ParetoPoint::getObjectives() const {
    return objectives;
}

double ParetoPoint::getObjectiveValue(int objective) const {
    return objectiveValues[objective];
}

void ParetoPoint::incDominatedBy() {
    ++dominatedBy;
}

void ParetoPoint::incDominates() {
    ++dominates;
}

void ParetoPoint::setObjectiveValue(int objective, double value) {
    objectiveValues[objective] = value;
}

void ParetoPoint::print(FILE *output, bool printVars) const {
    for (int i=0; i < objectives; i++) {
        fprintf(output, "%e", objectiveValues[i]);
        if (i < objectives - 1)
            fprintf(output, "\t");
    }

    if (printVars) {
        fprintf(output, "\t%d", dominatedBy);
        fprintf(output, "\t%d", dominates);
    }
    
    fprintf(output, "\n");
}

ParetoDominance ParetoPoint::paretoCompare(const ParetoPoint *h) const {
    int score1=0, score2=0;

    /* For each objective, checks which solution wins */
    for (int i=0; i < objectives; i++) {
        if (objectiveValues[i] < h->objectiveValues[i])
            ++score1;
        else if (objectiveValues[i] > h->objectiveValues[i])
            ++score2;
    }

    /* Analyze the result */
    if (score1 == 0 && score2 == 0)
        return PARETO_EQUALS;
    else if (score1 == 0 && score2 > 0)
        return PARETO_DOMINATED;
    else if (score2 == 0 && score1 > 0)
        return PARETO_DOMINATES;
    else
        return PARETO_NOT_COMPARABLES;
}

double ParetoPoint::distanceTo(const ParetoPoint *other) {
    double result = 0.0;
    int max = objectives <= other->objectives ? objectives : other->objectives;

    for (int i = 0; i < max; i++)
        result += pow(objectiveValues[i] - other->objectiveValues[i], 2);
    result = sqrt(result);

    return result;
}
