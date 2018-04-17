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

#ifndef PARETOSET_H
#define	PARETOSET_H

#include <list>
using namespace std;

#include "HS_Structures/Pareto/ParetoPoint.h"
#include "HS_Structures/NonDominatedSet.h"

class ParetoSet : public NonDominatedSet {
private:
    /* 
     * Datatype representing a node of the linked
     * list used to represent the Pareto set.
     */
    struct node {
        ParetoPoint *data;
        node *link;
    } *start, *current;

    /* Size of the Pareto set */
    int size;

    /* Checks if a point is dominated */
    bool isDominated(ParetoPoint *p) const;

    /* Find and remove a point of the set */
    void findAndRemove(ParetoPoint *p);

    /*
     * Removes a node, updates links and returns
     * next node (NULL if the removed one was
     * the last one).
     */
    node *iterationRemove(node *it, node *prev);

public:
    /** Constructor */
    ParetoSet();

    /** Destructor */
    virtual ~ParetoSet();

    /** Get the size of the Pareto set */
    int getSize() const;

    /**
     * Checks if the set includes the current
     * point. Comparison is made considering
     * objective space.
     */
    bool includes(const ParetoPoint *p) const;

    /**
     * Adds a point to the set if is non-dominated
     * and removes the points dominated by it.
     *
     * Returns a negative number if the point is
     * not added; zero if the point is added and
     * any other point is removed; a positive
     * number if the point is added and some points
     * are removed, being this value the number of
     * removed points.
     */
    int nonDominatedAdd(ParetoPoint *p);

    /**
     * Adds a new point to the set.
     */
    void add(ParetoPoint *p);

    /**
     * Initializes internal state to
     * iterate the set.
     */
    void begin();

    /**
     * Returns the next element during
     * iteration state.
     */
    ParetoPoint *getNext();

    /**
     * Checks if is there more elements
     * to iterate during iteration state.
     */
    bool hasNext();

    /**
     * Removes dominated points, returning
     * the number of removed ones.
     */
    int removeDominated();

    /** Detaches all solutions from the memory */
    void detachPoints();

    /** Prints the Pareto set */
    void print(FILE *output, bool printVars, bool printCounter) const;

    /** Successively removes solutions until the specified limit is reached */
    void truncate(const unsigned int limit);

    /**
     * Metric of distance to optimal Pareto front.
     *
     * Returns a negative number is either front is empty.
     */
    double metricM1(ParetoSet *yTrue);

    /**
     * Metric of distribution.
     *
     * Returns a negative number if the front is empty.
     */
    double metricM2();

    /**
     * Metric of extension.
     *
     * Returns a negative number if the front is empty.
     */
    double metricM3();

    /**
     * Metric of error.
     *
     * Return a negative number if either front is empty.
     */
    double metricError(ParetoSet *yTrue);

    /*
     * Inherited methods of NonDominatedSet
     */
    void printNonDominated(FILE *output, bool printVars, bool printCounter) const;
    int getNonDominatedSize() const;
};

#endif	/* PARETOSET_H */
