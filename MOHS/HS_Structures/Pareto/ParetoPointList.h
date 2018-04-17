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

#include "HS_Structures/Pareto/ParetoPoint.h"
#include "HS_Structures/Pareto/ParetoSet.h"

class ParetoPointList {
private:
    struct Node {
        ParetoPoint *dest;
        double distance;
        Node *next;
    } *start, *current, *frontier;

    ParetoPoint *orig;
    unsigned int size;

    void swap(Node *a, Node *b);
    void nextNearest(void);

public:
    ParetoPointList(ParetoPoint *orig, ParetoSet *ps);
    ~ParetoPointList();
    unsigned int getSize(void) const;
    void findAndRemove(ParetoPoint *p);
    void begin(void);
    ParetoPoint *getParetoPoint(void);
    double getDistance(void);
    void next(void);
    bool hasNext(void);
};
