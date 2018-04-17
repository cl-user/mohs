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

#include "HS_Operators/MemoryConsideration/SimpleMemoryConsideration.h"

SimpleMemoryConsideration::SimpleMemoryConsideration() {

}

SimpleMemoryConsideration::~SimpleMemoryConsideration() {

}

Variable *SimpleMemoryConsideration::selectVariable(Problem *problem, 
        Memory *memory, int variable, Random* random) {
    
    /* Randomly choose one slot from memory */
    int pos = random->boundedIntegerRandom(0, memory->getSize());

    /* Get the variable corresponding to the chosen solution */
    Variable *selected = memory->getSolution(pos)->getVariable(variable);

    /* Copy the selected variable */
    Variable *result = problem->getVariableBuilder()->createVariable(selected);
    return result;
}

const char *SimpleMemoryConsideration::getName() {
    return "SimpleMemoryConsideration";
}
