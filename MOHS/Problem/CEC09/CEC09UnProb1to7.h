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

#ifndef CEC09UNPROB1TO7_H
#define	CEC09UNPROB1TO7_H

#include "HS_Structures/Pareto/ParetoSet.h"
#include "Problem/RealProblem.h"
#include <vector>
using namespace std;

class CEC09UnProb1to7 : public RealProblem {
protected:
    /** Set of odd numbers. */
    vector<int> J1;

    /** Set of even numbers. */
    vector<int> J2;
    
public:
    CEC09UnProb1to7(const char *path, HS_Params *hsParams, VariableBuilder *varBuilder);
    virtual ~CEC09UnProb1to7();
    ParetoSet *optimalParetoFront(void);
};

#endif	/* CEC09UNPROB1TO7_H */

