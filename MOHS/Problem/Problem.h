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

#ifndef PROBLEM_H
#define	PROBLEM_H

#include "HS_Structures/Solution.h"
#include "VariableBuilder/VariableBuilder.h"
#include "HS_Structures/Pareto/ParetoSet.h"

class Problem {
protected:
    /* Problem size (number of variables) */
    int size;

    /* Pareto front size (number of points) */
    int pfsize;

    /* Number of problem objectives */
    int objectives;

    /* Variables upper bounds */
    Variable **maximum;

    /* Variables lower bounds */
    Variable **minimum;

    /* Variation range of a variable in pitch adjust */
    Variable **fretWidth;

    /* Variable builder */
    VariableBuilder *varBuilder;

    /* Optimal Pareto front computation (bi-objective case) */
    ParetoSet *optimalParetoFront2D(double f1min, double f1max, double epsilon);

    /*
     * Calculate the ordinate of a Pareto front's point
     * given the abscissa.
     */
    virtual double paretoOrdinate(double f1) = 0;

public:
    /** Constructor. */
    Problem(VariableBuilder *varBuilder);

    /** Destructor. */
    virtual ~Problem() = 0;

    /** Returns the problem size. */
    int getSize() const;

    /** Returns the number of objectives. */
    int getObjectives() const;

    /** Returns the upper bound for i-th variable. */
    Variable *getMaximum(int i) const;

    /** Returns the lower bound for i-th variable. */
    Variable *getMinimum(int i) const;

    /** Returns the variable variation range for pitch adjust. */
    Variable *getFretWidth(int i) const;

    /** Returns the variable builder. */
    VariableBuilder *getVariableBuilder() const;

    /** Optimal Pareto front computation. */
    virtual ParetoSet *optimalParetoFront() = 0;

    /** Evaluation function. */
    virtual void evaluate(Solution *h) = 0;

    virtual double getMaxDistance() const = 0;

    /** Problem name. */
    virtual const char *getName() = 0;
};

#endif	/* PROBLEM_H */
