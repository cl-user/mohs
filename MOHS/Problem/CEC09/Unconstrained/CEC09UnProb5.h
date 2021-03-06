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

#ifndef CEC09_UNPROB5_H
#define	CEC09_UNPROB5_H

#include "Problem/CEC09/CEC09UnProb1to7.h"
#include "HS_Structures/Pareto/ParetoSet.h"
#include "HS_Structures/Solution.h"

class CEC09UnProb5 : public CEC09UnProb1to7 {
private:
    double N;
    double epsilon;
    double y(double xj, int j, double x1);
    double h(double t);
public:
    CEC09UnProb5(const char *path, HS_Params *hsParams, VariableBuilder *varBuilder);
    ~CEC09UnProb5();
    ParetoSet *optimalParetoFront(void);
    double paretoOrdinate(double f1);
    void evaluate(Solution *sol);
    double getMaxDistance() const;
    const char *getName();
};

#endif	/* CEC09_UNPROB5_H */
