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

#ifndef SOLUTION_H
#define	SOLUTION_H

#include "Variable/Variable.h"
#include "VariableBuilder/VariableBuilder.h"
#include "HS_Structures/Pareto/ParetoPoint.h"
#include <cstdio>

/**
 * Datatype for the result of comparing
 * two solutions.
 */
typedef enum {
    BETTER,
    EQUAL,
    WORSE
} Comparison;

class Solution : public ParetoPoint {
private:
    /* Harmony variables */
    Variable **variables;

    /* Variable count */
    int size;

    /* Pareto ranking of the solution */
    int ranking;
    
public:
    /* Constructor */
    Solution(int size, int objectives);

    /* Destructor */
    virtual ~Solution();

    /* Getters */
    Variable *getVariable(int i) const;
    Variable **getVariables() const;
    int getSize() const;
    int getRanking() const;
    
    /* Setters */
    void setVariable(int i, Variable *value);
    void setRanking(int value);
    
    /** Prints the solution */
    void print(FILE *output, bool printVars) const;

    /**
     * Compares this solution against other one
     * considering the ranking of each one.
     */
    Comparison compare(const Solution *h) const;

    /**
     * Equality operator. The comparison is made
     * with decision variables.
     */
    bool equals(const Solution *h) const;

    /**
     * Clones this solution.
     */
    Solution* clone(VariableBuilder *varBuilder);
};

#endif	/* SOLUTION_H */
