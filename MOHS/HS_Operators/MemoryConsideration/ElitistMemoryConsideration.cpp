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

#include "HS_Operators/MemoryConsideration/ElitistMemoryConsideration.h"
#include <vector>
using namespace std;

ElitistMemoryConsideration::ElitistMemoryConsideration() {

}

ElitistMemoryConsideration::~ElitistMemoryConsideration() {

}

Variable *ElitistMemoryConsideration::selectVariable(Problem *problem,
        Memory *memory, int variable, Random *random) {

    /* Search which solution has the lowest ranking */
    int minRank = memory->getSolution(0)->getRanking();
    for (int i=1; i < memory->getSize(); i++) {
        int rank = memory->getSolution(i)->getRanking();
        if (rank < minRank)
            minRank = rank;
    }

    /* Choose the two with the best ranking */
    vector<Solution *> betters;
    for (int i=0; i < memory->getSize(); i++) {
        Solution *sol = memory->getSolution(i);
        if (sol->getRanking() == minRank)
            betters.push_back(sol);
    }

    /* Randomly choose between one of the best */
    int pos = random->boundedIntegerRandom(0, betters.size());
    Solution *sol = betters[pos];
    Variable *selected = sol->getVariable(variable);
    Variable *result = problem->getVariableBuilder()->createVariable(selected);
    return result;
}

const char *ElitistMemoryConsideration::getName() {
    return "ElitistMemoryConsideration";
}
