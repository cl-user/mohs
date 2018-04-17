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

#ifndef MEMORYINIT_H
#define	MEMORYINIT_H

#include "HS_Structures/Memory/Memory.h"
#include "Utils/Random.h"
#include "Problem/Problem.h"

class MemoryInit {
public:
    /** Virtual destructor. */
    virtual ~MemoryInit() = 0;

    /** Memory initialization. */
    virtual void initialize(Memory *memory, Problem *problem, Random *random) = 0;

    /** Returns the algorithm name. */
    virtual const char *getName() = 0;
};

#endif	/* MEMORYINIT_H */

