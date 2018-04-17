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

#ifndef BINARYMODALMEMORY_H
#define	BINARYMODALMEMORY_H

#include "HS_Structures/Memory/ModalMemory.h"

class BinaryModalMemory : public ModalMemory {
private:
    /* Location function (hashing) */
    int findBarPos(int variable, Variable *value);

public:
    /** Constructor */
    BinaryModalMemory(int size, Problem *problem);

    /** Destructor */
    virtual ~BinaryModalMemory();

    /** Calculates the mode when the memory has been initialized */
    void calculateMode();

    /** Calculates the mode of a given variable */
    Variable *getMode(int variable);

    /** Updates the mode of a given variable */
    void updateMode(int variable, Variable *value, bool increment);
};

#endif	/* BINARYMODALMEMORY_H */
