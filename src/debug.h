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
#ifndef DEBUG_H
#define DEBUG_H


#include "trace.h"
#include "event.h"
#include "eventquery.h"
#include "stationquery.h"
#include "dataselectquery.h"
#include "soundtags.h"
#include "apparguments.h"

void debug_print(const QString &string);
void debug_print(const AppArguments &arguments, const QString &string);

void debug_print(const AppArguments &arguments);
void debug_print(const AppArguments &arguments, const EventQuery &query);
void debug_print(const AppArguments &arguments, const StationQuery &query);
void debug_print(const AppArguments &arguments, const DataSelectQuery &query);
void debug_print(const AppArguments &arguments, const SoundTags &tags);


#endif // DEBUG_H
