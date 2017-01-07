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
#ifndef APPARGUMENTS_H
#define APPARGUMENTS_H


#include "appargument.h"
#include "eventquery.h"
#include "stationquery.h"
#include "dataselectquery.h"
#include "event.h"
#include "trace.h"
#include "filenameconflictaction.h"
#include <QStringList>


class AppArguments
{
    friend class Test_AppArguments;
    friend void debug_print(const AppArguments &);
public:
    explicit AppArguments(const QStringList &cmdlineArguments = QStringList());

    FileNameConflictAction conflictActions() const;
    int sampleFormat() const;
    int sampleRate() const;

    inline bool hasEventQuery() const;
    EventQuery eventQuery() const;

    StationQuery stationQuery() const;
    StationQuery stationQuery(const Event &event) const;

    DataSelectQuery dataSelectQuery(const Trace &trace) const;
    DataSelectQuery dataSelectQuery(const Event &event, const Trace &trace) const;

    QString fileName(const DataSelectQuery &query) const;
    QString fileName(const Event &event, const DataSelectQuery &query) const;

    inline int limit() const;
    inline int limitPerEvent() const;

    inline bool hasPrintFdsnwsDataselectServices() const;
    inline bool hasPrintFdsnwsStationServices() const;
    inline bool hasPrintFdsnwsEventServices() const;

    inline bool hasPrintSelectedEvents() const;
    inline QString selectedEventsFormat() const;

    inline bool hasPrintSelectedTraces() const;
    inline QString selectedTracesFormat() const;

    inline bool hasDebug() const;
    inline bool hasHelp() const;

    inline bool hasError() const;
    inline const QString &lastError() const;

private:
    inline const QHash<QString, AppArgument *> &arguments() const;

private:
    void create();
    void parseAndValidate(const QStringList &cmdlineArguments);

private:
    QString m_lastError;
    AppArgument m_argSampleRate;
    AppArgument m_argSampleFormat;
    AppArgument m_argOutputDirectory;
    AppArgument m_argFileNameFormat;
    AppArgument m_argFileNameConflictAction;
    AppArgument m_argEventId;
    AppArgument m_argEventStartTime;
    AppArgument m_argEventEndTime;
    AppArgument m_argEventMinMag;
    AppArgument m_argEventMaxMag;
    AppArgument m_argEventMinDepth;
    AppArgument m_argEventMaxDepth;
    AppArgument m_argEventMinLat;
    AppArgument m_argEventMaxLat;
    AppArgument m_argEventMinLon;
    AppArgument m_argEventMaxLon;
    AppArgument m_argEventLat;
    AppArgument m_argEventLon;
    AppArgument m_argEventMinRadius;
    AppArgument m_argEventMaxRadius;
    AppArgument m_argNetwork;
    AppArgument m_argStation;
    AppArgument m_argLocation;
    AppArgument m_argChannel;
    AppArgument m_argStartTime;
    AppArgument m_argEndTime;
    AppArgument m_argStationMinLat;
    AppArgument m_argStationMaxLat;
    AppArgument m_argStationMinLon;
    AppArgument m_argStationMaxLon;
    AppArgument m_argStationLat;
    AppArgument m_argStationLon;
    AppArgument m_argStationMinRadius;
    AppArgument m_argStationMaxRadius;
    AppArgument m_argLimit;
    AppArgument m_argLimitPerEvent;
    AppArgument m_argSecondsBefore;
    AppArgument m_argSecondsAfter;
    AppArgument m_argFdsnwsDataselectUrl;
    AppArgument m_argFdsnwsStationUrl;
    AppArgument m_argFdsnwsEventUrl;
    AppArgument m_argPrintFdsnwsDataselectServices;
    AppArgument m_argPrintFdsnwsStationServices;
    AppArgument m_argPrintFdsnwsEventServices;
    AppArgument m_argPrintFdsnwsServices;
    AppArgument m_argPrintSelectedEvents;
    AppArgument m_argPrintSelectedTraces;
    AppArgument m_argSelectedEventsFormat;
    AppArgument m_argSelectedTracesFormat;
    AppArgument m_argDebug;
    AppArgument m_argHelp;
    QHash<QString, AppArgument *> m_arguments;
};

int AppArguments::limit() const
{
    return m_argLimit.toInt();
}

int AppArguments::limitPerEvent() const
{
    return m_argLimitPerEvent.toInt();
}

bool AppArguments::hasPrintFdsnwsDataselectServices() const
{
    return m_argPrintFdsnwsDataselectServices.isFound();
}

bool AppArguments::hasPrintFdsnwsStationServices() const
{
    return m_argPrintFdsnwsStationServices.isFound();
}

bool AppArguments::hasPrintFdsnwsEventServices() const
{
    return m_argPrintFdsnwsEventServices.isFound();
}

bool AppArguments::hasPrintSelectedEvents() const
{
    return m_argPrintSelectedEvents.isFound();
}

bool AppArguments::hasPrintSelectedTraces() const
{
    return m_argPrintSelectedTraces.isFound();
}

QString AppArguments::selectedEventsFormat() const
{
    return m_argSelectedEventsFormat.toString();
}

QString AppArguments::selectedTracesFormat() const
{
    return m_argSelectedTracesFormat.toString();
}

bool AppArguments::hasDebug() const
{
    return m_argDebug.isFound();
}

bool AppArguments::hasHelp() const
{
    return m_argHelp.isFound();
}

bool AppArguments::hasError() const
{
    return !m_lastError.isEmpty();
}

const QString &AppArguments::lastError() const
{
    return m_lastError;
}

bool AppArguments::hasEventQuery() const
{
    return !m_argStartTime.isFound();
}

const QHash<QString, AppArgument *> &AppArguments::arguments() const
{
    return m_arguments;
}


#endif // APPARGUMENTS_H
