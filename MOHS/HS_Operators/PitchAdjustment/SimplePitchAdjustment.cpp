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

#include "HS_Operators/PitchAdjustment/SimplePitchAdjustment.h"

SimplePitchAdjustment::SimplePitchAdjustment() {

}

SimplePitchAdjustment::~SimplePitchAdjustment() {

}

Variable *SimplePitchAdjustment::adjust(Problem *problem, int variable, Variable* value, Random* random) {
    /* Resulting variable */
    Variable *result = NULL;

    /* Get fret width for the variable */
    Variable *fw = problem->getFretWidth(variable);

    /* Decide if the new variable will be lesser or greater */
    int rand = random->boundedIntegerRandom(0, 2);
    if (rand == 0) {
        /* Create a lesser variable */
        Variable *min = problem->getVariableBuilder()->substractVariables(value, fw);
        if (min->compare(problem->getMinimum(variable)) < 0)
            result = problem->getVariableBuilder()->createVariable(problem->getMinimum(variable), value, random);
        else
            result = problem->getVariableBuilder()->createVariable(min, value, random);

        delete min;
    }
    else {
        /* Create a greater variable */
        Variable *max = problem->getVariableBuilder()->addVariables(value, fw);
        if (max->compare(problem->getMaximum(variable)) > 0)
            result = problem->getVariableBuilder()->createVariable(value, problem->getMaximum(variable), random);
        else
            result = problem->getVariableBuilder()->createVariable(value, max, random);

        delete max;
    }

    delete value;
    return result;
}

const char *SimplePitchAdjustment::getName() {
    return "SimplePitchAdjustment";
}
