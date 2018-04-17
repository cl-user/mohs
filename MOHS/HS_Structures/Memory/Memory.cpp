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

#include "HS_Structures/Memory/Memory.h"

Memory::Memory(int size) {
    hm = new Solution*[size];
    this->size = size;
    for (int i=0; i < size; i++)
        hm[i] = NULL;
}

Memory::~Memory() {
    this->clear();
    delete[] hm;
}

Solution* Memory::getSolution(int i) const {
    return hm[i];
}

int Memory::getSize() const {
    return size;
}

void Memory::setSolution(int i, Solution *h) {
    if (hm[i] != NULL)
        delete hm[i];

    hm[i] = h;
}

bool Memory::includes(const Solution *h) const {
    for (int i=0; i < size; i++)
        if (h->equals(hm[i]))
            return true;

    return false;
}

Variable **Memory::getVariables(int i) const {
    Variable **var = new Variable*[size];
    for (int k=0; k < size; k++)
        var[k] = hm[k]->getVariable(i);

    return var;
}

void Memory::print(FILE* output, bool printVars, bool printCounter) const {
    for (int i=0; i < size; i++) {
        if (printCounter)
            fprintf(output, "%3d: ", i);
        
        hm[i]->print(output, printVars);
    }
}

bool Memory::converged() const {
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
            if (hm[i]->paretoCompare(hm[j]) != PARETO_NOT_COMPARABLES)
                return false;

    return true;
}

void Memory::detachSolutions() {
    for (int i=0; i < size; i++)
        hm[i] = NULL;
}

Solution *Memory::detach(int i) {
    Solution *result = hm[i];
    hm[i] = NULL;
    return result;
}

void Memory::clear() {
    for (int i=0; i < size; i++)
        delete hm[i];
}

double Memory::nDiff(const Solution* sol, double n, double max) const {
    int count = 0;
    for (int i=0; i < size; i++) {
        double dist = hm[i]->distanceTo(sol);
        if (dist / max >= n)
            ++count;
    }

    return count / ((double) size);
}

void Memory::printNonDominated(FILE *output, bool printVars, bool printCounter) const {
    for (int i=0; i < size; i++) {
        if (printCounter)
            fprintf(output, "%3d: ", i);

        if (hm[i]->getRanking() == 1)
            hm[i]->print(output, printVars);
    }
}

int Memory::getNonDominatedSize() const {
    int count = 0;
    
    for (int i=0; i < size; i++)
        if (hm[i]->getRanking() == 1)
            ++count;

    return count;
}
