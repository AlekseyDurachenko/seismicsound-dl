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
#include "downloaddatabytime.h"
#include "stationlistdownload.h"
#include "dataselect.h"
#include "info.h"
#include "debug.h"
#include <QFileInfo>
#include <QSet>


static QString unique_key(const Trace &trace)
{
    return QString("%1.%2.%3.%4")
           .arg(trace.network())
           .arg(trace.station())
           .arg(trace.location())
           .arg(trace.channel());
}


void download_data_by_time(const AppArguments &arguments)
{
    int totalCount = 0;
    QSet<QString> uniqueKeys;

    const QList<Trace> Traces = station_list_download(arguments, arguments.stationQuery());
    foreach (const Trace &trace, Traces) {
        // we shouldn't download the duplicates of the traces
        if (uniqueKeys.contains(unique_key(trace))) {
            debug_print(arguments,
                        QObject::tr("duplicate trace \'%1.%2.%3.%4\' was skiped")
                        .arg(trace.network())
                        .arg(trace.station())
                        .arg(trace.location())
                        .arg(trace.channel()));
            continue;
        }
        else {
            uniqueKeys.insert(unique_key(trace));
        }

        // create the dataselect query
        const DataSelectQuery query = arguments.dataSelectQuery(trace);
        debug_print(arguments, query);

        // create the sound tags
        const SoundTags tags = SoundTags::fromDataSelectQuery(query);
        debug_print(arguments, tags);

        // create the full file name to save the sound
        const QString fileName = arguments.fileName(query);

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
                debug_print(arguments, QObject::tr("limit exceed"));
                exit(EXIT_SUCCESS);
            }
        }
        else {
            info_print(QObject::tr("Downloading failed: %1").arg(errstr));
        }
    }
}
