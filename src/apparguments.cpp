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
#include "apparguments.h"
#include "appargumentconsts.h"
#include "fdsnwslist.h"
#include "consts.h"
#include <sndfile.h>
#include <QDir>


// create unique filename, for example:
// + name = "/tmp/sound"
// + ext  = "wav"
// = /tmp/sound.wav or /tmp/sound(1).wav .. /tmp/sound(N).wav
static QString create_unique_filename(const QString &name, const QString &ext)
{
    if (QFileInfo(QString("%1.%2").arg(name, ext)).exists()) {
        for (int i = 0;; ++i) {
            const QString fileName = QString("%1(%2).%3")
                                     .arg(name)
                                     .arg(QString::number(i))
                                     .arg(ext);
            if (!QFileInfo(fileName).exists()) {
                return fileName;
            }
        }
    }

    return QString("%1.%2").arg(name, ext);
}


AppArguments::AppArguments(const QStringList &cmdlineArguments)
{
    create();
    parseAndValidate(cmdlineArguments);
}

FileNameConflictAction AppArguments::conflictActions() const
{
    const QString action = m_argFileNameConflictAction.toString();
    if (action == "suffix") {
        return FileNameConflictAction::AddSuffix;
    }
    else if (action == "overwrite") {
        return FileNameConflictAction::Overwrite;
    }
    else if (action == "skip") {
        return FileNameConflictAction::Skip;
    }

    Q_ASSERT_X(false, "argument_to_conflictaction", "unknow conflict action");
    return FileNameConflictAction::AddSuffix;
}

int AppArguments::sampleFormat() const
{
    const QString sampleFormat = m_argSampleFormat.toString();
    if (sampleFormat == "i16") {
        return (SF_FORMAT_WAV | SF_FORMAT_PCM_16);
    }
    else if (sampleFormat == "i24") {
        return (SF_FORMAT_WAV | SF_FORMAT_PCM_24);
    }
    else if (sampleFormat == "i32") {
        return (SF_FORMAT_WAV | SF_FORMAT_PCM_32);
    }
    else if (sampleFormat == "f32") {
        return (SF_FORMAT_WAV | SF_FORMAT_FLOAT);
    }
    else if (sampleFormat == "f64") {
        return (SF_FORMAT_WAV | SF_FORMAT_DOUBLE);
    }

    Q_ASSERT_X(false, "argument_to_sampleformat", "unknow sample format");
    return (SF_FORMAT_WAV | SF_FORMAT_PCM_16);
}

int AppArguments::sampleRate() const
{
    return m_argSampleRate.toInt();
}

EventQuery AppArguments::eventQuery() const
{
    EventQuery query;
    if (m_argEventId.isFound())
        query.setId(m_argEventId.toString());
    if (m_argEventMinMag.isFound())
        query.setMinimumMagnitude(m_argEventMinMag.toDouble());
    if (m_argEventMaxMag.isFound())
        query.setMaximumMagnitude(m_argEventMaxMag.toDouble());
    if (m_argEventMinDepth.isFound())
        query.setMinimumDepth(m_argEventMinDepth.toDouble());
    if (m_argEventMaxDepth.isFound())
        query.setMaximumDepth(m_argEventMaxDepth.toDouble());
    if (m_argEventStartTime.isFound())
        query.setStartTime(m_argEventStartTime.toDateTime());
    if (m_argEventEndTime.isFound())
        query.setEndTime(m_argEventEndTime.toDateTime());
    if (m_argEventMinLat.isFound())
        query.setMinimumLatitude(m_argEventMinLat.toDouble());
    if (m_argEventMaxLat.isFound())
        query.setMaximumLatitude(m_argEventMaxLat.toDouble());
    if (m_argEventMinLon.isFound())
        query.setMinimumLongitude(m_argEventMinLon.toDouble());
    if (m_argEventMaxLon.isFound())
        query.setMaximumLongitude(m_argEventMaxLon.toDouble());
    if (m_argEventLat.isFound())
        query.setLatitude(m_argEventLat.toDouble());
    if (m_argEventLon.isFound())
        query.setLongitude(m_argEventLon.toDouble());
    if (m_argEventMinRadius.isFound())
        query.setMinimumRadius(m_argEventMinRadius.toDouble());
    if (m_argEventMaxRadius.isFound())
        query.setMaximumRadius(m_argEventMaxRadius.toDouble());
    if (m_argFdsnwsEventUrl.isFound())
        query.setUrl(m_argFdsnwsEventUrl.toUrl());

    if (m_argEventMaxLat.isFound()) {
        query.setSearchTerms(EventQuery::Box);
    }
    else if (m_argEventMaxRadius.isFound()) {
        query.setSearchTerms(EventQuery::Radial);
    }

    return query;
}

StationQuery AppArguments::stationQuery() const
{
    StationQuery query;
    if (m_argNetwork.isFound())
        query.setNetwork(m_argNetwork.toString());
    if (m_argStation.isFound())
        query.setStation(m_argStation.toString());
    if (m_argChannel.isFound())
        query.setChannel(m_argChannel.toString());
    if (m_argLocation.isFound())
        query.setLocation(m_argLocation.toString());
    if (m_argStartTime.isFound())
        query.setStartTime(m_argStartTime.toDateTime());
    if (m_argEndTime.isFound())
        query.setEndTime(m_argEndTime.toDateTime());
    if (m_argStationMinLat.isFound())
        query.setMinimumLatitude(m_argStationMinLat.toDouble());
    if (m_argStationMaxLat.isFound())
        query.setMaximumLatitude(m_argStationMaxLat.toDouble());
    if (m_argStationMinLon.isFound())
        query.setMinimumLongitude(m_argStationMinLon.toDouble());
    if (m_argStationMaxLon.isFound())
        query.setMaximumLongitude(m_argStationMaxLon.toDouble());
    if (m_argStationLat.isFound())
        query.setLatitude(m_argStationLat.toDouble());
    if (m_argStationLon.isFound())
        query.setLongitude(m_argStationLon.toDouble());
    if (m_argStationMinRadius.isFound())
        query.setMinimumRadius(m_argStationMinRadius.toDouble());
    if (m_argStationMaxRadius.isFound())
        query.setMaximumRadius(m_argStationMaxRadius.toDouble());
    if (m_argFdsnwsStationUrl.isFound())
        query.setUrl(m_argFdsnwsStationUrl.toUrl());

    if (m_argStationMaxLat.isFound()) {
        query.setSearchTerms(StationQuery::Box);
    }
    else if (m_argStationMaxRadius.isFound()) {
        query.setSearchTerms(StationQuery::Radial);
    }

    return query;
}

StationQuery AppArguments::stationQuery(const Event &event) const
{
    StationQuery query = stationQuery();
    // find stations which worked while event happened
    query.setStartTime(event.time().addSecs(-3600));
    query.setEndTime(event.time().addSecs(+3600));

    return query;
}

DataSelectQuery AppArguments::dataSelectQuery(const Trace &trace) const
{
    DataSelectQuery query;
    query.setUrl(m_argFdsnwsDataselectUrl.toUrl());
    query.setNetwork(trace.network());
    query.setStation(trace.station());
    query.setChannel(trace.channel());
    query.setLocation(trace.location());
    if (m_argStartTime.isFound())
        query.setStartTime(m_argStartTime.toDateTime());
    if (m_argEndTime.isFound())
        query.setEndTime(m_argEndTime.toDateTime());

    return query;
}

DataSelectQuery AppArguments::dataSelectQuery(const Event &event,
                                              const Trace &trace) const
{
    const double pi = 3.14159265358979;
    const double radius = 6371116.0;        // the earth radius in meters
    const double lat1 = event.latitude();
    const double lon1 = event.longitude();
    const double lat2 = trace.latitude();
    const double lon2 = trace.longitude();
    // calculate th great-circle distance between earthquake coordinate
    // and seismic station coordinate:
    // https://en.wikipedia.org/wiki/Great-circle_distance
    const double distance =
        radius * acos(sin(lat1 * pi / 180)
                      * sin(lat2 * pi / 180)
                      + (cos(lat1 * pi / 180)
                         * cos(lat2 * pi / 180)
                         * cos(lon1 * pi / 180 - lon2 * pi / 180)));
    // we use the travel-time digaramm for calculate the estimated first
    // phase time. 20min (1200sec) is maximum seismic travel time for
    // first phase, see the
    // http://earthquake.usgs.gov/learn/topics/ttgraph.php
    const int travelTime = 1200 / radius * (distance / 1000.0);
    const QDateTime startTime = event.time().addSecs(travelTime);

    DataSelectQuery query = dataSelectQuery(trace);
    query.setStartTime(startTime.addSecs(-m_argSecondsBefore.toInt()));
    // TODO: we should have possibility for estimate the length
    //       of event by event magnitude
    query.setEndTime(startTime.addSecs(m_argSecondsAfter.toInt()));

    return query;
}

QString AppArguments::fileName(const DataSelectQuery &query) const
{
    QString baseName = m_argFileNameFormat.toString();
    baseName.replace("%eid%", DefaultNoneEventIdName);
    baseName.replace("%net%", query.network());
    baseName.replace("%sta%", query.station());
    baseName.replace("%loc%", query.location());
    baseName.replace("%chan%", query.channel());
    baseName.replace("%starttime%", query.startTime().toString(FileNameDateTimeFormat));
    baseName.replace("%endtime%", query.endTime().toString(FileNameDateTimeFormat));
    baseName = m_argOutputDirectory.toString() + QDir::separator() + baseName;

    if (conflictActions() == FileNameConflictAction::AddSuffix) {
        return create_unique_filename(baseName, "wav");
    }
    else {
        return baseName + ".wav";
    }
}

QString AppArguments::fileName(const Event &event, const DataSelectQuery &query) const
{
    QString baseName = m_argFileNameFormat.toString();
    baseName.replace("%eid%", QString("ID_%1").arg(event.id()));
    baseName.replace("%net%", query.network());
    baseName.replace("%sta%", query.station());
    baseName.replace("%loc%", query.location());
    baseName.replace("%chan%", query.channel());
    baseName.replace("%starttime%", query.startTime().toString(FileNameDateTimeFormat));
    baseName.replace("%endtime%", query.endTime().toString(FileNameDateTimeFormat));
    baseName = m_argOutputDirectory.toString() + QDir::separator() + baseName;

    if (conflictActions() == FileNameConflictAction::AddSuffix) {
        return create_unique_filename(baseName, "wav");
    }
    else {
        return baseName + ".wav";
    }
}

void AppArguments::create()
{
    m_argSampleRate.setType(AppArgument::Integer);
    m_argSampleRate.setFound(true);
    m_argSampleRate.setKey(ArgSampleRate);
    m_argSampleRate.setValue(DefaultSampleRate);
    m_argSampleRate.setIntegerRange(MinimumSampleRate, MaximumSampleRate);
    m_arguments.insert(ArgSampleRate, &m_argSampleRate);

    m_argSampleFormat.setType(AppArgument::String);
    m_argSampleFormat.setFound(true);
    m_argSampleFormat.setKey(ArgSampleFormat);
    m_argSampleFormat.setValue("i16");
    m_argSampleFormat.setStringRegExp(QRegExp("(i16)|(i24)|(i32)|(f32)|(f64)"));
    m_arguments.insert(ArgSampleFormat, &m_argSampleFormat);

    m_argOutputDirectory.setType(AppArgument::String);
    m_argOutputDirectory.setFound(true);
    m_argOutputDirectory.setKey(ArgOutputDirectory);
    m_argOutputDirectory.setValue(QDir::currentPath());
    m_arguments.insert(ArgOutputDirectory, &m_argOutputDirectory);

    m_argFileNameFormat.setType(AppArgument::String);
    m_argFileNameFormat.setFound(true);
    m_argFileNameFormat.setKey(ArgFileNameFormat);
    m_argFileNameFormat.setValue(DefaultSoundFileNameFormat);
    m_arguments.insert(ArgFileNameFormat, &m_argFileNameFormat);

    m_argFileNameConflictAction.setType(AppArgument::String);
    m_argFileNameConflictAction.setFound(true);
    m_argFileNameConflictAction.setKey(ArgFileNameConflictAction);
    m_argFileNameConflictAction.setValue("suffix");
    m_argFileNameConflictAction.setStringRegExp(QRegExp("(suffix)|(overwrite)|(skip)"));
    m_arguments.insert(ArgFileNameConflictAction, &m_argFileNameConflictAction);

    m_argEventId.setType(AppArgument::String);
    m_argEventId.setKey(ArgEventId);
    m_arguments.insert(ArgEventId, &m_argEventId);

    m_argEventStartTime.setType(AppArgument::DateTime);
    m_argEventStartTime.setKey(ArgEventStartTime);
    m_argEventStartTime.setDateTimeFormat(DisplayDateTimeFormat);
    m_arguments.insert(ArgEventStartTime, &m_argEventStartTime);

    m_argEventEndTime.setType(AppArgument::DateTime);
    m_argEventEndTime.setKey(ArgEventEndTime);
    m_argEventEndTime.setDateTimeFormat(DisplayDateTimeFormat);
    m_arguments.insert(ArgEventEndTime, &m_argEventEndTime);

    m_argEventMinMag.setType(AppArgument::Double);
    m_argEventMinMag.setKey(ArgEventMinMag);
    m_argEventMinMag.setIntegerRange(MinimumMagnitude, MaximumMagnitude);
    m_arguments.insert(ArgEventMinMag, &m_argEventMinMag);

    m_argEventMaxMag.setType(AppArgument::Double);
    m_argEventMaxMag.setKey(ArgEventMaxMag);
    m_argEventMaxMag.setIntegerRange(MinimumMagnitude, MaximumMagnitude);
    m_arguments.insert(ArgEventMaxMag, &m_argEventMaxMag);

    m_argEventMinDepth.setType(AppArgument::Double);
    m_argEventMinDepth.setKey(ArgEventMinDepth);
    m_argEventMinDepth.setIntegerRange(MinimumDepth, MaximumDepth);
    m_arguments.insert(ArgEventMinDepth, &m_argEventMinDepth);

    m_argEventMaxDepth.setType(AppArgument::Double);
    m_argEventMaxDepth.setKey(ArgEventMaxDepth);
    m_argEventMaxDepth.setIntegerRange(MinimumDepth, MaximumDepth);
    m_arguments.insert(ArgEventMaxDepth, &m_argEventMaxDepth);

    m_argEventMinLat.setType(AppArgument::Double);
    m_argEventMinLat.setKey(ArgEventMinLat);
    m_argEventMinLat.setIntegerRange(MinimumLatitude, MaximumLatitude);
    m_arguments.insert(ArgEventMinLat, &m_argEventMinLat);

    m_argEventMaxLat.setType(AppArgument::Double);
    m_argEventMaxLat.setKey(ArgEventMaxLat);
    m_argEventMaxLat.setIntegerRange(MinimumLatitude, MaximumLatitude);
    m_arguments.insert(ArgEventMaxLat, &m_argEventMaxLat);

    m_argEventMinLon.setType(AppArgument::Double);
    m_argEventMinLon.setKey(ArgEventMinLon);
    m_argEventMinLon.setIntegerRange(MinimumLongitude, MaximumLongitude);
    m_arguments.insert(ArgEventMinLon, &m_argEventMinLon);

    m_argEventMaxLon.setType(AppArgument::Double);
    m_argEventMaxLon.setKey(ArgEventMaxLon);
    m_argEventMaxLon.setIntegerRange(MinimumLongitude, MaximumLongitude);
    m_arguments.insert(ArgEventMaxLon, &m_argEventMaxLon);

    m_argEventLat.setType(AppArgument::Double);
    m_argEventLat.setKey(ArgEventLat);
    m_argEventLat.setIntegerRange(MinimumLatitude, MaximumLatitude);
    m_arguments.insert(ArgEventLat, &m_argEventLat);

    m_argEventLon.setType(AppArgument::Double);
    m_argEventLon.setKey(ArgEventLon);
    m_argEventLon.setIntegerRange(MinimumLongitude, MaximumLongitude);
    m_arguments.insert(ArgEventLon, &m_argEventLon);

    m_argEventMinRadius.setType(AppArgument::Double);
    m_argEventMinRadius.setKey(ArgEventMinRadius);
    m_argEventMinRadius.setIntegerRange(MinimumRadius, MaximumRadius);
    m_arguments.insert(ArgEventMinRadius, &m_argEventMinRadius);

    m_argEventMaxRadius.setType(AppArgument::Double);
    m_argEventMaxRadius.setKey(ArgEventMaxRadius);
    m_argEventMaxRadius.setIntegerRange(MinimumRadius, MaximumRadius);
    m_arguments.insert(ArgEventMaxRadius, &m_argEventMaxRadius);

    m_argNetwork.setType(AppArgument::String);
    m_argNetwork.setKey(ArgNetwork);
    m_argNetwork.setStringRegExp(QRegExp("^[A-Z0-9\\-\\*\\?]{1,2}$"));
    m_arguments.insert(ArgNetwork, &m_argNetwork);

    m_argStation.setType(AppArgument::String);
    m_argStation.setKey(ArgStation);
    m_argStation.setStringRegExp(QRegExp("^[A-Z0-9\\-\\*\\?]{1,5}$"));
    m_arguments.insert(ArgStation, &m_argStation);

    m_argLocation.setType(AppArgument::String);
    m_argLocation.setKey(ArgLocation);
    m_argLocation.setStringRegExp(QRegExp("^[A-Z0-9\\-\\*\\?]{1,2}$"));
    m_arguments.insert(ArgLocation, &m_argLocation);

    m_argChannel.setType(AppArgument::String);
    m_argChannel.setKey(ArgChannel);
    m_argChannel.setStringRegExp(QRegExp("^[A-Z0-9\\-\\*\\?]{1,3}$"));
    m_arguments.insert(ArgChannel, &m_argChannel);

    m_argStartTime.setType(AppArgument::DateTime);
    m_argStartTime.setKey(ArgStartTime);
    m_argStartTime.setDateTimeFormat(DisplayDateTimeFormat);
    m_arguments.insert(ArgStartTime, &m_argStartTime);

    m_argEndTime.setType(AppArgument::DateTime);
    m_argEndTime.setKey(ArgEndTime);
    m_argEndTime.setDateTimeFormat(DisplayDateTimeFormat);
    m_arguments.insert(ArgEndTime, &m_argEndTime);

    m_argStationMinLat.setType(AppArgument::Double);
    m_argStationMinLat.setKey(ArgStationMinLat);
    m_argStationMinLat.setIntegerRange(MinimumLatitude, MaximumLatitude);
    m_arguments.insert(ArgStationMinLat, &m_argStationMinLat);

    m_argStationMaxLat.setType(AppArgument::Double);
    m_argStationMaxLat.setKey(ArgStationMaxLat);
    m_argStationMaxLat.setIntegerRange(MinimumLatitude, MaximumLatitude);
    m_arguments.insert(ArgStationMaxLat, &m_argStationMaxLat);

    m_argStationMinLon.setType(AppArgument::Double);
    m_argStationMinLon.setKey(ArgStationMinLon);
    m_argStationMinLon.setIntegerRange(MinimumLongitude, MaximumLongitude);
    m_arguments.insert(ArgStationMinLon, &m_argStationMinLon);

    m_argStationMaxLon.setType(AppArgument::Double);
    m_argStationMaxLon.setKey(ArgStationMaxLon);
    m_argStationMaxLon.setIntegerRange(MinimumLongitude, MaximumLongitude);
    m_arguments.insert(ArgStationMaxLon, &m_argStationMaxLon);

    m_argStationLat.setType(AppArgument::Double);
    m_argStationLat.setKey(ArgStationLat);
    m_argStationLat.setIntegerRange(MinimumLatitude, MaximumLatitude);
    m_arguments.insert(ArgStationLat, &m_argStationLat);

    m_argStationLon.setType(AppArgument::Double);
    m_argStationLon.setKey(ArgStationLon);
    m_argStationLon.setIntegerRange(MinimumLongitude, MaximumLongitude);
    m_arguments.insert(ArgStationLon, &m_argStationLon);

    m_argStationMinRadius.setType(AppArgument::Double);
    m_argStationMinRadius.setKey(ArgStationMinRadius);
    m_argStationMinRadius.setIntegerRange(MinimumRadius, MaximumRadius);
    m_arguments.insert(ArgStationMinRadius, &m_argStationMinRadius);

    m_argStationMaxRadius.setType(AppArgument::Double);
    m_argStationMaxRadius.setKey(ArgStationMaxRadius);
    m_argStationMaxRadius.setIntegerRange(MinimumRadius, MaximumRadius);
    m_arguments.insert(ArgStationMaxRadius, &m_argStationMaxRadius);

    m_argLimit.setType(AppArgument::Integer);
    m_argLimit.setFound(true);
    m_argLimit.setKey(ArgLimit);
    m_argLimit.setValue(MaximumLimit);
    m_argLimit.setIntegerRange(MinimumLimit, MaximumLimit);
    m_arguments.insert(ArgLimit, &m_argLimit);

    m_argLimitPerEvent.setType(AppArgument::Integer);
    m_argLimitPerEvent.setFound(true);
    m_argLimitPerEvent.setKey(ArgLimitPerEvent);
    m_argLimitPerEvent.setValue(MaximumLimit);
    m_argLimitPerEvent.setIntegerRange(MinimumLimit, MaximumLimit);
    m_arguments.insert(ArgLimitPerEvent, &m_argLimitPerEvent);

    m_argSecondsBefore.setType(AppArgument::Integer);
    m_argSecondsBefore.setFound(true);
    m_argSecondsBefore.setKey(ArgSecondsBefore);
    m_argSecondsBefore.setValue(DefaultSecondsBefore);
    m_arguments.insert(ArgSecondsBefore, &m_argSecondsBefore);

    m_argSecondsAfter.setType(AppArgument::Integer);
    m_argSecondsAfter.setFound(true);
    m_argSecondsAfter.setKey(ArgSecondsAfter);
    m_argSecondsAfter.setValue(DefaultSecondsAfter);
    m_arguments.insert(ArgSecondsAfter, &m_argSecondsAfter);

    m_argFdsnwsDataselectUrl.setType(AppArgument::Url);
    m_argFdsnwsDataselectUrl.setFound(true);
    m_argFdsnwsDataselectUrl.setKey(ArgFdsnwsDataselectUrl);
    m_argFdsnwsDataselectUrl.setValue(fdsnws_dataselect_url(fdsnws_dataselect_default_code()));
    m_arguments.insert(ArgFdsnwsDataselectUrl, &m_argFdsnwsDataselectUrl);

    m_argFdsnwsStationUrl.setType(AppArgument::Url);
    m_argFdsnwsStationUrl.setFound(true);
    m_argFdsnwsStationUrl.setKey(ArgFdsnwsStationUrl);
    m_argFdsnwsStationUrl.setValue(fdsnws_station_url(fdsnws_station_default_code()));
    m_arguments.insert(ArgFdsnwsStationUrl, &m_argFdsnwsStationUrl);

    m_argFdsnwsEventUrl.setType(AppArgument::Url);
    m_argFdsnwsEventUrl.setFound(true);
    m_argFdsnwsEventUrl.setKey(ArgFdsnwsEventUrl);
    m_argFdsnwsEventUrl.setValue(fdsnws_event_url(fdsnws_event_default_code()));
    m_arguments.insert(ArgFdsnwsEventUrl, &m_argFdsnwsEventUrl);

    m_argPrintFdsnwsDataselectServices.setType(AppArgument::Bool);
    m_argPrintFdsnwsDataselectServices.setKey(ArgPrintFdsnwsDataselectServices);
    m_arguments.insert(ArgPrintFdsnwsDataselectServices, &m_argPrintFdsnwsDataselectServices);

    m_argPrintFdsnwsStationServices.setType(AppArgument::Bool);
    m_argPrintFdsnwsStationServices.setKey(ArgPrintFdsnwsStationServices);
    m_arguments.insert(ArgPrintFdsnwsStationServices, &m_argPrintFdsnwsStationServices);

    m_argPrintFdsnwsEventServices.setType(AppArgument::Bool);
    m_argPrintFdsnwsEventServices.setKey(ArgPrintFdsnwsEventServices);
    m_arguments.insert(ArgPrintFdsnwsEventServices, &m_argPrintFdsnwsEventServices);

    m_argPrintFdsnwsServices.setType(AppArgument::Bool);
    m_argPrintFdsnwsServices.setKey(ArgPrintFdsnwsServices);
    m_arguments.insert(ArgPrintFdsnwsServices, &m_argPrintFdsnwsServices);

    m_argPrintSelectedEvents.setType(AppArgument::Bool);
    m_argPrintSelectedEvents.setKey(ArgPrintSelectedEvents);
    m_arguments.insert(ArgPrintSelectedEvents, &m_argPrintSelectedEvents);

    m_argPrintSelectedTraces.setType(AppArgument::Bool);
    m_argPrintSelectedTraces.setKey(ArgPrintSelectedTraces);
    m_arguments.insert(ArgPrintSelectedTraces, &m_argPrintSelectedTraces);

    m_argSelectedEventsFormat.setType(AppArgument::String);
    m_argSelectedEventsFormat.setFound(true);
    m_argSelectedEventsFormat.setKey(ArgSelectedEventsFormat);
    m_argSelectedEventsFormat.setValue(DefaultShowEventsFormat);
    m_arguments.insert(ArgSelectedEventsFormat, &m_argSelectedEventsFormat);

    m_argSelectedTracesFormat.setType(AppArgument::String);
    m_argSelectedTracesFormat.setFound(true);
    m_argSelectedTracesFormat.setKey(ArgSelectedTracesFormat);
    m_argSelectedTracesFormat.setValue(DefaultShowStationFormat);
    m_arguments.insert(ArgSelectedTracesFormat, &m_argSelectedTracesFormat);

    m_argDebug.setType(AppArgument::Bool);
    m_argDebug.setKey(ArgDebug);
    m_arguments.insert(ArgDebug, &m_argDebug);

    m_argHelp.setType(AppArgument::Bool);
    m_argHelp.setKey(ArgHelp);
    m_arguments.insert(ArgHelp, &m_argHelp);
}

void AppArguments::parseAndValidate(const QStringList &cmdlineArguments)
{
    try {
        for (int index = 1; index < cmdlineArguments.count();) {
            const QString &key = cmdlineArguments.at(index);

            // special cases
            if (key == ArgPrintFdsnwsServices) {
                m_argPrintFdsnwsDataselectServices.setFound(true);
                m_argPrintFdsnwsStationServices.setFound(true);
                m_argPrintFdsnwsEventServices.setFound(true);
            }
            else if (key == ArgFdsnwsDataselectUrl) {
                if (index + 1 >= cmdlineArguments.count()) {
                    throw QObject::tr("\'%1\' must have an argument").arg(key);
                }

                const QString &value = cmdlineArguments.at(index + 1);
                if (fdsnws_dataselect_contains(value)) {
                    m_argFdsnwsDataselectUrl.setFound(true);
                    m_argFdsnwsDataselectUrl.setValue(fdsnws_dataselect_url(value));
                }
                else {
                    m_argFdsnwsDataselectUrl.setValue(value);
                }
            }
            else if (key == ArgFdsnwsStationUrl) {
                if (index + 1 >= cmdlineArguments.count()) {
                    throw QObject::tr("\'%1\' must have an argument").arg(key);
                }

                const QString &value = cmdlineArguments.at(index + 1);
                if (fdsnws_station_contains(value)) {
                    m_argFdsnwsStationUrl.setFound(true);
                    m_argFdsnwsStationUrl.setValue(fdsnws_station_url(value));
                }
                else {
                    m_argFdsnwsStationUrl.setValue(value);
                }
            }
            else if (key == ArgFdsnwsEventUrl) {
                if (index + 1 >= cmdlineArguments.count()) {
                    throw QObject::tr("\'%1\' must have an argument").arg(key);
                }

                const QString &value = cmdlineArguments.at(index + 1);
                if (fdsnws_event_contains(value)) {
                    m_argFdsnwsEventUrl.setFound(true);
                    m_argFdsnwsEventUrl.setValue(fdsnws_event_url(value));
                }
                else {
                    m_argFdsnwsEventUrl.setValue(value);
                }
            }
            // common cases
            else {
                if (!m_arguments.contains(key)) {
                    throw QObject::tr("\'%1\' invalid option").arg(key);
                }

                if (m_arguments[key]->type() == AppArgument::Bool) {
                    m_arguments[key]->setFound(true);
                }
                else {
                    if (index + 1 >= cmdlineArguments.count()) {
                        throw QObject::tr("\'%1\' must have an argument").arg(key);
                    }

                    m_arguments[key]->setFound(true);
                    m_arguments[key]->setValue(cmdlineArguments.at(index + 1));
                }
            }

            if (m_arguments[key]->type() == AppArgument::Bool) {
                index += 1;
            }
            else {
                index += 2;
            }
        }

        // validate the each argument
        QHashIterator<QString, AppArgument *> argument(m_arguments);
        while (argument.hasNext()) {
            argument.next();

            if (!argument.value()->validate(&m_lastError)) {
                return;
            }
        }

        // -- event ---
        // event start/end time
        if (m_argEventStartTime.isFound() && m_argEventEndTime.isFound()) {
            if (m_argEventStartTime.toDateTime() >= m_argEventEndTime.toDateTime()) {
                throw QObject::tr("event start time must be less than event end time");
            }
        }

        // event min/max magnitude
        if (m_argEventMinMag.isFound() && m_argEventMaxMag.isFound()) {
            if (m_argEventMinMag.toDouble() >= m_argEventMaxMag.toDouble()) {
                throw QObject::tr("event minimum magnitude must be less than event maximum magnitude");
            }
        }

        // event min/max depth
        if (m_argEventMinDepth.isFound() && m_argEventMaxDepth.isFound()) {
            if (m_argEventMinDepth.toDouble() >= m_argEventMaxDepth.toDouble()) {
                throw QObject::tr("event minimum depth must be less than event maximum depth");
            }
        }

        // event min/max latitude
        if (m_argEventMinLat.isFound() && m_argEventMaxLat.isFound()) {
            if (m_argEventMinLat.toDouble() >= m_argEventMaxLat.toDouble()) {
                throw QObject::tr("event minimum latitude must be less than event maximum latitude");
            }
        }

        // event min/max longitude
        if (m_argEventMinLon.isFound() && m_argEventMaxLon.isFound()) {
            if (m_argEventMinLon.toDouble() >= m_argEventMaxLon.toDouble()) {
                throw QObject::tr("event minimum longitude must be less than event maximum longitude");
            }
        }

        // event min/max radius
        if (m_argEventMinRadius.isFound() && m_argEventMaxRadius.isFound()) {
            if (m_argEventMinRadius.toDouble() >= m_argEventMaxRadius.toDouble()) {
                throw QObject::tr("event minimum radius must be less than event maximum radius");
            }
        }

        // event BOX or RADIAL search terms
        if ((m_argEventMinLat.isFound()
                || m_argEventMaxLat.isFound()
                || m_argEventMinLon.isFound()
                || m_argEventMaxLon.isFound())
                && (m_argEventLat.isFound()
                    || m_argEventLon.isFound()
                    || m_argEventMinRadius.isFound()
                    || m_argEventMaxRadius.isFound())) {
            throw QObject::tr("event can have only BOX search terms or RADIAL search terms");
        }


        // event BOX search terms has empty fields
        if ((m_argEventMinLat.isFound()
                || m_argEventMaxLat.isFound()
                || m_argEventMinLon.isFound()
                || m_argEventMaxLon.isFound())
                && (!m_argEventMinLat.isFound()
                    || !m_argEventMaxLat.isFound()
                    || !m_argEventMinLon.isFound()
                    || !m_argEventMaxLon.isFound())) {
            throw QObject::tr("event BOX search terms has empty fields");
        }

        // event RADIAL search terms has empty fields
        if ((m_argEventLat.isFound()
                || m_argEventLon.isFound()
                || m_argEventMinRadius.isFound()
                || m_argEventMaxRadius.isFound())
                && (!m_argEventLat.isFound()
                    || !m_argEventLon.isFound()
                    || !m_argEventMinRadius.isFound()
                    || !m_argEventMaxRadius.isFound())) {
            throw QObject::tr("event RADIAL search terms has empty fields");
        }


        // -- trace ---
        // data start/end time
        if (m_argStartTime.isFound() && m_argEndTime.isFound()) {
            if (m_argStartTime.toDateTime() >= m_argEndTime.toDateTime()) {
                throw QObject::tr("data start time must be less than data end time");
            }
        }

        // data start/end time must be defined together or not defined
        if ((m_argStartTime.isFound() || m_argEndTime.isFound())
                && (!m_argStartTime.isFound() || !m_argEndTime.isFound())) {
            throw QObject::tr("start time and end time must be setted together");
        }


        // -- station ---
        // station min/max latitude
        if (m_argStationMinLat.isFound() && m_argStationMaxLat.isFound()) {
            if (m_argStationMinLat.toDouble() >= m_argStationMaxLat.toDouble()) {
                throw QObject::tr("station minimum latitude must be less than station maximum latitude");
            }
        }

        // station min/max longitude
        if (m_argStationMinLon.isFound() && m_argStationMaxLon.isFound()) {
            if (m_argStationMinLon.toDouble() >= m_argStationMaxLon.toDouble()) {
                throw QObject::tr("station minimum longitude must be less than station maximum longitude");
            }
        }

        // station min/max radius
        if (m_argStationMinRadius.isFound() && m_argStationMaxRadius.isFound()) {
            if (m_argStationMinRadius.toDouble() >= m_argStationMaxRadius.toDouble()) {
                throw QObject::tr("station minimum radius must be less than station maximum radius");
            }
        }

        // station BOX or RADIAL search terms
        if ((m_argStationMinLat.isFound()
                || m_argStationMaxLat.isFound()
                || m_argStationMinLon.isFound()
                || m_argStationMaxLon.isFound())
                && (m_argStationLat.isFound()
                    || m_argStationLon.isFound()
                    || m_argStationMinRadius.isFound()
                    || m_argStationMaxRadius.isFound())) {
            throw QObject::tr("station can have only BOX search terms or RADIAL search terms");
        }

        // station BOX search terms has empty fields
        if ((m_argStationMinLat.isFound()
                || m_argStationMaxLat.isFound()
                || m_argStationMinLon.isFound()
                || m_argStationMaxLon.isFound())
                && (!m_argStationMinLat.isFound()
                    || !m_argStationMaxLat.isFound()
                    || !m_argStationMinLon.isFound()
                    || !m_argStationMaxLon.isFound())) {
            throw QObject::tr("station BOX search terms has empty fields");
        }

        // station RADIAL search terms has empty fields
        if ((m_argStationLat.isFound()
                || m_argStationLon.isFound()
                || m_argStationMinRadius.isFound()
                || m_argStationMaxRadius.isFound())
                && (!m_argStationLat.isFound()
                    || !m_argStationLon.isFound()
                    || !m_argStationMinRadius.isFound()
                    || !m_argStationMaxRadius.isFound())) {
            throw QObject::tr("station RADIAL search terms has empty fields");
        }
    }
    catch (const QString &errorString) {
        m_lastError = errorString;
    }
}
