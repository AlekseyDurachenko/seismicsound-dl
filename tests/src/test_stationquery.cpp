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
#include "test_stationquery.h"
#include "stationquery.h"
#include "consts.h"


Test_StationQuery::Test_StationQuery(QObject *parent)
    : QObject(parent)
{
}

void Test_StationQuery::test_defaultConstructor()
{
    StationQuery query;
    QCOMPARE(query.searchTerms(), StationQuery::All);
    QCOMPARE(query.network(), QString());
    QCOMPARE(query.station(), QString());
    QCOMPARE(query.channel(), QString());
    QCOMPARE(query.location(), QString());
    QCOMPARE(query.startTime(), QDateTime());
    QCOMPARE(query.endTime(), QDateTime());
    QVERIFY(qFuzzyCompare(query.minimumLatitude(), InvalidLatitude));
    QVERIFY(qFuzzyCompare(query.maximumLatitude(), InvalidLatitude));
    QVERIFY(qFuzzyCompare(query.minimumLongitude(), InvalidLongitude));
    QVERIFY(qFuzzyCompare(query.maximumLongitude(), InvalidLongitude));
    QVERIFY(qFuzzyCompare(query.latitude(), InvalidLatitude));
    QVERIFY(qFuzzyCompare(query.longitude(), InvalidLongitude));
    QVERIFY(qFuzzyCompare(query.minimumRadius(), InvalidRadius));
    QVERIFY(qFuzzyCompare(query.maximumRadius(), InvalidRadius));
    QCOMPARE(query.url(), (QUrl()));
}

void Test_StationQuery::test_setGet()
{
    StationQuery query;

    query.setSearchTerms(StationQuery::Box);
    query.setNetwork(QString("1"));
    query.setStation(QString("2"));
    query.setChannel(QString("3"));
    query.setLocation(QString("4"));
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
    query.setUrl(QUrl("http://localhost.xyz/query"));

    QCOMPARE(query.searchTerms(), StationQuery::Box);
    QCOMPARE(query.network(), QString("1"));
    QCOMPARE(query.station(), QString("2"));
    QCOMPARE(query.channel(), QString("3"));
    QCOMPARE(query.location(), QString("4"));
    QCOMPARE(query.startTime(), QDateTime(QDate(2001, 2, 3), QTime(4, 5, 6), Qt::UTC));
    QCOMPARE(query.endTime(), QDateTime(QDate(2007, 8, 9), QTime(10, 11, 12), Qt::UTC));
    QVERIFY(qFuzzyCompare(query.minimumLatitude(), 1.0));
    QVERIFY(qFuzzyCompare(query.maximumLatitude(), 2.0));
    QVERIFY(qFuzzyCompare(query.minimumLongitude(), 3.0));
    QVERIFY(qFuzzyCompare(query.maximumLongitude(), 4.0));
    QVERIFY(qFuzzyCompare(query.latitude(), 5.0));
    QVERIFY(qFuzzyCompare(query.longitude(), 6.0));
    QVERIFY(qFuzzyCompare(query.minimumRadius(), 7.0));
    QVERIFY(qFuzzyCompare(query.maximumRadius(), 8.0));
    QCOMPARE(query.url(), (QUrl("http://localhost.xyz/query")));
}

void Test_StationQuery::test_buildQueryUrl()
{
    StationQuery query;
    query.setUrl(QUrl("http://localhost.xyz/query"));
    QCOMPARE(query.buildQueryUrl(),
             QUrl("http://localhost.xyz/query?"
                  "level=channel&"
                  "includecomments=false&"
                  "format=xml"));

    query.setNetwork("NE");
    query.setStation("STA");
    query.setChannel("CHE");
    query.setLocation("LO");
    query.setStartTime(QDateTime(QDate(2000, 1, 2), QTime(3, 4, 5), Qt::UTC));
    query.setEndTime(QDateTime(QDate(2006, 7, 8), QTime(9, 10, 11), Qt::UTC));
    QCOMPARE(query.buildQueryUrl(),
             QUrl("http://localhost.xyz/query?"
                  "level=channel&"
                  "includecomments=false&"
                  "format=xml&"
                  "network=NE&"
                  "station=STA&"
                  "channel=CHE&"
                  "location=LO&"
                  "starttime=2000-01-02T03:04:05&"
                  "endtime=2006-07-08T09:10:11"));

    query.setSearchTerms(StationQuery::Box);
    query.setMinimumLatitude(10.0);
    query.setMaximumLatitude(20.0);
    query.setMinimumLongitude(30.0);
    query.setMaximumLongitude(40.0);
    QCOMPARE(query.buildQueryUrl(),
             QUrl("http://localhost.xyz/query?"
                  "level=channel&"
                  "includecomments=false&"
                  "format=xml&"
                  "network=NE&"
                  "station=STA&"
                  "channel=CHE&"
                  "location=LO&"
                  "starttime=2000-01-02T03:04:05&"
                  "endtime=2006-07-08T09:10:11&"
                  "minlatitude=10.000000&"
                  "maxlatitude=20.000000&"
                  "minlongitude=30.000000&"
                  "maxlongitude=40.000000"));

    query.setSearchTerms(StationQuery::Radial);
    query.setLatitude(50.0);
    query.setLongitude(60.0);
    query.setMinimumRadius(70.0);
    query.setMaximumRadius(80.0);
    QCOMPARE(query.buildQueryUrl(),
             QUrl("http://localhost.xyz/query?"
                  "level=channel&"
                  "includecomments=false&"
                  "format=xml&"
                  "network=NE&"
                  "station=STA&"
                  "channel=CHE&"
                  "location=LO&"
                  "starttime=2000-01-02T03:04:05&"
                  "endtime=2006-07-08T09:10:11&"
                  "latitude=50.000000&"
                  "longitude=60.000000&"
                  "minradius=70.000000&"
                  "maxradius=80.000000"));
}

void Test_StationQuery::test_setUrl()
{
    StationQuery query;
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
