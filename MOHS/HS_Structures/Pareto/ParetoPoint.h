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

#ifndef PARETOPOINT_H
#define	PARETOPOINT_H

#include <cstdio>

/**
 * Datatype for the result of comparing
 * two solutions considering Pareto dominance.
 */
typedef enum {
    PARETO_EQUALS,
    PARETO_DOMINATES,
    PARETO_DOMINATED,
    PARETO_NOT_COMPARABLES
} ParetoDominance;

class ParetoPoint {
protected:
    /* Number of solutions that dominate this solution */
    int dominatedBy;

    /* Number of solutions dominated by this solution */
    int dominates;

    /* Number of objectives */
    int objectives;

    /* Objectives */
    double *objectiveValues;
    
public:
    /** Constructor */
    ParetoPoint(int objectives);

    /** Destructor */
    virtual ~ParetoPoint();

    /* Getters */
    int getDominatedBy() const;
    int getDominates() const;
    int getObjectives() const;
    double getObjectiveValue(int objective) const;

    /* Setters */
    void incDominatedBy();
    void incDominates();
    void setObjectiveValue(int objective, double value);

    /** Prints the Pareto point */
    virtual void print(FILE *output, bool printVars) const;

    /**
     * Compares a ParetoPoint object (p2) with the
     * current one (p1), considering Pareto dominance.
     *
     * For each objective checks which point wins,
     * scoring each one.
     * Finally, decision is taken according to the
     * total score for each one:
     *  (1) 0-0 : equals
     *  (2) W-0 : p1 dominates p2
     *  (3) 0-X : p1 is dominated by p2
     *  (4) Y-Z : p1 and p2 are not comparables
     *
     * where W, X, Y, Z are integers greater than zero.
     */
    ParetoDominance paretoCompare(const ParetoPoint *p) const;

    /**
     * Returns the euclidean distance to another point.
     */
    double distanceTo(const ParetoPoint *other);
};

#endif	/* PARETOPOINT_H */
