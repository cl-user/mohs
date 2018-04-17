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

#include "Problem/CEC09/CEC09UnProb1to7.h"

CEC09UnProb1to7::CEC09UnProb1to7(const char *path, HS_Params *hsParams,
        VariableBuilder *varBuilder) : RealProblem(path, hsParams, varBuilder) {

    /* Build up sets for odd and even numbers */
    J1;
    J2;
    for (int j=2; j <= size; j++) {
        if (j % 2 == 0)
            J2.push_back(j);
        else
            J1.push_back(j);
    }
}

CEC09UnProb1to7::~CEC09UnProb1to7() {
    
}

ParetoSet *CEC09UnProb1to7::optimalParetoFront(void) {
    /*
     * For all Optimal Fronts, the first objective function (abscissa)
     * is in the range [0, 1]. The number of points is arbitrary, except
     * for problems 5 and 6 (they should override this method).
     */
    return optimalParetoFront2D(0.0, 1.0, 1.0 / pfsize);
}
