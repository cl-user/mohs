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

#ifndef MEMORY_H
#define	MEMORY_H

#include "HS_Structures/Solution.h"
#include "HS_Structures/NonDominatedSet.h"

class Memory : public NonDominatedSet {
protected:
    Solution **hm;
    int size;

public:
    /** Constructor. */
    Memory(int size);

    /** Destructor. */
    virtual ~Memory();

    /** Gets a memory solution. */
    Solution* getSolution(int i) const;

    /** Gets memory size. */
    int getSize() const;

    /** Replaces a solution. */
    void setSolution(int i, Solution *h);

    /**
     * Checks if the memory already includes
     * the given solution. Comparison is made
     * considering the decision space.
     */
    bool includes(const Solution *h) const;

    /**
     * Gets an array with i-th variables of
     * each memory solution.
     */
    Variable **getVariables(int i) const;

    /** Prints the memory. */
    void print(FILE *output, bool printVars, bool printCounter) const;

    /** Indicates if the memory have converged (all non-dominated solutions) */
    bool converged() const;

    /** Detaches all memory solutions. */
    void detachSolutions();

    /** Detaches a given solution from the memory. */
    Solution *detach(int i);

    /** Removes all solutions. */
    void clear();

    /**
     * Calculates percentage of n-distant solutions
     * to given solution.
     * Two solutions are n-distant if the distance
     * between them is equal or greater than a given
     * percentage "n".
     */
    double nDiff(const Solution *sol, double n, double max) const;

    /*
     * Inherited methods of NonDominatedSet
     */
    void printNonDominated(FILE *output, bool printVars, bool printCounter) const;
    int getNonDominatedSize() const;
};

#endif	/* MEMORY_H */
