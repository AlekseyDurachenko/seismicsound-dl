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
#include "debug.h"
#include "appargumentconsts.h"
#include <iostream>


static QString argument_to_printable(const AppArgument &argument)
{
    if (argument.isFound()) {
        switch (argument.type()) {
        case AppArgument::Bool:
            return QString("true");
        case AppArgument::Integer:
            return QString::number(argument.toInt());
        case AppArgument::Double:
            return QString::number(argument.toDouble(), 'f', 6);
        case AppArgument::String:
            return argument.toString();
        case AppArgument::DateTime:
            return argument.toDateTime().toString(DisplayDateTimeFormat);
        case AppArgument::Url:
            return argument.toUrl().toString();
        }
    }
    else if (argument.type() == AppArgument::Bool) {
        return QString("false");
    }

    return QString();
}


void debug_print(const QString &string)
{
    std::cout << QObject::tr("DEBUG: %1", "debug").arg(string).toStdString() << std::endl;
}


void debug_print(const AppArguments &arguments, const QString &string)
{
    if (arguments.hasDebug()) {
        debug_print(string);
    }
}


void debug_print(const AppArguments &arguments)
{
    // print arguments only if debug is enabled
    if (!arguments.hasDebug()) {
        return;
    }

    // correct order of argument list
    QStringList keys
        = QStringList()
          << ArgSampleRate
          << ArgSampleFormat
          << ArgOutputDirectory
          << ArgFileNameFormat
          << ArgFileNameConflictAction
          << ArgEventId
          << ArgEventStartTime
          << ArgEventEndTime
          << ArgEventMinMag
          << ArgEventMaxMag
          << ArgEventMinDepth
          << ArgEventMaxDepth
          << ArgEventMinLat
          << ArgEventMaxLat
          << ArgEventMinLon
          << ArgEventMaxLon
          << ArgEventLat
          << ArgEventLon
          << ArgEventMinRadius
          << ArgEventMaxRadius
          << ArgNetwork
          << ArgStation
          << ArgLocation
          << ArgChannel
          << ArgStartTime
          << ArgEndTime
          << ArgStationMinLat
          << ArgStationMaxLat
          << ArgStationMinLon
          << ArgStationMaxLon
          << ArgStationLat
          << ArgStationLon
          << ArgStationMinRadius
          << ArgStationMaxRadius
          << ArgLimit
          << ArgLimitPerEvent
          << ArgSecondsBefore
          << ArgSecondsAfter
          << ArgFdsnwsDataselectUrl
          << ArgFdsnwsStationUrl
          << ArgFdsnwsEventUrl
          << ArgPrintFdsnwsDataselectServices
          << ArgPrintFdsnwsStationServices
          << ArgPrintFdsnwsEventServices
          << ArgPrintSelectedEvents
          << ArgSelectedEventsFormat
          << ArgPrintSelectedTraces
          << ArgSelectedTracesFormat
          << ArgDebug
          << ArgHelp;

    // find the maximum length
    int maxLen = 0;
    foreach (const QString &key, keys) {
        if (arguments.arguments().value(key)->isFound()) {
            maxLen = qMax(maxLen, key.length());
        }
    }

    debug_print(QObject::tr("Command-line arguments", "debug"));

    // print all values
    foreach (const QString &key, keys) {
        if (arguments.arguments().value(key)->isFound()) {
            debug_print(QString("%1%2: %3")
                        .arg(key)
                        .arg(QString(), maxLen - key.length(), '.')
                        .arg(argument_to_printable(*arguments.arguments().value(key))));
        }
    }
}


void debug_print(const AppArguments &arguments, const EventQuery &query)
{
    // print arguments only if debug is enabled
    if (!arguments.hasDebug()) {
        return;
    }

    debug_print(QObject::tr("EventQuery", "debug"));

    switch (query.searchTerms()) {
    case EventQuery::All:
        debug_print(QObject::tr("->searchTerms().....: All", "debug"));
        break;
    case EventQuery::Box:
        debug_print(QObject::tr("->searchTerms().....: Box", "debug"));
        break;
    case EventQuery::Radial:
        debug_print(QObject::tr("->searchTerms().....: Radial", "debug"));
        break;
    }

    if (!query.id().isEmpty())
        debug_print(QObject::tr("->id()..............: %1", "debug").arg(query.id()));
    if (query.startTime().isValid())
        debug_print(QObject::tr("->startTime().......: %1", "debug").arg(query.startTime().toString(DisplayDateTimeFormat)));
    if (query.endTime().isValid())
        debug_print(QObject::tr("->endTime().........: %1", "debug").arg(query.endTime().toString(DisplayDateTimeFormat)));
    if (!qFuzzyCompare(query.minimumMagnitude(), InvalidMagnitude))
        debug_print(QObject::tr("->minimumMagnitude(): %1", "debug").arg(query.minimumMagnitude(), 0, 'f', 6));
    if (!qFuzzyCompare(query.maximumMagnitude(), InvalidMagnitude))
        debug_print(QObject::tr("->maximumMagnitude(): %1", "debug").arg(query.maximumMagnitude(), 0, 'f', 6));
    if (!qFuzzyCompare(query.minimumDepth(), InvalidDepth))
        debug_print(QObject::tr("->minimumDepth()....: %1", "debug").arg(query.minimumDepth(), 0, 'f', 6));
    if (!qFuzzyCompare(query.maximumDepth(), InvalidDepth))
        debug_print(QObject::tr("->maximumDepth()....: %1", "debug").arg(query.maximumDepth(), 0, 'f', 6));
    if (!qFuzzyCompare(query.minimumLatitude(), InvalidLatitude))
        debug_print(QObject::tr("->minimumLatitude().: %1", "debug").arg(query.minimumLatitude(), 0, 'f', 6));
    if (!qFuzzyCompare(query.maximumLatitude(), InvalidLatitude))
        debug_print(QObject::tr("->maximumLatitude().: %1", "debug").arg(query.maximumLatitude(), 0, 'f', 6));
    if (!qFuzzyCompare(query.minimumLongitude(), InvalidLongitude))
        debug_print(QObject::tr("->minimumLongitude(): %1", "debug").arg(query.minimumLongitude(), 0, 'f', 6));
    if (!qFuzzyCompare(query.maximumLongitude(), InvalidLongitude))
        debug_print(QObject::tr("->maximumLongitude(): %1", "debug").arg(query.maximumLongitude(), 0, 'f', 6));
    if (!qFuzzyCompare(query.latitude(), InvalidLatitude))
        debug_print(QObject::tr("->latitude()........: %1", "debug").arg(query.latitude(), 0, 'f', 6));
    if (!qFuzzyCompare(query.longitude(), InvalidLongitude))
        debug_print(QObject::tr("->longitude().......: %1", "debug").arg(query.longitude(), 0, 'f', 6));
    if (!qFuzzyCompare(query.minimumRadius(), InvalidRadius))
        debug_print(QObject::tr("->minimumRadius()...: %1", "debug").arg(query.minimumRadius(), 0, 'f', 6));
    if (!qFuzzyCompare(query.maximumRadius(), InvalidRadius))
        debug_print(QObject::tr("->maximumRadius()...: %1", "debug").arg(query.maximumRadius(), 0, 'f', 6));
    if (query.url().isValid())
        debug_print(QObject::tr("->url().............: %1", "debug").arg(query.url().toString()));
    if (query.limit() != InvalidLimit)
        debug_print(QObject::tr("->limit()...........: %1", "debug").arg(query.limit()));
    if (query.offset() != InvalidOffset)
        debug_print(QObject::tr("->offset()..........: %1", "debug").arg(query.offset()));
    if (query.buildQueryUrl().isValid())
        debug_print(QObject::tr("->buildQueryUrl()...: %1", "debug").arg(query.buildQueryUrl().toString()));
}


void debug_print(const AppArguments &arguments, const StationQuery &query)
{
    // print arguments only if debug is enabled
    if (!arguments.hasDebug()) {
        return;
    }

    debug_print(QObject::tr("StationQuery", "debug"));

    switch (query.searchTerms()) {
    case EventQuery::All:
        debug_print(QObject::tr("->searchTerms().....: All", "debug"));
        break;
    case EventQuery::Box:
        debug_print(QObject::tr("->searchTerms().....: Box", "debug"));
        break;
    case EventQuery::Radial:
        debug_print(QObject::tr("->searchTerms().....: Radial", "debug"));
        break;
    }

    if (!query.network().isEmpty())
        debug_print(QObject::tr("->network().........: %1", "debug").arg(query.network()));
    if (!query.station().isEmpty())
        debug_print(QObject::tr("->station().........: %1", "debug").arg(query.station()));
    if (!query.channel().isEmpty())
        debug_print(QObject::tr("->channel().........: %1", "debug").arg(query.channel()));
    if (!query.location().isEmpty())
        debug_print(QObject::tr("->location()........: %1", "debug").arg(query.location()));
    if (query.startTime().isValid())
        debug_print(QObject::tr("->startTime().......: %1", "debug").arg(query.startTime().toString(DisplayDateTimeFormat)));
    if (query.endTime().isValid())
        debug_print(QObject::tr("->endTime().........: %1", "debug").arg(query.endTime().toString(DisplayDateTimeFormat)));
    if (!qFuzzyCompare(query.minimumLatitude(), InvalidLatitude))
        debug_print(QObject::tr("->minimumLatitude().: %1", "debug").arg(query.minimumLatitude(), 0, 'f', 6));
    if (!qFuzzyCompare(query.maximumLatitude(), InvalidLatitude))
        debug_print(QObject::tr("->maximumLatitude().: %1", "debug").arg(query.maximumLatitude(), 0, 'f', 6));
    if (!qFuzzyCompare(query.minimumLongitude(), InvalidLongitude))
        debug_print(QObject::tr("->minimumLongitude(): %1", "debug").arg(query.minimumLongitude(), 0, 'f', 6));
    if (!qFuzzyCompare(query.maximumLongitude(), InvalidLongitude))
        debug_print(QObject::tr("->maximumLongitude(): %1", "debug").arg(query.maximumLongitude(), 0, 'f', 6));
    if (!qFuzzyCompare(query.latitude(), InvalidLatitude))
        debug_print(QObject::tr("->latitude()........: %1", "debug").arg(query.latitude(), 0, 'f', 6));
    if (!qFuzzyCompare(query.longitude(), InvalidLongitude))
        debug_print(QObject::tr("->longitude().......: %1", "debug").arg(query.longitude(), 0, 'f', 6));
    if (!qFuzzyCompare(query.minimumRadius(), InvalidRadius))
        debug_print(QObject::tr("->minimumRadius()...: %1", "debug").arg(query.minimumRadius(), 0, 'f', 6));
    if (!qFuzzyCompare(query.maximumRadius(), InvalidRadius))
        debug_print(QObject::tr("->maximumRadius()...: %1", "debug").arg(query.maximumRadius(), 0, 'f', 6));
    if (query.url().isValid())
        debug_print(QObject::tr("->url().............: %1", "debug").arg(query.url().toString()));
    if (query.buildQueryUrl().isValid())
        debug_print(QObject::tr("->buildQueryUrl()...: %1", "debug").arg(query.buildQueryUrl().toString()));
}


void debug_print(const AppArguments &arguments, const DataSelectQuery &query)
{
    // print arguments only if debug is enabled
    if (!arguments.hasDebug()) {
        return;
    }

    debug_print(QObject::tr("DataSelectQuery", "debug"));
    debug_print(QObject::tr("->network()......: %1", "debug").arg(query.network()));
    debug_print(QObject::tr("->station()......: %1", "debug").arg(query.station()));
    debug_print(QObject::tr("->location().....: %1", "debug").arg(query.location()));
    debug_print(QObject::tr("->channel()......: %1", "debug").arg(query.channel()));
    debug_print(QObject::tr("->startTime()....: %1", "debug").arg(query.startTime().toString(DisplayDateTimeFormat)));
    debug_print(QObject::tr("->endTime()......: %1", "debug").arg(query.endTime().toString(DisplayDateTimeFormat)));
    debug_print(QObject::tr("->url()..........: %1", "debug").arg(query.url().toString()));
    debug_print(QObject::tr("->buildQueryUrl(): %1", "debug").arg(query.buildQueryUrl().toString()));
}


void debug_print(const AppArguments &arguments, const SoundTags &tags)
{
    // print arguments only if debug is enabled
    if (!arguments.hasDebug()) {
        return;
    }

    debug_print(QObject::tr("SoundTags", "debug"));
    debug_print(QObject::tr("->artist()...: %1", "debug").arg(tags.artist()));
    debug_print(QObject::tr("->title()....: %1", "debug").arg(tags.title()));
    debug_print(QObject::tr("->date().....: %1", "debug").arg(tags.date()));
    debug_print(QObject::tr("->genre()....: %1", "debug").arg(tags.genre()));
    debug_print(QObject::tr("->copyright(): %1", "debug").arg(tags.copyright()));
    debug_print(QObject::tr("->software().: %1", "debug").arg(tags.software()));
    debug_print(QObject::tr("->comment()..: %1", "debug").arg(tags.comment()));
}
