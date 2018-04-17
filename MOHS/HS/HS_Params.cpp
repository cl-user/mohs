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

#include "HS/HS_Params.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>

HS_Params::HS_Params(const char *path) {
    FILE *file;
    char buffer[30];
    const int PARAMS = 19;
    int count = 0;

    if ((file = fopen(path, "r")) == NULL) {
        fprintf(stderr, "Error opening file '%s' in read mode\n", path);
        exit(EXIT_FAILURE);
    }

    while (!feof(file)) {
        buffer[0] = '\0';
        fscanf(file, "%s", buffer);
        
        if (strcasecmp(buffer, "HMCR") == 0) {
            fscanf(file, "%lf", &hmcr);
            ++count;
        }
        else if (strcasecmp(buffer, "PAR") == 0) {
            fscanf(file, "%lf", &par);
            ++count;
        }
        else if (strcasecmp(buffer, "SETFW") == 0) {
            fscanf(file, "%d", &setFW);
            ++count;
        }
        else if (strcasecmp(buffer, "REALFW") == 0) {
            fscanf(file, "%lf", &realFW);
            ++count;
        }
        else if (strcasecmp(buffer, "BINFW") == 0) {
            fscanf(file, "%lf", &binFW);
            ++count;
        }
        else if (strcasecmp(buffer, "HMS") == 0) {
            fscanf(file, "%d", &hms);
            ++count;
        }
        else if (strcasecmp(buffer, "TMPHMS") == 0) {
            fscanf(file, "%d", &tmpHms);
            ++count;
        }
        else if (strcasecmp(buffer, "STOP") == 0) {
            fscanf(file, "%d", &stoppingCriteria);
            ++count;
        }
        else if (strcasecmp(buffer, "SAMPLING") == 0) {
            fscanf(file, "%d", &samplingCriteria);
            ++count;
        }
        else if (strcasecmp(buffer, "MAXITERATION") == 0) {
            fscanf(file, "%d", &maxIteration);
            ++count;
        }
        else if (strcasecmp(buffer, "TIME") == 0) {
            fscanf(file, "%lld", &miliseconds);
            ++count;
        }
        else if (strcasecmp(buffer, "CYCLES") == 0) {
            fscanf(file, "%d", &cycles);
            ++count;
        }
        else if (strcasecmp(buffer, "INTERVAL") == 0) {
            fscanf(file, "%lld", &samplingInterval);
            ++count;
        }
        else if (strcasecmp(buffer, "DEBUG") == 0) {
            fscanf(file, "%d", &debug);
            ++count;
        }
        else if (strcasecmp(buffer, "PSMAXSIZE") == 0) {
            fscanf(file, "%d", &psMaxSize);
            ++count;
        }
        else if (strcasecmp(buffer, "PSMAXGROWTH") == 0) {
            fscanf(file, "%d", &psMaxGrowth);
            ++count;
        }
        else if (strcasecmp(buffer, "EPSILONM1") == 0) {
            fscanf(file, "%lf", &epsilonM1);
            ++count;
        }
        else if (strcasecmp(buffer, "FRONTMINSIZE") == 0) {
            fscanf(file, "%d", &frontMinSize);
            ++count;
        }
        else if (strcasecmp(buffer, "TRUNCATEPERCENTAGE") == 0) {
            fscanf(file, "%lf", &truncatePercentage);
            ++count;
        }
    }

    /* Parameters validation */
    assert(count == PARAMS);
    assert(hmcr >= 0);
    assert(par >= 0);
    assert(setFW == 0 || setFW == 1);
    assert(realFW > 0 && realFW < 100);
    assert(binFW > 0 && binFW < 100);
    assert(hms > 0);
    assert(tmpHms > 0);
    assert(stoppingCriteria == 0 || stoppingCriteria == 1);
    assert(samplingCriteria == 0 || samplingCriteria == 1);
    assert(maxIteration > 0);
    assert(miliseconds > 0);
    assert(samplingInterval > 0);
    assert(cycles > 0);
    assert(debug == 0 || debug == 1);
    assert(psMaxSize > 0);
    assert(psMaxGrowth > 0 && psMaxGrowth > psMaxSize);
    assert(epsilonM1 > 0);
    assert(frontMinSize > 0);
    assert(truncatePercentage >= 0.0 && truncatePercentage <= 100.0);

    fclose(file);
}

HS_Params::~HS_Params() {

}

int HS_Params::getHMS() const {
    return hms;
}

int HS_Params::getTmpHMS() const {
    return tmpHms;
}

double HS_Params::getPAR() const {
    return par;
}

double HS_Params::getHMCR() const {
    return hmcr;
}

int HS_Params::getSetFW() const {
    return setFW;
}

double HS_Params::getRealFW() const {
    return realFW;
}

double HS_Params::getBinFW() const {
    return binFW;
}

int HS_Params::getStoppingCriteria() const {
    return stoppingCriteria;
}

int HS_Params::getSamplingCriteria() const {
    return samplingCriteria;
}

int HS_Params::getMaxIteration() const {
    return maxIteration;
}

long long HS_Params::getMiliseconds() const {
    return miliseconds;
}

long long HS_Params::getInterval() const {
    return samplingInterval;
}

int HS_Params::getCycles() const {
    return cycles;
}

bool HS_Params::getDebug() const {
    if (debug == 0)
        return false;

    return true;
}

int HS_Params::getParetoSetMaxSize() const {
    return psMaxSize;
}

int HS_Params::getParetoSetMaxGrowth() const {
    return psMaxGrowth;
}

double HS_Params::getEpsilonM1() const {
    return epsilonM1;
}

int HS_Params::getFrontMinSize() const {
    return frontMinSize;
}

double HS_Params::getTruncatePercentage() const {
    return truncatePercentage;
}
