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

#ifndef VARIABLE_H
#define	VARIABLE_H

#include <cstdio>
#include <cmath>

class Variable {
public:
    /** Virtual destructor. */
    virtual ~Variable() = 0;

    /** Prints the variable. */
    virtual void print(FILE *output) = 0;

    /** Compare the given variable with this variable. */
    virtual int compare(const Variable *other) = 0;

    /**
     * Returns the distance between the given
     * variable and this variable.
     */
    virtual Variable *distanceTo(const Variable *other) = 0;

    /** Returns the name of the variable. */
    virtual const char *getName() = 0;
};

#endif
