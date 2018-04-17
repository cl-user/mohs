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

#ifndef TIME_H
#define	TIME_H

#include <list>
using namespace std;

/**
 * Datatype for timer states.
 */
typedef enum {
    STARTED, PAUSED
} TimerState;

class Timer {
private:
    long long begin;
    long long pauseValue;
    TimerState state;
    list<long long> splitList;
    
public:
    /** Get the elapsed time in miliseconds */
    static long long getTimeMillis();

    /** Constructor */
    Timer();

    /** Destructor */
    ~Timer();

    /** Starts the timer */
    void start();

    /** Get elapsed time in miliseconds */
    long long getElapsed() const;

    /** Checks if a number of miliseconds have elapsed */
    bool hasElapsed(long long miliseconds) const;

    /** Forwards the beginning of the timer */
    void forward(long long elapsed);

    /** Pauses the timer */
    void pause();

    /** Resumes the paused timer */
    void resume();

    /** Save a split time */
    long long split();

    /** Get the last saved split time */
    long long lastSplit() const;
};

#endif	/* TIME_H */
