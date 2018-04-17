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

#ifndef BITFIELDVARIABLEBUILDER_H
#define	BITFIELDVARIABLEBUILDER_H

#include "Variable/BinaryVariable.h"
#include "VariableBuilder/BinaryVariableBuilder.h"
#include "Variable/BitFieldVariable.h"

class BitFieldVariableBuilder : public BinaryVariableBuilder {
public:
    BitFieldVariableBuilder();
    virtual ~BitFieldVariableBuilder();

    BitFieldVariable *createVariable(unsigned int length);
    BitFieldVariable *createVariable(int32_t value, unsigned int length);
    BitFieldVariable *createVariable(Variable *min, Variable *max, Random *random);
    BitFieldVariable *createVariable(Variable *value);
    BitFieldVariable *addVariables(Variable *a, Variable *b);
    BitFieldVariable *substractVariables(Variable *a, Variable *b);
    BitFieldVariable *mutateVariable(BinaryVariable *v, BinaryVariable *mask);
    const char *getName();
};

#endif	/* BITFIELDVARIABLEBUILDER_H */
