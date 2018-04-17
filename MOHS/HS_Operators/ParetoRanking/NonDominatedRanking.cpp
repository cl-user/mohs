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

#include "HS_Operators/ParetoRanking/NonDominatedRanking.h"

NonDominatedRanking::NonDominatedRanking() {

}

NonDominatedRanking::~NonDominatedRanking() {

}

void NonDominatedRanking::swap(Solution *population[], unsigned int i, unsigned int j) {
    Solution *temp;

    temp = population[i];
    population[i] = population[j];
    population[j] = temp;
}

int NonDominatedRanking::sort(Solution *population[], unsigned int start, unsigned int count) {
    int nextAvailable = start;

    for (int i = start; i < count; i++) {
        Solution *cur = population[i];
        for (int j = start; j < count; j++) {
            Solution *other = population[j];
            if (cur != other && cur->paretoCompare(other) == PARETO_DOMINATED) {
                swap(population, i, nextAvailable);
                nextAvailable++;
                break;
            }
        }
    }

    /*
     * count = number of elements to sort
     * nextAvailable - start = number of dominated solutions
     */
    return count - (nextAvailable - start);
}


void NonDominatedRanking::rank(Memory* memory) {
    Solution **population = new Solution*[memory->getSize()];
    unsigned int rank = 0;
    unsigned int begin = 0;
    unsigned int count = memory->getSize();
    unsigned int nonDominatedCount = memory->getSize();

    for (int i = 0; i < memory->getSize(); i++)
        population[i] = memory->getSolution(i);

    while (count > 0) {
        rank++;
        nonDominatedCount = sort(population, begin, count);
        for (int i = count - nonDominatedCount; i < count; i++)
            population[i]->setRanking(rank);
        count -= nonDominatedCount;
    }

    delete[] population;
}

void NonDominatedRanking::rank(Memory *memory, Solution *solution) {
    Solution *other;
    unsigned int cmp;

    /* At the beginning we assume than "solution" is the the first front */
    solution->setRanking(1);

    /* Find the front to which "solution" belongs */
    for (int i = 0; i < memory->getSize(); i++) {
        other = memory->getSolution(i);
        cmp = solution->paretoCompare(other);
        if (cmp == PARETO_DOMINATED && solution->getRanking() <= other->getRanking())
            solution->setRanking(other->getRanking() + 1);
    }

    /*
     * All solutions that are in the same front of "solution" or
     * in a previous front, but are dominated by "solution" are
     * moved to the next front.
     */
    for (int i = 0; i < memory->getSize(); i++) {
        other = memory->getSolution(i);
        cmp = solution->paretoCompare(other);
        if (cmp == PARETO_DOMINATES && solution->getRanking() >= other->getRanking())
            other->setRanking(solution->getRanking() + 1);
    }
}

const char *NonDominatedRanking::getName() {
    return "NonDominatedRanking";
}
