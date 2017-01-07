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
#include "downloaddatabyevent.h"
#include "dataselect.h"
#include "stationlistdownload.h"
#include "eventlistdownload.h"
#include "info.h"
#include "debug.h"
#include <QDir>
#include <QSet>


static QString unique_key(const Event &event, const Trace &trace)
{
    return QString("%1.%2.%3.%4.%5")
           .arg(event.id())
           .arg(trace.network())
           .arg(trace.station())
           .arg(trace.location())
           .arg(trace.channel());
}


static void download_data_for_event(const AppArguments &arguments, const Event &event, int &totalCount)
{
    int countPerEvent = 0;
    static QSet<QString> uniqueKeys;

    const QList<Trace> traces = station_list_download(arguments, arguments.stationQuery(event));
    foreach (const Trace &trace, traces) {
        // we shouldn't download the duplicates of the traces
        if (uniqueKeys.contains(unique_key(event, trace))) {
            debug_print(arguments,
                        QObject::tr("duplicate trace \'%1 - %2.%3.%4.%5\' was skiped")
                        .arg(event.id())
                        .arg(trace.network())
                        .arg(trace.station())
                        .arg(trace.location())
                        .arg(trace.channel()));
            continue;
        }
        else {
            uniqueKeys.insert(unique_key(event, trace));
        }

        // create the dataselect query
        const DataSelectQuery query = arguments.dataSelectQuery(event, trace);
        debug_print(arguments, query);

        // create the sound tags
        const SoundTags tags = SoundTags::fromDataSelectQuery(event, query);
        debug_print(arguments, tags);


        // create the full file name to save the sound
        const QString fileName = arguments.fileName(event, query);

        // skip the already exists file
        if (arguments.conflictActions() == FileNameConflictAction::Skip
                && QFileInfo(fileName).exists()) {
            info_print(QObject::tr("file \'%1\' already exists").arg(fileName));
            continue;
        }

        // download trace and save it as a sound
        info_print(QObject::tr("Downloading trace \'%1.%2.%3.%4 (%5 - %6)\' to \'%7\'")
                   .arg(query.network())
                   .arg(query.station())
                   .arg(query.location())
                   .arg(query.channel())
                   .arg(query.startTime().toString(DisplayDateTimeFormat))
                   .arg(query.endTime().toString(DisplayDateTimeFormat))
                   .arg(fileName));

        QString errstr;
        if (dataselect_and_save_sound(arguments, query, fileName, tags, &errstr)) {
            info_print(QObject::tr("Success"));

            if (++totalCount >= arguments.limit()) {
                debug_print(QObject::tr("limit exceed"));
                exit(EXIT_SUCCESS);
            }

            if (++countPerEvent >= arguments.limitPerEvent()) {
                debug_print(QObject::tr("limit per event exceed"));
                return;
            }
        }
        else {
            info_print(QObject::tr("Downloading failed: %1").arg(errstr));
        }
    }
}


void download_data_by_event(const AppArguments &arguments)
{
    int totalCount = 0;
    const QList<Event> events = event_list_download(arguments, arguments.eventQuery());
    foreach (const Event &event, events) {
        download_data_for_event(arguments, event, totalCount);
    }
}
