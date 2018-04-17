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

#ifndef SIMPLEMEMORYCONSIDERATION_H
#define	SIMPLEMEMORYCONSIDERATION_H

#include "HS_Operators/MemoryConsideration/MemoryConsideration.h"

class SimpleMemoryConsideration : public MemoryConsideration {
public:
    SimpleMemoryConsideration();
    virtual ~SimpleMemoryConsideration();
    Variable *selectVariable(Problem *problem, Memory *memory, int variable, Random *random);
    const char *getName();
};

#endif	/* SIMPLEMEMORYCONSIDERATION_H */
