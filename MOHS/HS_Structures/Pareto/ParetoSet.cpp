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

#include "HS_Structures/Pareto/ParetoPointList.h"
#include "HS_Structures/Pareto/ParetoSet.h"
#include "Utils/Random.h"

#include <map>
using namespace std;

#include <cmath>
#include <cstdlib>

ParetoSet::ParetoSet() {
    start = NULL;
    size  = 0;
}

ParetoSet::~ParetoSet() {
    while (start != NULL) {
        node *tmp = start->link;
        delete start->data;
        delete start;
        start = tmp;
    }
}

int ParetoSet::getSize() const {
    return size;
}

bool ParetoSet::includes(const ParetoPoint *p) const {
    for (node *it = start; it != NULL; it = it->link)
        if (p->paretoCompare(it->data) == PARETO_EQUALS)
            return true;

    return false;
}

int ParetoSet::nonDominatedAdd(ParetoPoint *p) {
    int count = 0;
    node *prev = NULL;
    node *it = start;
    while (it != NULL) {
        int cmpResult = p->paretoCompare(it->data);

        if (cmpResult == PARETO_DOMINATED) {
            /* Point is dominated, return */
            delete p;
            return -1;
        }
        else if (cmpResult == PARETO_DOMINATES) {
            /* Remove dominated */
            it = iterationRemove(it, prev);
            ++count;
        }
        else {
            /* Iterate to the next */
            prev = it;
            it = it->link;
        }
    }

    /* Add point and update size */
    this->add(p);
    size -= count;
    return count;
}

void ParetoSet::add(ParetoPoint *p) {
    node *tmp = new node;
    tmp->data = p;
    tmp->link = start;

    start = tmp;
    ++size;
}

void ParetoSet::begin() {
    current = start;
}

bool ParetoSet::hasNext() {
    if (current == NULL)
        return false;
    else
        return true;
}

ParetoPoint *ParetoSet::getNext() {
    ParetoPoint *p = current->data;
    current = current->link;
    return p;
}

bool ParetoSet::isDominated(ParetoPoint *p) const {
    for (node *it = start; it != NULL; it = it->link)
        if (it->data->paretoCompare(p) == PARETO_DOMINATES)
            return true;

    return false;
}

int ParetoSet::removeDominated() {
    int count = 0;
    node *prev = NULL;
    node *it = start;
    while (it != NULL) {
        if (isDominated(it->data)) {
            /* Remove dominated */
            it = iterationRemove(it, prev);
            ++count;
        }
        else {
            /* Iterate to the next */
            prev = it;
            it = it->link;
        }
    }

    size -= count;
    return count;
}

void ParetoSet::detachPoints() {
    while (start != NULL) {
        node *tmp = start->link;
        delete start;
        start = tmp;
    }
    size = 0;
}

void ParetoSet::print(FILE* output, bool printVars, bool printCounter) const {
    node *it = start;
    for (int i=0; i < size; i++) {
        if (printCounter)
            fprintf(output, "%3d: ", i);
        
        it->data->print(output, printVars);
        fflush(output);
        it = it->link;
    }
}

void ParetoSet::findAndRemove(ParetoPoint *p) {
    node *prev;
    node *cur = start;

    while (cur != NULL && cur->data != p) {
        prev = cur;
        cur = cur->link;
    }

    if (cur != NULL) {
        if (cur == start)
            start = cur->link;
        else
            prev->link = cur->link;

        delete cur->data;
        delete cur;
        size--;
    }
}

ParetoSet::node *ParetoSet::iterationRemove(node *it, node *prev) {
    if (it == start) {
        node *tmp = it;
        it = it->link;
        start = it;
        delete tmp->data;
        delete tmp;
    }
    else {
        node *tmp = it;
        it = it->link;
        prev->link = it;
        delete tmp->data;
        delete tmp;
    }

    return it;
}

void ParetoSet::truncate(const unsigned int limit) {
    /*
     * Each list in ``neighbors'' is partially ordered so that for a list L, the
     * solutions in the range [L.begin(), x) are ordered by the distance to the
     * corresponding solution and the solutions in the range [orderedFrontier,
     * L.end()) are not ordered.
     */
    typedef map<ParetoPoint *, ParetoPointList *> ParetoPoints;
    ParetoPoints neighbors;

    if (size <= limit)
        return;

    for (node *orig = start; orig != NULL; orig = orig->link)
        neighbors[orig->data] = new ParetoPointList(orig->data, this);

    while (size > limit) {
        ParetoPoints candidates;

        /*
         * At the beginning, all solutions are candidates to be removed from the
	 * Pareto Front.
         */
        ParetoPoints::iterator it;
        for (it = neighbors.begin(); it != neighbors.end(); ++it) {
            candidates[it->first] = it->second;
            candidates[it->first]->begin();
        }

        /*
	 * Succesively consider the set of solutions with the k-nearest
	 * neighbor, denoted by ``candidates'' until it is represented by a
	 * single solution or until all neighbors have been visited. At the end
	 * of the loop, ``candidates'' represents all candidate solutions to be
	 * removed from the Pareto Front.
         */
        while (candidates.size() > 1) {
            ParetoPoints newCandidates;
            ParetoPoints::iterator other = candidates.begin();
            ParetoPointList *min = other->second;

            /*
	     * Store all solutions with minimum distance to their k-nearest
	     * neighbor in a new set of candidates to be removed.
             */
            for (; other != candidates.end(); ++other) {
                if (other->second->getDistance() < min->getDistance()) {
                    newCandidates.clear();
                    newCandidates[other->first] = other->second;
                    min = other->second;
                }
                else if (other->second->getDistance() == min->getDistance())
                    newCandidates[other->first] = other->second;
            }

            if (newCandidates.size() > 1 && min->hasNext()) {
                for (ParetoPoints::iterator it = newCandidates.begin(); it != newCandidates.end(); ++it)
                    it->second->next();

                candidates = newCandidates;
            }
            else {
                candidates = newCandidates;
                break;
            }
        }

        /* Randomly choose a solution from the set of candidate solutions. */
        Random *rand = new Random();
        unsigned int pos = rand->boundedIntegerRandom(0, candidates.size());
        delete rand;

        it = candidates.begin();
        for (unsigned int i = 0; i < pos; i++)
            it++;
        ParetoPoint *selected = it->first;

	/* Remove the neighbors list of the chosen solution */
        delete neighbors[selected];
        neighbors.erase(selected);

        for (ParetoPoints::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
            it->second->findAndRemove(selected);

	/* Remove the chosen solution from the Pareto Set. */
        this->findAndRemove(selected);

	/* Clean the set of candidate solutions. */
        candidates.clear();
    }

    for (ParetoPoints::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
        delete it->second;
}

double ParetoSet::metricM1(ParetoSet *yTrue) {
    /* If either front is empty, returns -1 */
    if (this->size == 0 || yTrue->size == 0)
        return -1;

    double sum = 0;
    for (node *p = this->start; p != NULL; p = p->link) {
        node *q = yTrue->start;
        double minDist = p->data->distanceTo(q->data);

        for (q = q->link; q != NULL; q = q->link) {
            double dist = p->data->distanceTo(q->data);
            if (dist < minDist)
                minDist = dist;
        }

        sum += minDist;
    }

    double m1 = sum / this->size;
    return m1;
}

double ParetoSet::metricM2() {
    /* If the front is empty, returns -1 */
    if (this->size == 0)
        return -1;

    /*
     * Calculates sigma as 10% of the distance
     * between the two outer points of the front.
     * That is, the maximum distance between two
     * given points of the front.
     */
    double maxDist = 0;
    for (node *p = this->start; p != NULL; p = p->link) {
        for (node *q = this->start; q != NULL; q = q->link) {
            double dist = p->data->distanceTo(q->data);
            if (dist > maxDist)
                maxDist = dist;
        }
    }

    /* Sigma as 10% */
    double sigma = maxDist * 0.1;

    /* Calculate the metric */
    int sum = 0;
    for (node *p = this->start; p != NULL; p = p->link) {
        int w = 0;
        for (node *q = this->start; q != NULL; q = q->link) {
            if (p->data->distanceTo(q->data) > sigma)
                ++w;
        }

        sum += w;
    }

    double m2 = ((double) sum) / (this->size - 1);
    return m2;
}

double ParetoSet::metricM3() {
    /* If the front is empty, returns -1 */
    if (this->size == 0)
        return -1;

    /* Problem's objective number */
    int objectives = this->start->data->getObjectives();

    /* Calculates minimum and maximun for each objective */
    double *min = new double[objectives];
    double *max = new double[objectives];
    for (int i=0; i < objectives; i++) {
        min[i] = this->start->data->getObjectiveValue(i);
        max[i] = this->start->data->getObjectiveValue(i);
    }

    for (node *p = start->link; p != NULL; p = p->link) {
        for (int i=0; i < objectives; i++) {
            double value = p->data->getObjectiveValue(i);

            if (value > max[i])
                max[i] = value;

            if (value < min[i])
                min[i] = value;
        }
    }

    /* Calculate sum of the differences */
    double sum = 0;
    for (int i=0; i < objectives; i++)
        sum += fabs(max[i] - min[i]);

    delete[] min;
    delete[] max;

    double m3 = sqrt(sum);
    return m3;
}

double ParetoSet::metricError(ParetoSet *yTrue) {
    /* If either front is empty, returns -1 */
    if (this->size == 0 || yTrue->size == 0)
        return -1;

    int sum = 0;
    for (node *p = this->start; p != NULL; p = p->link) {
        if (!yTrue->includes(p->data))
            sum += 1;
    }

    double error = ((double) sum) / this->size;
    return error;
}

void ParetoSet::printNonDominated(FILE *output, bool printVars, bool printCounter) const {
    this->print(output, printVars, printCounter);
}

int ParetoSet::getNonDominatedSize() const {
    return this->getSize();
}
