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

#ifndef VARIABLEBUILDER_H
#define	VARIABLEBUILDER_H

#include "Variable/Variable.h"
#include "Utils/Random.h"

class VariableBuilder {
public:
    /** Virtual destructor. */
    virtual ~VariableBuilder() = 0;
    
    /** Creates a random variable between specified range. */
    virtual Variable *createVariable(Variable *min, Variable *max, Random *random) = 0;

    /** Creates a copy of the specified variable parameter. */
    virtual Variable *createVariable(Variable *value) = 0;

    /**
     * Creates a new variable resulting from the sum
     * of two given variables.
     */
    virtual Variable *addVariables(Variable *a, Variable *b) = 0;

    /**
     * Creates a new variable resulting from the subtraction
     * of two given variables.
     */
    virtual Variable *substractVariables(Variable *a, Variable *b) = 0;

    /** Get the name of the variable builder. */
    virtual const char *getName() = 0;
};

#endif	/* VARIABLEBUILDER_H */
