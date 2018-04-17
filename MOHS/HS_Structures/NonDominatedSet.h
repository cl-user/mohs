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

#ifndef NONDOMINATEDSET_H
#define	NONDOMINATEDSET_H

#include <cstdio>

class NonDominatedSet {
public:
    NonDominatedSet();
    virtual ~NonDominatedSet();

    /**
     * Get the size of non-dominated subset.
     */
    virtual int getNonDominatedSize() const = 0;

    /**
     * Prints non-dominated points.
     */
    virtual void printNonDominated(FILE *output, bool printVars,
        bool printCounter) const = 0;
};

#endif	/* NONDOMINATEDSET_H */
