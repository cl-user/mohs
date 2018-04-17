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

#ifndef INTEGERVARIABLEBUILDER_H
#define	INTEGERVARIABLEBUILDER_H

#include "VariableBuilder/VariableBuilder.h"

class IntegerVariableBuilder : public VariableBuilder {
public:
    IntegerVariableBuilder();
    virtual ~IntegerVariableBuilder();

    Variable *createVariable(int value);
    Variable *createVariable(Variable *min, Variable *max, Random *random);
    Variable *createVariable(Variable *value);
    Variable *addVariables(Variable *a, Variable *b);
    Variable *substractVariables(Variable *a, Variable *b);
    const char *getName();
};

#endif	/* INTEGERVARIABLEBUILDER_H */
