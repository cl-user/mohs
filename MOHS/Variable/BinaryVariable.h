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

#ifndef BINARYVARIABLE_H
#define	BINARYVARIABLE_H

#include "Variable/Variable.h"

class BinaryVariable : public Variable {
private:
    /* Value of this binary variable */
    unsigned int length;

public:
    /** Constructor. */
    BinaryVariable(unsigned int length);
    virtual ~BinaryVariable() = 0;
    /** Returns the bit at the given position. */
    virtual char getBit(unsigned int position) = 0;
    /** Set the bit at the given position. */
    virtual void setBit(char bit, unsigned int position) = 0;
    /** Returns the number of bits equal to 1. */
    virtual unsigned int countBitsSet(void) = 0;
    /** Returns the length of this binary variable. */
    unsigned int getLength(void);
};

#endif
