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

#ifndef MEMORYUPDATE_H
#define	MEMORYUPDATE_H

#include "HS_Structures/Memory/Memory.h"
#include "HS_Structures/Solution.h"
#include "Problem/Problem.h"

class MemoryUpdate {
public:
    /** Virtual destructor. */
    virtual ~MemoryUpdate() = 0;

    /**
     * Memory update. Returns true if the memory have been
     * updated by the given solution.
     */
    virtual void update(Problem *problem, Memory *memory, Solution *solution) = 0;

    /** Returns the algorithm name. */
    virtual const char *getName() = 0;
};

#endif	/* MEMORYUPDATE_H */
