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

#include "Problem/CEC09/CEC09UnProb8to10.h"

CEC09UnProb8to10::CEC09UnProb8to10(const char *path, HS_Params *hsParams,
        VariableBuilder *varBuilder) : RealProblem(path, hsParams, varBuilder) {

    /* Build up sets J1, J2, J3 */
    J1;
    J2;
    J3;
    for (int j=3; j <= size; j++) {
        if (((j - 1) % 3) == 0)
            J1.push_back(j);

        if (((j - 2) % 3) == 0)
            J2.push_back(j);

        if ((j % 3) == 0)
            J3.push_back(j);
    }
}

CEC09UnProb8to10::~CEC09UnProb8to10() {
    
}
