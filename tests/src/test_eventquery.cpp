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
#include "test_eventquery.h"
#include "eventquery.h"
#include "consts.h"


Test_EventQuery::Test_EventQuery(QObject *parent)
    : QObject(parent)
{
}

void Test_EventQuery::test_defaultConstructor()
{
    EventQuery query;
    QCOMPARE(query.searchTerms(), EventQuery::All);
    QCOMPARE(query.id(), QString());
    QCOMPARE(query.startTime(), QDateTime());
    QCOMPARE(query.endTime(), QDateTime());
    QVERIFY(qFuzzyCompare(query.minimumMagnitude(), InvalidMagnitude));
    QVERIFY(qFuzzyCompare(query.maximumMagnitude(), InvalidMagnitude));
    QVERIFY(qFuzzyCompare(query.minimumDepth(), InvalidDepth));
    QVERIFY(qFuzzyCompare(query.maximumDepth(), InvalidDepth));
    QVERIFY(qFuzzyCompare(query.minimumLatitude(), InvalidLatitude));
    QVERIFY(qFuzzyCompare(query.maximumLatitude(), InvalidLatitude));
    QVERIFY(qFuzzyCompare(query.minimumLongitude(), InvalidLongitude));
    QVERIFY(qFuzzyCompare(query.maximumLongitude(), InvalidLongitude));
    QVERIFY(qFuzzyCompare(query.latitude(), InvalidLatitude));
    QVERIFY(qFuzzyCompare(query.longitude(), InvalidLongitude));
    QVERIFY(qFuzzyCompare(query.minimumRadius(), InvalidRadius));
    QVERIFY(qFuzzyCompare(query.maximumRadius(), InvalidRadius));
    QCOMPARE(query.url(), (QUrl()));
    QCOMPARE(query.limit(), InvalidLimit);
    QCOMPARE(query.offset(), InvalidOffset);
}

void Test_EventQuery::test_setGet()
{
    EventQuery query;

    query.setSearchTerms(EventQuery::Box);
    query.setId("123456");
    query.setMinimumMagnitude(0.1);
    query.setMaximumMagnitude(0.2);
    query.setMinimumDepth(0.3);
    query.setMaximumDepth(0.4);
    query.setStartTime(QDateTime(QDate(2001, 2, 3), QTime(4, 5, 6), Qt::UTC));
    query.setEndTime(QDateTime(QDate(2007, 8, 9), QTime(10, 11, 12), Qt::UTC));
    query.setMinimumLatitude(1.0);
    query.setMaximumLatitude(2.0);
    query.setMinimumLongitude(3.0);
    query.setMaximumLongitude(4.0);
    query.setLatitude(5.0);
    query.setLongitude(6.0);
    query.setMinimumRadius(7.0);
    query.setMaximumRadius(8.0);
    query.setUrl(QUrl("http://localhost.xyz/"));
    query.setLimit(400);
    query.setOffset(404);

    QCOMPARE(query.searchTerms(), EventQuery::Box);
    QCOMPARE(query.id(), QString("123456"));
    QCOMPARE(query.startTime(), (QDateTime(QDate(2001, 2, 3), QTime(4, 5, 6), Qt::UTC)));
    QCOMPARE(query.endTime(), (QDateTime(QDate(2007, 8, 9), QTime(10, 11, 12), Qt::UTC)));
    QVERIFY(qFuzzyCompare(query.minimumMagnitude(), 0.1));
    QVERIFY(qFuzzyCompare(query.maximumMagnitude(), 0.2));
    QVERIFY(qFuzzyCompare(query.minimumDepth(), 0.3));
    QVERIFY(qFuzzyCompare(query.maximumDepth(), 0.4));
    QVERIFY(qFuzzyCompare(query.minimumLatitude(), 1.0));
    QVERIFY(qFuzzyCompare(query.maximumLatitude(), 2.0));
    QVERIFY(qFuzzyCompare(query.minimumLongitude(), 3.0));
    QVERIFY(qFuzzyCompare(query.maximumLongitude(), 4.0));
    QVERIFY(qFuzzyCompare(query.latitude(), 5.0));
    QVERIFY(qFuzzyCompare(query.longitude(), 6.0));
    QVERIFY(qFuzzyCompare(query.minimumRadius(), 7.0));
    QVERIFY(qFuzzyCompare(query.maximumRadius(), 8.0));
    QCOMPARE(query.url(), (QUrl("http://localhost.xyz/query")));
    QCOMPARE(query.limit(), 400);
    QCOMPARE(query.offset(), 404);
}

void Test_EventQuery::test_buildQueryUrl()
{
    EventQuery query;
    query.setUrl(QUrl("http://localhost.xyz/"));
    QCOMPARE(query.buildQueryUrl(),
             QUrl("http://localhost.xyz/query?"
                  "format=xml"));

    query.setStartTime(QDateTime(QDate(2000, 1, 2), QTime(3, 4, 5), Qt::UTC));
    query.setEndTime(QDateTime(QDate(2006, 7, 8), QTime(9, 10, 11), Qt::UTC));
    query.setMinimumMagnitude(0.1);
    query.setMaximumMagnitude(0.2);
    query.setMinimumDepth(0.3);
    query.setMaximumDepth(0.4);
    query.setUrl(QUrl("http://localhost.xyz/"));
    query.setLimit(400);
    query.setOffset(404);
    QCOMPARE(query.buildQueryUrl(),
             QUrl("http://localhost.xyz/query?"
                  "format=xml&"
                  "starttime=2000-01-02T03:04:05&"
                  "endtime=2006-07-08T09:10:11&"
                  "minmagnitude=0.100000&"
                  "maxmagnitude=0.200000&"
                  "mindepth=0.300000&"
                  "maxdepth=0.400000&"
                  "limit=400&"
                  "offset=404"));

    query.setSearchTerms(EventQuery::Box);
    query.setMinimumLatitude(10.0);
    query.setMaximumLatitude(20.0);
    query.setMinimumLongitude(30.0);
    query.setMaximumLongitude(40.0);
    QCOMPARE(query.buildQueryUrl(),
             QUrl("http://localhost.xyz/query?"
                  "format=xml&"
                  "starttime=2000-01-02T03:04:05&"
                  "endtime=2006-07-08T09:10:11&"
                  "minmagnitude=0.100000&"
                  "maxmagnitude=0.200000&"
                  "mindepth=0.300000&"
                  "maxdepth=0.400000&"
                  "minlatitude=10.000000&"
                  "maxlatitude=20.000000&"
                  "minlongitude=30.000000&"
                  "maxlongitude=40.000000&"
                  "limit=400&"
                  "offset=404"));

    query.setSearchTerms(EventQuery::Radial);
    query.setLatitude(50.0);
    query.setLongitude(60.0);
    query.setMinimumRadius(70.0);
    query.setMaximumRadius(80.0);
    QCOMPARE(query.buildQueryUrl(),
             QUrl("http://localhost.xyz/query?"
                  "format=xml&"
                  "starttime=2000-01-02T03:04:05&"
                  "endtime=2006-07-08T09:10:11&"
                  "minmagnitude=0.100000&"
                  "maxmagnitude=0.200000&"
                  "mindepth=0.300000&"
                  "maxdepth=0.400000&"
                  "latitude=50.000000&"
                  "longitude=60.000000&"
                  "minradius=70.000000&"
                  "maxradius=80.000000&"
                  "limit=400&"
                  "offset=404"));

    query.setId("123456");
    QCOMPARE(query.buildQueryUrl(),
             QUrl("http://localhost.xyz/query?"
                  "format=xml&"
                  "eventid=123456"));
}

void Test_EventQuery::test_setUrl()
{
    EventQuery query;
    query.setUrl(QUrl("http://localhost.xyz/"));
    QCOMPARE(query.url(), QUrl("http://localhost.xyz/query"));
    query.setUrl(QUrl("http://localhost.xyz"));
    QCOMPARE(query.url(), QUrl("http://localhost.xyz/query"));
    query.setUrl(QUrl("http://localhost.xyz/query"));
    QCOMPARE(query.url(), QUrl("http://localhost.xyz/query"));
    query.setUrl(QUrl("http://localhost.xyz//"));
    QVERIFY(query.url() == QUrl("http://localhost.xyz//query")
            || query.url() == QUrl("http://localhost.xyz/query"));
}
