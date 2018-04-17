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

#include "HS_Structures/Pareto/ParetoPointList.h"

ParetoPointList::ParetoPointList(ParetoPoint *orig, ParetoSet *ps) {
    this->orig = orig;
    this->start = 0;
    this->size = 0;

    ps->begin();
    while (ps->hasNext()) {
        ParetoPoint *dest = ps->getNext();

        if (orig != dest) {
            Node *tmp = new Node;

            tmp->dest = dest;
            tmp->distance = this->orig->distanceTo(dest);
            tmp->next = start;

            this->start = tmp;
            this->size++;
        }
    }
    
    this->frontier = this->start;
}

ParetoPointList::~ParetoPointList() {
    while (start) {
        Node *tmp = start->next;
        delete start;
        start = tmp;
    }
}

unsigned int ParetoPointList::getSize(void) const {
    return size;
}

void ParetoPointList::findAndRemove(ParetoPoint *p) {
    Node *prev;
    Node *cur = start;

    while (cur && cur->dest != p) {
        prev = cur;
        cur = cur->next;
    }

    if (cur) {
        if (cur == frontier)
            frontier = frontier->next;

        if (cur == start)
            start = cur->next;
        else
            prev->next = cur->next;

        delete cur;
        size--;
    }
}

void ParetoPointList::nextNearest(void) {
    Node *min = frontier;

    for (Node *challenger = frontier->next; challenger; challenger = challenger->next)
        if (challenger->distance < min->distance)
            min = challenger;

    swap(frontier, min);
    frontier = frontier->next;
}

void ParetoPointList::begin(void) {
    current = start;
    if (current == frontier)
        nextNearest();
}

ParetoPoint *ParetoPointList::getParetoPoint(void) {
    return current->dest;
}

double ParetoPointList::getDistance(void) {
    return current->distance;
}

void ParetoPointList::swap(Node *a, Node *b) {
    Node tmp;

    tmp.dest = a->dest;
    tmp.distance = a->distance;

    a->dest = b->dest;
    a->distance = b->distance;

    b->dest = tmp.dest;
    b->distance = tmp.distance;
}

void ParetoPointList::next(void) {
    if (current->next == frontier)
        nextNearest();
    current = current->next;
}

bool ParetoPointList::hasNext(void) {
    return current->next ? true : false;
}
