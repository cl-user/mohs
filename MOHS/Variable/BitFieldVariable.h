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

#ifndef BITFIELDVARIABLE_H
#define	BITFIELDVARIABLE_H

#include "Variable/BinaryVariable.h"
#include <stdint.h>
#include <cstdio>

class BitFieldVariable : public BinaryVariable {
private:
    /* Value of this bit field variable */
    int32_t value;

public:
    /** Constructor. */
    BitFieldVariable(unsigned int length);
    /** Constructor. */
    BitFieldVariable(int32_t value, unsigned int length);
    ~BitFieldVariable();
    void print(FILE *output);
    int compare(const Variable *other);
    Variable *distanceTo(const Variable *other);
    /** Returns the value of this bit field variable. */
    int32_t getValue(void);
    const char *getName();
    char getBit(unsigned int position);
    void setBit(char bit, unsigned int position);
    unsigned int countBitsSet(void);
};

#endif
