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

#include "HS_Structures/Memory/ModalMemory.h"
#include "HS_Operators/MemoryUpdate/ModalMemoryUpdate.h"

ModalMemoryUpdate::ModalMemoryUpdate() {
    
}

ModalMemoryUpdate::~ModalMemoryUpdate() {
    
}

void ModalMemoryUpdate::update(Problem *problem, Memory* memory, Solution* solution) {
    if (!memory->includes(solution)) {
        ModalMemory *mem = (ModalMemory *) memory;
	int worstPos     = this->getWorst(memory);
	Solution *worst  = mem->getSolution(worstPos);
        Solution *sol    = solution->clone(problem->getVariableBuilder());
    
	/*
         * Replace the less ranking solution in
         * memory if it is worse or equal than "sol".
         */
	if (sol->compare(worst) == WORSE)
            delete sol;
	else {
            /* Update mode */
            for (int i=0; i < worst->getSize(); i++)
                mem->updateMode(i, worst->getVariable(i), false);

            for (int i=0; i < sol->getSize(); i++)
                mem->updateMode(i, sol->getVariable(i), true);
	      
            mem->setSolution(worstPos, sol);
	}
    }
}

const char *ModalMemoryUpdate::getName() {
    return "ModalMemoryUpdate";
}
