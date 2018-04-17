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

#include "HS_Structures/Memory/MemoryBuilder/SimpleMemoryBuilder.h"

SimpleMemoryBuilder::SimpleMemoryBuilder() {
    
}

SimpleMemoryBuilder::~SimpleMemoryBuilder() {
    
}

Memory *SimpleMemoryBuilder::createMemory(int size, Problem *problem) {
    return new Memory(size);
}

const char *SimpleMemoryBuilder::getName() {
    return "SimpleMemoryBuilder";
}
