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

#include <list>
using namespace std;

#include "HS_Operators/ParetoRanking/FastNonDominatedRanking.h"
#include "HS_Structures/Memory/Memory.h"
#include "HS_Structures/Pareto/ParetoPoint.h"

void FastNonDominatedRanking::rank(Memory *memory) {
    int *dominates = new int[memory->getSize()];
    list<int> *dominatedBy = new list<int>[memory->getSize()];
    list<int> currentFront;

    for (int i = 0; i < memory->getSize(); i++) {
        Solution *cur = memory->getSolution(i);
        for (int j = 0; j < memory->getSize(); j++) {
            Solution *other = memory->getSolution(j);
            if (cur->paretoCompare(other) == PARETO_DOMINATES)
                dominatedBy[i].push_front(j);
            else if (cur->paretoCompare(other) == PARETO_DOMINATED)
                dominates[i]++;
        }
        if (dominates[i] == 0) {
            cur->setRanking(1);
            currentFront.push_front(i);
        }
    }

    while (!currentFront.empty()) {
        for (list<int>::iterator it = currentFront.begin(); it != currentFront.end(); it = currentFront.erase(it)) {
            int i = *it;
            Solution *cur = memory->getSolution(i);
            for (list<int>::iterator it = dominatedBy[i].begin(); it != dominatedBy[i].end(); ++it) {
                int j = *it;
                Solution *other = memory->getSolution(j);

                if (--dominates[j] == 0) {
                    other->setRanking(cur->getRanking() + 1);
                    currentFront.push_front(j);
                }
            }
        }
    }

    delete[] dominates;
    delete[] dominatedBy;
}

const char *FastNonDominatedRanking::getName() {
    return "FastNonDominatedRanking";
}
