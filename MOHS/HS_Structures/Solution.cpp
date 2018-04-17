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

#include "HS_Structures/Solution.h"

Solution::Solution(int size, int objectives) : ParetoPoint(objectives) {
    variables = new Variable*[size];
    for (int i=0; i < size; i++)
        variables[i] = NULL;

    this->size = size;
    ranking = 0;
}

Solution::~Solution() {
    for (int i=0; i < size; i++)
        delete variables[i];
    
    delete[] variables;
}

Variable *Solution::getVariable(int i) const {
    return variables[i];
}

Variable **Solution::getVariables() const {
    return variables;
}

int Solution::getSize() const {
    return size;
}

int Solution::getRanking() const {
    return ranking;
}

void Solution::setVariable(int i, Variable *value) {
    if (variables[i] != NULL)
        delete variables[i];
    
    variables[i] = value;
}

void Solution::setRanking(int value) {
    ranking = value;
}

void Solution::print(FILE *output, bool printVars) const {
    for (int i=0; i < objectives; i++) {
        fprintf(output, "%e", objectiveValues[i]);
        if (i < objectives - 1)
            fprintf(output, "\t");
    }

    if (printVars) {
        fprintf(output, "\t");

        for (int i=0; i < size; i++) {
            variables[i]->print(output);
            if (i < size - 1)
                fprintf(output, "\t");
        }

        fprintf(output, "\t%d", ranking);
        fprintf(output, "\t%d", dominatedBy);
        fprintf(output, "\t%d", dominates);
    }
    
    fprintf(output, "\n");
}

Comparison Solution::compare(const Solution* h) const {
    if (this->ranking < h->ranking)
        return BETTER;
    else if (this->ranking > h->ranking)
        return WORSE;
    else
        return EQUAL;
}

bool Solution::equals(const Solution *h) const {
    if (h == NULL)
        return false;

    if (this->size != h->size)
        return false;

    for (int i=0; i < size; i++)
        if (variables[i]->compare(h->variables[i]) != 0)
            return false;

    return true;
}

Solution* Solution::clone(VariableBuilder *varBuilder) {
    Solution *sol = new Solution(this->size, this->objectives);
    for (int i=0; i < this->size; i++)
        sol->setVariable(i, varBuilder->createVariable(this->getVariable(i)));

    for (int i=0; i < this->objectives; i++)
        sol->setObjectiveValue(i, this->getObjectiveValue(i));
    
    sol->ranking = this->ranking;
    sol->dominatedBy = this->dominatedBy;
    sol->dominates = this->dominates;
    
    return sol;
}
