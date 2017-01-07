// Copyright 2017, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#ifndef CONSTS_H
#define CONSTS_H


#include <limits>
#include <QtGlobal>

const int MinimumSampleRate = 100;
const int MaximumSampleRate = 192000;

const double MinimumLatitude = -90.0;
const double MaximumLatitude = +90.0;
const double InvalidLatitude = +999999.9;

const double MinimumLongitude = -180.0;
const double MaximumLongitude = +180.0;
const double InvalidLongitude = +999999.9;

const double MinimumDepth = -100000.0;
const double MaximumDepth = +900000.0;
const double InvalidDepth = +999999.9;

const double MinimumRadius = +0.0;
const double MaximumRadius = +180.0;
const double InvalidRadius = +999999.9;

const double MinimumMagnitude = -100.0;
const double MaximumMagnitude = +100.0;
const double InvalidMagnitude = +999999.9;

const int MinimumOffset = 0;
const int MaximumOffset = std::numeric_limits<int>::max() - 1;
const int InvalidOffset = -1;

const int MinimumLimit = 1;
const int MaximumLimit = std::numeric_limits<int>::max() - 1;
const int InvalidLimit = -1;


const int DefaultSampleRate = 44100;
const int DefaultSecondsBefore = 300;
const int DefaultSecondsAfter = 3600;
const char DefaultSoundFileNameFormat[] = "%eid%.%net%.%sta%.%loc%.%chan%.%starttime%.%endtime%";
const char DefaultShowEventsFormat[] = " %eid% | %type% | %val% | %lat% | %lon% | %depth% | %time | %desc%";
const char DefaultShowStationFormat[] =  " %net% | %sta% | %loc% | %chan% | %lat% | %lon% | %elevat% | %depth% | %stime% | %etime% | %site%";
const char DisplayDateTimeFormat[] = "yyyy-MM-ddTHH:mm:ss";
const char FileNameDateTimeFormat[] = "yyyyMMddHHmmss";
const char DefaultSoundGenre[] = "seismic";
const char DefaultNoneEventIdName[] = "ID_NONE";


#endif // CONSTS_H
