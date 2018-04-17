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

#include "HS_Operators/MemoryInit/ModalMemoryInit.h"
#include "HS_Structures/Memory/ModalMemory.h"

ModalMemoryInit::ModalMemoryInit() {
    
}

ModalMemoryInit::~ModalMemoryInit() {
    
}

void ModalMemoryInit::initialize(Memory *memory, Problem *problem, Random *random) {
    /* Fill the memory */
    SimpleMemoryInit::initialize(memory, problem, random);

    /* Calculate mode for each variable */
    ModalMemory *mem = (ModalMemory *) memory;
    mem->calculateMode();
}

const char *ModalMemoryInit::getName() {
    return "ModalMemoryInit";
}
