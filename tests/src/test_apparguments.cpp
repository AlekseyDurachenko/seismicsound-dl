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
#include "test_apparguments.h"
#include "apparguments.h"
#include "appargumentconsts.h"
#include "consts.h"
#include <sndfile.h>


Test_AppArguments::Test_AppArguments(QObject *parent)
    : QObject(parent)
{
}


void Test_AppArguments::defaultConstructor()
{
    AppArguments args;
    QVERIFY(args.arguments().contains(ArgSampleRate));
    QVERIFY(args.arguments().contains(ArgSampleFormat));
    QVERIFY(args.arguments().contains(ArgOutputDirectory));
    QVERIFY(args.arguments().contains(ArgFileNameFormat));
    QVERIFY(args.arguments().contains(ArgFileNameConflictAction));
    QVERIFY(args.arguments().contains(ArgEventId));
    QVERIFY(args.arguments().contains(ArgEventStartTime));
    QVERIFY(args.arguments().contains(ArgEventEndTime));
    QVERIFY(args.arguments().contains(ArgEventMinMag));
    QVERIFY(args.arguments().contains(ArgEventMaxMag));
    QVERIFY(args.arguments().contains(ArgEventMinDepth));
    QVERIFY(args.arguments().contains(ArgEventMaxDepth));
    QVERIFY(args.arguments().contains(ArgEventMinLat));
    QVERIFY(args.arguments().contains(ArgEventMaxLat));
    QVERIFY(args.arguments().contains(ArgEventMinLon));
    QVERIFY(args.arguments().contains(ArgEventMaxLon));
    QVERIFY(args.arguments().contains(ArgEventLat));
    QVERIFY(args.arguments().contains(ArgEventLon));
    QVERIFY(args.arguments().contains(ArgEventMinRadius));
    QVERIFY(args.arguments().contains(ArgEventMaxRadius));
    QVERIFY(args.arguments().contains(ArgNetwork));
    QVERIFY(args.arguments().contains(ArgStation));
    QVERIFY(args.arguments().contains(ArgLocation));
    QVERIFY(args.arguments().contains(ArgChannel));
    QVERIFY(args.arguments().contains(ArgStartTime));
    QVERIFY(args.arguments().contains(ArgEndTime));
    QVERIFY(args.arguments().contains(ArgStationMinLat));
    QVERIFY(args.arguments().contains(ArgStationMaxLat));
    QVERIFY(args.arguments().contains(ArgStationMinLon));
    QVERIFY(args.arguments().contains(ArgStationMaxLon));
    QVERIFY(args.arguments().contains(ArgStationLat));
    QVERIFY(args.arguments().contains(ArgStationLon));
    QVERIFY(args.arguments().contains(ArgStationMinRadius));
    QVERIFY(args.arguments().contains(ArgStationMaxRadius));
    QVERIFY(args.arguments().contains(ArgLimit));
    QVERIFY(args.arguments().contains(ArgLimitPerEvent));
    QVERIFY(args.arguments().contains(ArgSecondsBefore));
    QVERIFY(args.arguments().contains(ArgSecondsAfter));
    QVERIFY(args.arguments().contains(ArgFdsnwsDataselectUrl));
    QVERIFY(args.arguments().contains(ArgFdsnwsStationUrl));
    QVERIFY(args.arguments().contains(ArgFdsnwsEventUrl));
    QVERIFY(args.arguments().contains(ArgPrintFdsnwsDataselectServices));
    QVERIFY(args.arguments().contains(ArgPrintFdsnwsStationServices));
    QVERIFY(args.arguments().contains(ArgPrintFdsnwsEventServices));
    QVERIFY(args.arguments().contains(ArgPrintFdsnwsServices));
    QVERIFY(args.arguments().contains(ArgPrintSelectedEvents));
    QVERIFY(args.arguments().contains(ArgSelectedEventsFormat));
    QVERIFY(args.arguments().contains(ArgPrintSelectedTraces));
    QVERIFY(args.arguments().contains(ArgSelectedTracesFormat));
    QVERIFY(args.arguments().contains(ArgDebug));
    QVERIFY(args.arguments().contains(ArgHelp));
}


void Test_AppArguments::test_001()
{
    QStringList cmdlineArgs
        = QStringList()
          << "seismicsound-dl"
          << ArgSampleRate             << "1100"
          << ArgSampleFormat           << "f32"
          << ArgOutputDirectory        << "/mnt/tmp/"
          << ArgFileNameFormat         << "some_format"
          << ArgFileNameConflictAction << "skip"
          << ArgEventId                     << "123456"
          << ArgEventStartTime              << "2011-01-02T03:04:05"
          << ArgEventEndTime                << "2012-01-02T03:04:05"
          << ArgEventMinMag                 << "1.1"
          << ArgEventMaxMag                 << "2.2"
          << ArgEventMinDepth               << "3.3"
          << ArgEventMaxDepth               << "4.4"
          << ArgEventMinLat                 << "10.1"
          << ArgEventMaxLat                 << "10.2"
          << ArgEventMinLon                 << "10.3"
          << ArgEventMaxLon                 << "10.4"
          << ArgNetwork                     << "AA"
          << ArgStation                     << "BBBBB"
          << ArgLocation                    << "00"
          << ArgChannel                     << "CCC"
          << ArgStartTime                   << "2013-01-02T03:04:05"
          << ArgEndTime                     << "2014-01-02T03:04:05"
          << ArgStationMinLat               << "20.1"
          << ArgStationMaxLat               << "20.2"
          << ArgStationMinLon               << "20.3"
          << ArgStationMaxLon               << "20.4"
          << ArgLimit                       << "30"
          << ArgLimitPerEvent               << "40"
          << ArgSecondsBefore               << "100"
          << ArgSecondsAfter                << "1000"
          << ArgFdsnwsDataselectUrl         << "0010"
          << ArgFdsnwsStationUrl            << "0010"
          << ArgFdsnwsEventUrl              << "0010"
          << ArgPrintFdsnwsDataselectServices
          << ArgPrintFdsnwsStationServices
          << ArgPrintFdsnwsEventServices
          << ArgPrintSelectedEvents
          << ArgSelectedEventsFormat          << "zzz"
          << ArgPrintSelectedTraces
          << ArgSelectedTracesFormat          << "xxx"
          << ArgDebug
          << ArgHelp;



    AppArguments appArgs(cmdlineArgs);
    QCOMPARE(appArgs.hasError(), false);

    const QHash<QString, AppArgument *> &arguments = appArgs.arguments();
    QCOMPARE(arguments[ArgSampleRate]->toInt(),  1100);
    QCOMPARE(appArgs.sampleFormat(), (SF_FORMAT_WAV | SF_FORMAT_FLOAT));
    QCOMPARE(arguments[ArgOutputDirectory]->toString(), QString("/mnt/tmp/"));
    QCOMPARE(arguments[ArgFileNameFormat]->toString(), QString("some_format"));
    QCOMPARE(appArgs.conflictActions(), FileNameConflictAction::Skip);
    QCOMPARE(arguments[ArgEventId]->toString(), QString("123456"));
    QCOMPARE(arguments[ArgEventStartTime]->toDateTime(), QDateTime(QDate(2011, 1, 2), QTime(3, 4, 5), Qt::UTC));
    QCOMPARE(arguments[ArgEventEndTime]->toDateTime(), QDateTime(QDate(2012, 1, 2), QTime(3, 4, 5), Qt::UTC));
    QCOMPARE(qFuzzyCompare(arguments[ArgEventMinMag]->toDouble(), 1.1), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgEventMaxMag]->toDouble(), 2.2), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgEventMinDepth]->toDouble(), 3.3), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgEventMaxDepth]->toDouble(), 4.4), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgEventMinLat]->toDouble(), 10.1), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgEventMaxLat]->toDouble(), 10.2), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgEventMinLon]->toDouble(), 10.3), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgEventMaxLon]->toDouble(), 10.4), true);
    QCOMPARE(arguments[ArgNetwork]->toString(), QString("AA"));
    QCOMPARE(arguments[ArgStation]->toString(), QString("BBBBB"));
    QCOMPARE(arguments[ArgLocation]->toString(), QString("00"));
    QCOMPARE(arguments[ArgChannel]->toString(), QString("CCC"));
    QCOMPARE(arguments[ArgStartTime]->toDateTime(), QDateTime(QDate(2013, 1, 2), QTime(3, 4, 5), Qt::UTC));
    QCOMPARE(arguments[ArgEndTime]->toDateTime(), QDateTime(QDate(2014, 1, 2), QTime(3, 4, 5), Qt::UTC));
    QCOMPARE(qFuzzyCompare(arguments[ArgStationMinLat]->toDouble(), 20.1), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgStationMaxLat]->toDouble(), 20.2), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgStationMinLon]->toDouble(), 20.3), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgStationMaxLon]->toDouble(), 20.4), true);
    QCOMPARE(arguments[ArgLimit]->toInt(), 30);
    QCOMPARE(arguments[ArgLimitPerEvent]->toInt(), 40);
    QCOMPARE(arguments[ArgSecondsBefore]->toInt(), 100);
    QCOMPARE(arguments[ArgSecondsAfter]->toInt(), 1000);
    QCOMPARE(arguments[ArgFdsnwsDataselectUrl]->toUrl(),  QUrl("http://service.iris.edu/fdsnws/dataselect/1/"));
    QCOMPARE(arguments[ArgFdsnwsStationUrl]->toUrl(),  QUrl("http://service.iris.edu/fdsnws/station/1/"));
    QCOMPARE(arguments[ArgFdsnwsEventUrl]->toUrl(),  QUrl("http://service.iris.edu/fdsnws/event/1/"));
    QCOMPARE(arguments[ArgPrintFdsnwsDataselectServices]->toBool(), true);
    QCOMPARE(arguments[ArgPrintFdsnwsStationServices]->toBool(), true);
    QCOMPARE(arguments[ArgPrintFdsnwsEventServices]->toBool(), true);
    QCOMPARE(arguments[ArgPrintSelectedEvents]->toBool(), true);
    QCOMPARE(arguments[ArgSelectedEventsFormat]->toString(), QString("zzz"));
    QCOMPARE(arguments[ArgPrintSelectedTraces]->toBool(), true);
    QCOMPARE(arguments[ArgSelectedTracesFormat]->toString(), QString("xxx"));
    QCOMPARE(arguments[ArgDebug]->toBool(), true);
    QCOMPARE(arguments[ArgHelp]->toBool(), true);
}


void Test_AppArguments::test_002()
{
    QStringList cmdlineArgs
        = QStringList()
          << "seismicsound-dl"
          << ArgSampleRate             << "1100"
          << ArgSampleFormat           << "f32"
          << ArgOutputDirectory        << "/mnt/tmp/"
          << ArgFileNameFormat         << "some_format"
          << ArgFileNameConflictAction << "skip"
          << ArgEventId                     << "123456"
          << ArgEventStartTime              << "2011-01-02T03:04:05"
          << ArgEventEndTime                << "2012-01-02T03:04:05"
          << ArgEventMinMag                 << "1.1"
          << ArgEventMaxMag                 << "2.2"
          << ArgEventMinDepth               << "3.3"
          << ArgEventMaxDepth               << "4.4"
          << ArgEventLat                    << "10.5"
          << ArgEventLon                    << "10.6"
          << ArgEventMinRadius              << "10.7"
          << ArgEventMaxRadius              << "10.8"
          << ArgNetwork                     << "AA"
          << ArgStation                     << "BBBBB"
          << ArgLocation                    << "00"
          << ArgChannel                     << "CCC"
          << ArgStartTime                   << "2013-01-02T03:04:05"
          << ArgEndTime                     << "2014-01-02T03:04:05"
          << ArgStationLat                  << "20.5"
          << ArgStationLon                  << "20.6"
          << ArgStationMinRadius            << "20.7"
          << ArgStationMaxRadius            << "20.8"
          << ArgLimit                       << "30"
          << ArgLimitPerEvent               << "40"
          << ArgSecondsBefore               << "100"
          << ArgSecondsAfter                << "1000"
          << ArgFdsnwsDataselectUrl         << "0010"
          << ArgFdsnwsStationUrl            << "0010"
          << ArgFdsnwsEventUrl              << "0010"
          << ArgPrintFdsnwsDataselectServices
          << ArgPrintFdsnwsStationServices
          << ArgPrintFdsnwsEventServices
          << ArgPrintSelectedEvents
          << ArgSelectedEventsFormat          << "zzz"
          << ArgPrintSelectedTraces
          << ArgSelectedTracesFormat          << "xxx"
          << ArgDebug
          << ArgHelp;



    AppArguments appArgs(cmdlineArgs);
    QCOMPARE(appArgs.hasError(), false);

    const QHash<QString, AppArgument *> &arguments = appArgs.arguments();
    QCOMPARE(arguments[ArgSampleRate]->toInt(),  1100);
    QCOMPARE(appArgs.sampleFormat(), (SF_FORMAT_WAV | SF_FORMAT_FLOAT));
    QCOMPARE(arguments[ArgOutputDirectory]->toString(), QString("/mnt/tmp/"));
    QCOMPARE(arguments[ArgFileNameFormat]->toString(), QString("some_format"));
    QCOMPARE(appArgs.conflictActions(), FileNameConflictAction::Skip);
    QCOMPARE(arguments[ArgEventId]->toString(), QString("123456"));
    QCOMPARE(arguments[ArgEventStartTime]->toDateTime(), QDateTime(QDate(2011, 1, 2), QTime(3, 4, 5), Qt::UTC));
    QCOMPARE(arguments[ArgEventEndTime]->toDateTime(), QDateTime(QDate(2012, 1, 2), QTime(3, 4, 5), Qt::UTC));
    QCOMPARE(qFuzzyCompare(arguments[ArgEventMinMag]->toDouble(), 1.1), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgEventMaxMag]->toDouble(), 2.2), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgEventMinDepth]->toDouble(), 3.3), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgEventMaxDepth]->toDouble(), 4.4), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgEventLat]->toDouble(), 10.5), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgEventLon]->toDouble(), 10.6), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgEventMinRadius]->toDouble(), 10.7), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgEventMaxRadius]->toDouble(), 10.8), true);
    QCOMPARE(arguments[ArgNetwork]->toString(), QString("AA"));
    QCOMPARE(arguments[ArgStation]->toString(), QString("BBBBB"));
    QCOMPARE(arguments[ArgLocation]->toString(), QString("00"));
    QCOMPARE(arguments[ArgChannel]->toString(), QString("CCC"));
    QCOMPARE(arguments[ArgStartTime]->toDateTime(), QDateTime(QDate(2013, 1, 2), QTime(3, 4, 5), Qt::UTC));
    QCOMPARE(arguments[ArgEndTime]->toDateTime(), QDateTime(QDate(2014, 1, 2), QTime(3, 4, 5), Qt::UTC));
    QCOMPARE(qFuzzyCompare(arguments[ArgStationLat]->toDouble(), 20.5), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgStationLon]->toDouble(), 20.6), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgStationMinRadius]->toDouble(), 20.7), true);
    QCOMPARE(qFuzzyCompare(arguments[ArgStationMaxRadius]->toDouble(), 20.8), true);
    QCOMPARE(arguments[ArgLimit]->toInt(), 30);
    QCOMPARE(arguments[ArgLimitPerEvent]->toInt(), 40);
    QCOMPARE(arguments[ArgSecondsBefore]->toInt(), 100);
    QCOMPARE(arguments[ArgSecondsAfter]->toInt(), 1000);
    QCOMPARE(arguments[ArgFdsnwsDataselectUrl]->toUrl(),  QUrl("http://service.iris.edu/fdsnws/dataselect/1/"));
    QCOMPARE(arguments[ArgFdsnwsStationUrl]->toUrl(),  QUrl("http://service.iris.edu/fdsnws/station/1/"));
    QCOMPARE(arguments[ArgFdsnwsEventUrl]->toUrl(),  QUrl("http://service.iris.edu/fdsnws/event/1/"));
    QCOMPARE(arguments[ArgPrintFdsnwsDataselectServices]->toBool(), true);
    QCOMPARE(arguments[ArgPrintFdsnwsStationServices]->toBool(), true);
    QCOMPARE(arguments[ArgPrintFdsnwsEventServices]->toBool(), true);
    QCOMPARE(arguments[ArgPrintSelectedEvents]->toBool(), true);
    QCOMPARE(arguments[ArgSelectedEventsFormat]->toString(), QString("zzz"));
    QCOMPARE(arguments[ArgPrintSelectedTraces]->toBool(), true);
    QCOMPARE(arguments[ArgSelectedTracesFormat]->toString(), QString("xxx"));
    QCOMPARE(arguments[ArgDebug]->toBool(), true);
    QCOMPARE(arguments[ArgHelp]->toBool(), true);
}

void Test_AppArguments::test_toStationQuery_001()
{
    QStringList cmdlineArgs
        = QStringList()
          << "appname"
          << ArgNetwork                     << "AA"
          << ArgStation                     << "BBBBB"
          << ArgLocation                    << "00"
          << ArgChannel                     << "CCC"
          << ArgStartTime                   << "2013-01-02T03:04:05"
          << ArgEndTime                     << "2014-01-02T03:04:05"
          << ArgStationMinLat               << "20.1"
          << ArgStationMaxLat               << "20.2"
          << ArgStationMinLon               << "20.3"
          << ArgStationMaxLon               << "20.4";

    AppArguments appArgs(cmdlineArgs);
    QCOMPARE(appArgs.hasError(), false);

    StationQuery query = appArgs.stationQuery();
    QCOMPARE(query.searchTerms(), StationQuery::Box);
    QCOMPARE(query.network(), QString("AA"));
    QCOMPARE(query.station(), QString("BBBBB"));
    QCOMPARE(query.channel(), QString("CCC"));
    QCOMPARE(query.location(), QString("00"));
    QCOMPARE(query.startTime(), QDateTime(QDate(2013, 1, 2), QTime(3, 4, 5), Qt::UTC));
    QCOMPARE(query.endTime(), QDateTime(QDate(2014, 1, 2), QTime(3, 4, 5), Qt::UTC));
    QCOMPARE(query.url(), QUrl("http://service.iris.edu/fdsnws/station/1/query"));
    QVERIFY(qFuzzyCompare(query.minimumLatitude(), 20.1));
    QVERIFY(qFuzzyCompare(query.maximumLatitude(), 20.2));
    QVERIFY(qFuzzyCompare(query.minimumLongitude(), 20.3));
    QVERIFY(qFuzzyCompare(query.maximumLongitude(), 20.4));
    QVERIFY(qFuzzyCompare(query.latitude(), InvalidLatitude));
    QVERIFY(qFuzzyCompare(query.longitude(), InvalidLongitude));
    QVERIFY(qFuzzyCompare(query.minimumRadius(), InvalidRadius));
    QVERIFY(qFuzzyCompare(query.maximumRadius(), InvalidRadius));
}

void Test_AppArguments::test_toStationQuery_002()
{
    QStringList cmdlineArgs
        = QStringList()
          << "appname"
          << ArgStationLat                  << "20.5"
          << ArgStationLon                  << "20.6"
          << ArgStationMinRadius            << "20.7"
          << ArgStationMaxRadius            << "20.8"
          << ArgFdsnwsStationUrl            << "http://localhost/query";

    AppArguments appArgs(cmdlineArgs);
    QCOMPARE(appArgs.hasError(), false);

    StationQuery query = appArgs.stationQuery();
    QCOMPARE(query.searchTerms(), StationQuery::Radial);
    QCOMPARE(query.network(), QString());
    QCOMPARE(query.station(), QString());
    QCOMPARE(query.channel(), QString());
    QCOMPARE(query.location(), QString());
    QCOMPARE(query.startTime(), QDateTime());
    QCOMPARE(query.endTime(), QDateTime());
    QCOMPARE(query.url(), QUrl("http://localhost/query"));
    QVERIFY(qFuzzyCompare(query.minimumLatitude(), InvalidLatitude));
    QVERIFY(qFuzzyCompare(query.maximumLatitude(), InvalidLatitude));
    QVERIFY(qFuzzyCompare(query.minimumLongitude(), InvalidLongitude));
    QVERIFY(qFuzzyCompare(query.maximumLongitude(), InvalidLongitude));
    QVERIFY(qFuzzyCompare(query.latitude(), 20.5));
    QVERIFY(qFuzzyCompare(query.longitude(), 20.6));
    QVERIFY(qFuzzyCompare(query.minimumRadius(), 20.7));
    QVERIFY(qFuzzyCompare(query.maximumRadius(), 20.8));
}

void Test_AppArguments::test_toEventQuery_001()
{
    QStringList cmdlineArgs
        = QStringList()
          << "appname"
          << ArgEventId                     << "123456"
          << ArgEventStartTime              << "2011-01-02T03:04:05"
          << ArgEventEndTime                << "2012-01-02T03:04:05"
          << ArgEventMinMag                 << "1.1"
          << ArgEventMaxMag                 << "2.2"
          << ArgEventMinDepth               << "3.3"
          << ArgEventMaxDepth               << "4.4"
          << ArgEventMinLat                 << "10.1"
          << ArgEventMaxLat                 << "10.2"
          << ArgEventMinLon                 << "10.3"
          << ArgEventMaxLon                 << "10.4"
          << ArgLimitPerEvent               << "200";


    AppArguments appArgs(cmdlineArgs);
    QCOMPARE(appArgs.hasError(), false);

    EventQuery query = appArgs.eventQuery();
    QCOMPARE(query.searchTerms(), EventQuery::Box);
    QCOMPARE(query.id(), QString("123456"));
    QCOMPARE(query.startTime(), QDateTime(QDate(2011, 1, 2), QTime(3, 4, 5), Qt::UTC));
    QCOMPARE(query.endTime(), QDateTime(QDate(2012, 1, 2), QTime(3, 4, 5), Qt::UTC));
    QCOMPARE(query.url(), QUrl("http://service.iris.edu/fdsnws/event/1/query"));
    QVERIFY(qFuzzyCompare(query.minimumMagnitude(), 1.1));
    QVERIFY(qFuzzyCompare(query.maximumMagnitude(), 2.2));
    QVERIFY(qFuzzyCompare(query.minimumDepth(), 3.3));
    QVERIFY(qFuzzyCompare(query.maximumDepth(), 4.4));
    QVERIFY(qFuzzyCompare(query.minimumLatitude(), 10.1));
    QVERIFY(qFuzzyCompare(query.maximumLatitude(), 10.2));
    QVERIFY(qFuzzyCompare(query.minimumLongitude(), 10.3));
    QVERIFY(qFuzzyCompare(query.maximumLongitude(), 10.4));
    QVERIFY(qFuzzyCompare(query.latitude(), InvalidLatitude));
    QVERIFY(qFuzzyCompare(query.longitude(), InvalidLongitude));
    QVERIFY(qFuzzyCompare(query.minimumRadius(), InvalidRadius));
    QVERIFY(qFuzzyCompare(query.maximumRadius(), InvalidRadius));
    QCOMPARE(query.limit(), InvalidLimit);
    QCOMPARE(query.offset(), InvalidOffset);
}

void Test_AppArguments::test_toEventQuery_002()
{
    QStringList cmdlineArgs
        = QStringList()
          << "appname"
          << ArgEventLat                    << "10.5"
          << ArgEventLon                    << "10.6"
          << ArgEventMinRadius              << "10.7"
          << ArgEventMaxRadius              << "10.8"
          << ArgFdsnwsEventUrl              << "http://localhost/query";


    AppArguments appArgs(cmdlineArgs);
    QCOMPARE(appArgs.hasError(), false);

    EventQuery query = appArgs.eventQuery();
    QCOMPARE(query.searchTerms(), EventQuery::Radial);
    QCOMPARE(query.id(), QString());
    QCOMPARE(query.startTime(), QDateTime());
    QCOMPARE(query.endTime(), QDateTime());
    QCOMPARE(query.url(), QUrl("http://localhost/query"));
    QVERIFY(qFuzzyCompare(query.minimumMagnitude(), InvalidMagnitude));
    QVERIFY(qFuzzyCompare(query.maximumMagnitude(), InvalidMagnitude));
    QVERIFY(qFuzzyCompare(query.minimumDepth(), InvalidDepth));
    QVERIFY(qFuzzyCompare(query.maximumDepth(), InvalidDepth));
    QVERIFY(qFuzzyCompare(query.minimumLatitude(), InvalidLatitude));
    QVERIFY(qFuzzyCompare(query.maximumLatitude(), InvalidLatitude));
    QVERIFY(qFuzzyCompare(query.minimumLongitude(), InvalidLongitude));
    QVERIFY(qFuzzyCompare(query.maximumLongitude(), InvalidLongitude));
    QVERIFY(qFuzzyCompare(query.latitude(), 10.5));
    QVERIFY(qFuzzyCompare(query.longitude(), 10.6));
    QVERIFY(qFuzzyCompare(query.minimumRadius(), 10.7));
    QVERIFY(qFuzzyCompare(query.maximumRadius(), 10.8));
    QCOMPARE(query.limit(), InvalidLimit);
    QCOMPARE(query.offset(), InvalidOffset);
}
