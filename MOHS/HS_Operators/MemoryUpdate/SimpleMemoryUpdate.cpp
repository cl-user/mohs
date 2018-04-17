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

#include "HS_Operators/MemoryUpdate/SimpleMemoryUpdate.h"

SimpleMemoryUpdate::SimpleMemoryUpdate() {
    
}

SimpleMemoryUpdate::~SimpleMemoryUpdate() {
    
}

void SimpleMemoryUpdate::update(Problem *problem, Memory* memory, Solution* solution) {
    if (!memory->includes(solution)) {
        Solution *sol = solution->clone(problem->getVariableBuilder());
	int worstPos = getWorst(memory);
    
        /* Replace worst solution if "sol" is better */
	if (sol->compare(memory->getSolution(worstPos)) == WORSE)
            delete sol;
	else
            memory->setSolution(worstPos, sol);
    }
}

int SimpleMemoryUpdate::getWorst(Memory *memory) {
    int worstPos = 0;

    for (int i=1; i < memory->getSize(); i++) {
        Solution *aux = memory->getSolution(i);
        if (aux->compare(memory->getSolution(worstPos)) == WORSE)
            worstPos = i;
    }

    return worstPos;
}
 
const char *SimpleMemoryUpdate::getName() {
    return "SimpleMemoryUpdate";
}
