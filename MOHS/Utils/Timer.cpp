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

#include "Utils/Timer.h"
#include <cstdio>
#include <cstdlib>
#include <sys/time.h>

Timer::Timer() {
    splitList;
    begin = 0;
    state = PAUSED;
}

Timer::~Timer() {

}

void Timer::start() {
    begin = getTimeMillis();
    state = STARTED;
}

long long Timer::getElapsed() const {
    long long end = getTimeMillis();
    return (end - begin);
}

bool Timer::hasElapsed(long long miliseconds) const {
    return getElapsed() >= miliseconds;
}

long long Timer::split() {
    long long tmp = getElapsed();
    splitList.push_back(tmp);
    return tmp;
}

long long Timer::lastSplit() const {
    long long last = splitList.back();
    return last;
}

void Timer::forward(long long elapsed) {
    begin += elapsed;
}

void Timer::pause() {
    if (state == PAUSED)
        return;

    pauseValue = getTimeMillis();
    state = PAUSED;
}

void Timer::resume() {
    if (state == STARTED)
        return;

    begin += getTimeMillis() - pauseValue;
    state = STARTED;
}

long long Timer::getTimeMillis() {
    long long seconds, miliseconds;
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1) {
        fprintf(stderr, "%s(): %s", __func__, "Error getting time.");
        exit(EXIT_FAILURE);
    }

    /* Save times */
    seconds = tv.tv_sec;
    miliseconds = tv.tv_usec;

    /* Convert times to miliseconds */
    seconds = seconds * 1000;
    miliseconds = miliseconds / 1000;

    /* Return the result */
    return (seconds + miliseconds);
}
