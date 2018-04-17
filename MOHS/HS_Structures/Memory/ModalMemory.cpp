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

#include "HS_Structures/Memory/ModalMemory.h"
#include <cstdlib>

ModalMemory::ModalMemory(int size, Problem *problem) : Memory(size) {
    this->problem = problem;

    /* Each variable histogram */
    this->histogramCount = this->problem->getSize();
    this->histogram = new histogram_t[this->histogramCount];
}

ModalMemory::~ModalMemory() {
    for (int i=0; i < this->histogramCount; i++) {
        delete[] this->histogram[i].bars;
        delete[] this->histogram[i].orderedBars;
    }

    delete[] this->histogram;
}

int barCmp(const void *a, const void *b) {
    histogram_bar_t *b1 = *((histogram_bar_t **) a);
    histogram_bar_t *b2 = *((histogram_bar_t **) b);

    if (b1->count > b2->count)
        return 1;
    else if (b1->count < b2->count)
        return -1;
    else
        return 0;
}

void ModalMemory::sortHistogram() {
    /* Bars sorting */
    for (int i=0; i < this->histogramCount; i++) {

        /* Initialize array of sorted bars */
        for (int j=0; j < this->histogram[i].barsCount; j++)
            histogram[i].orderedBars[j] = &(histogram[i].bars[j]);

        /* Sort bars according to counting */
        qsort(histogram[i].orderedBars, histogram[i].barsCount,
                sizeof(histogram_bar_t *), barCmp);

        /* Update index of each barr according to its position in "orderedBars" */
	for (int j=0; j < this->histogram[i].barsCount; j++)
	    histogram[i].orderedBars[j]->rank = j;
    }
}

void ModalMemory::updateMode(int variable, Variable *value, bool increment) {
    /* Find position of the variable corresponding bar */
    int pos = this->findBarPos(variable, value);

    /* Counting */
    histogram[variable].bars[pos].count += increment ? 1 : -1;

    /* Recalculate mode */
    sortBars(variable, histogram[variable].bars[pos].rank, increment);
}

void ModalMemory::sortBars(int histogramPos, int barPos, bool ascending) {
    histogram_t     hist = histogram[histogramPos];
    histogram_bar_t *bar = hist.orderedBars[barPos];
    histogram_bar_t *other;

    if (ascending) {
        /* Successively comparing with neighbors on the right */
        for (; barPos < hist.barsCount - 1; barPos++) {
            other = hist.orderedBars[barPos + 1];

            if (bar->count > other->count)
                swapBars(histogramPos, barPos, barPos + 1);
            else
                break;
        }
    }
    else {
        /* Successively comparing with neighbors on the left */
        for (; barPos > 0; barPos--) {
            other = hist.orderedBars[barPos - 1];

            if (bar->count < other->count)
                swapBars(histogramPos, barPos, barPos - 1);
            else
                break;
        }
    }
}

void ModalMemory::swapBars(int histPos, int barPos, int otherPos) {
    histogram_t     hist   = histogram[histPos];
    histogram_bar_t *bar   = hist.orderedBars[barPos];
    histogram_bar_t *other = hist.orderedBars[otherPos];

    /* Swap bars */
    hist.orderedBars[barPos] = other;
    hist.orderedBars[otherPos] = bar;

    /* Update bar position */
    bar->rank = otherPos;
    other->rank = barPos;
}
