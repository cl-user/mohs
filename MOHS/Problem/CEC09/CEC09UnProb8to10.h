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

#ifndef CEC09UNPROB8TO10_H
#define	CEC09UNPROB8TO10_H

#include "Problem/RealProblem.h"
#include <vector>
using namespace std;

class CEC09UnProb8to10 : public RealProblem {
protected:
    /* Set J1 */
    vector<int> J1;

    /* Set J2 */
    vector<int> J2;

    /* Set J3 */
    vector<int> J3;
    
public:
    CEC09UnProb8to10(const char *path, HS_Params *hsParams, VariableBuilder *varBuilder);
    virtual ~CEC09UnProb8to10();
};

#endif	/* CEC09UNPROB8TO10_H */

