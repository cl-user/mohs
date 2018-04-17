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

#include "HS_Operators/PitchAdjustment/BoundedPitchAdjustment.h"

BoundedPitchAdjustment::BoundedPitchAdjustment() {

}

BoundedPitchAdjustment::~BoundedPitchAdjustment() {

}

Variable *BoundedPitchAdjustment::adjust(Problem *problem, int variable, Variable* value, Random* random) {
    /* Resulting variable */
    Variable *result = NULL;

    /* Bound variable */
    Variable *limit = NULL;

    /* Get fret width for the variable */
    Variable *fw = problem->getFretWidth(variable);

    /* Get upper and lower bounds for the variable */
    Variable *min = problem->getMinimum(variable);
    Variable *max = problem->getMaximum(variable);

    /* Decide if the new variable will be lesser or greater */
    int rand = random->boundedIntegerRandom(0, 2);
    if (rand == 0) {
        /* Create a lesser variable */
        limit = problem->getVariableBuilder()->substractVariables(value, fw);
        result = problem->getVariableBuilder()->createVariable(limit, value, random);

        /* If it is lesser than lower bound, return lower bound */
        if (result->compare(min) < 0) {
            delete result;
            result = problem->getVariableBuilder()->createVariable(min);
        }
    }
    else {
        /* Create a greater variable */
        limit = problem->getVariableBuilder()->addVariables(value, fw);
        result = problem->getVariableBuilder()->createVariable(value, limit, random);

        /* If it is greater than upper bound, return upper bound */
        if (result->compare(max) > 0) {
            delete result;
            result = problem->getVariableBuilder()->createVariable(max);
        }
    }

    delete limit;
    delete value;
    return result;
}

const char *BoundedPitchAdjustment::getName() {
    return "BoundedPitchAdjustment";
}
