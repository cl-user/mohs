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

#include "HS_Operators/MemoryInit/SimpleMemoryInit.h"

SimpleMemoryInit::SimpleMemoryInit() {
    
}

SimpleMemoryInit::~SimpleMemoryInit() {
    
}

void SimpleMemoryInit::initialize(Memory* memory, Problem *problem, Random* random) {
    /*
     * Create random solutions, calculate its'
     * ranking and add them to the memory.
     */
    for (int i=0; i < memory->getSize(); i++) {
        Solution *sol = new Solution(problem->getSize(), problem->getObjectives());

        /* Generate a random solution */
        for (int j=0; j < sol->getSize(); j++) {
            Variable *min   = problem->getMinimum(j);
            Variable *max   = problem->getMaximum(j);
            Variable *value = problem->getVariableBuilder()->createVariable(min, max, random);
            sol->setVariable(j, value);
        }

        /* Evaluate solution */
        problem->evaluate(sol);

        /* Add solution to memory */
        if (!memory->includes(sol))
            memory->setSolution(i, sol);
        else {
            --i;
            delete sol;
        }
    }
}

const char *SimpleMemoryInit::getName() {
    return "SimpleMemoryInit";
}
