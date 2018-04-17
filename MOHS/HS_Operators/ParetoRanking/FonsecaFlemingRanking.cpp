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

#include "HS_Operators/ParetoRanking/FonsecaFlemingRanking.h"

FonsecaFlemingRanking::FonsecaFlemingRanking() {

}

FonsecaFlemingRanking::~FonsecaFlemingRanking() {

}

void FonsecaFlemingRanking::rank(Memory* memory) {
    for (int i=0; i < memory->getSize(); i++) {
        int ranking = 1;
        Solution *current = memory->getSolution(i);
        for (int j=0; j < memory->getSize(); j++) {
            Solution *other = memory->getSolution(j);
            if (i != j && current->paretoCompare(other) == PARETO_DOMINATED)
                ranking = ranking + 1;
        }

        current->setRanking(ranking);
    }
}

void FonsecaFlemingRanking::rank(Memory* memory, Solution* solution) {
    /* Calculate ranking of new solution */
    int ranking = 1;
    for (int i=0; i < memory->getSize(); i++) {
        Solution *current = memory->getSolution(i);
        if (current->paretoCompare(solution) == PARETO_DOMINATES)
            ranking = ranking + 1;
    }
    solution->setRanking(ranking);

    /* Update ranking of other solutions */
    for (int i=0; i < memory->getSize(); i++) {
        Solution *current = memory->getSolution(i);
        int ranking = current->getRanking();
        if (solution->paretoCompare(current) == PARETO_DOMINATES)
            current->setRanking(ranking + 1);
    }
}

const char *FonsecaFlemingRanking::getName() {
    return "FonsecaFlemingRanking";
}
