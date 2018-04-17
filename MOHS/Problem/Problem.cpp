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

#include "Problem/Problem.h"

Problem::Problem(VariableBuilder* varBuilder) {
    this->varBuilder = varBuilder;
}

Problem::~Problem() {
    delete varBuilder;
}

int Problem::getSize() const {
    return size;
}

int Problem::getObjectives() const {
    return objectives;
}

Variable *Problem::getMaximum(int i) const {
    return maximum[i];
}

Variable *Problem::getMinimum(int i) const {
    return minimum[i];
}

Variable *Problem::getFretWidth(int i) const {
    return fretWidth[i];
}

VariableBuilder *Problem::getVariableBuilder() const {
    return varBuilder;
}

ParetoSet *Problem::optimalParetoFront2D(double f1min, double f1max, double epsilon) {
    ParetoSet *ps = new ParetoSet();

    /* Add first outermost point */
    ParetoPoint *p1 = new ParetoPoint(2);
    p1->setObjectiveValue(0, f1min);
    p1->setObjectiveValue(1, paretoOrdinate(f1min));
    ps->nonDominatedAdd(p1);

    /* Add second outermost point */
    ParetoPoint *p2 = new ParetoPoint(2);
    p2->setObjectiveValue(0, f1max);
    p2->setObjectiveValue(1, paretoOrdinate(f1max));
    ps->nonDominatedAdd(p2);

    /* Add middle points */
    f1min += epsilon;
    while (f1min < f1max) {
        ParetoPoint *p = new ParetoPoint(2);

        p->setObjectiveValue(0, f1min);
        p->setObjectiveValue(1, paretoOrdinate(f1min));

        ps->nonDominatedAdd(p);

        f1min += epsilon;
    }

    return ps;
}
