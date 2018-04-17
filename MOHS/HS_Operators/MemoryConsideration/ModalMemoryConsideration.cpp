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

#include "HS_Operators/MemoryConsideration/ModalMemoryConsideration.h"
#include "HS_Structures/Memory/ModalMemory.h"

ModalMemoryConsideration::ModalMemoryConsideration() {
    
}

ModalMemoryConsideration::~ModalMemoryConsideration() {
    
}

Variable *ModalMemoryConsideration::selectVariable(Problem *problem,
        Memory *memory, int variable, Random* random) {

    /* Randomly choose two slots from memory */
    int pos1, pos2;
    pos1 = random->boundedIntegerRandom(0, memory->getSize());
    do {
        pos2 = random->boundedIntegerRandom(0, memory->getSize());
    } while (pos1 == pos2);

    /* Choose candidate variables */
    Variable *var1 = memory->getSolution(pos1)->getVariable(variable);
    Variable *var2 = memory->getSolution(pos2)->getVariable(variable);

    /* Get mode from the given variable */
    ModalMemory *mem = (ModalMemory *) memory;
    Variable *mode = mem->getMode(variable);

    /* Compute distance from each variable to the mode */
    Variable *dist1 = var1->distanceTo(mode);
    Variable *dist2 = var2->distanceTo(mode);

    /* Select the farthest variable from the mode */
    Variable *selected;
    if (dist1->compare(dist2) > 0)
        selected = problem->getVariableBuilder()->createVariable(var1);
    else
        selected = problem->getVariableBuilder()->createVariable(var2);
    
    delete mode;
    delete dist1;
    delete dist2;

    return selected;
}

const char *ModalMemoryConsideration::getName() {
    return "ModalMemoryConsideration";
}
