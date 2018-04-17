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

#ifndef NONDOMINATEDRANKING_H
#define	NONDOMINATEDRANKING_H 

#include "HS_Operators/ParetoRanking/ParetoRanking.h"

class NonDominatedRanking : public ParetoRanking {
private:
    /* Utilitario para intercambiar de lugar dos individuos. */
    void swap(Solution *population[], unsigned int i, unsigned int j);

    /*
     * Ordena la población dentro del rango [start, count) colocando a los
     * individuos no-dominados al final del arreglo. Retorna la cantidad de
     * individuos no-dominados.
     */
    int sort(Solution *population[], unsigned int start, unsigned int count);
public:
    NonDominatedRanking();
    virtual ~NonDominatedRanking();
    void rank(Memory *memory);
    void rank(Memory *memory, Solution *solution);
    const char *getName();
};

#endif	/* NONDOMINATEDRANKING_H */

