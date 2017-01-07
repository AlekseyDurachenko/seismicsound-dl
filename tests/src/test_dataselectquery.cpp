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
#include "test_dataselectquery.h"
#include "dataselectquery.h"


Test_DataSelectQuery::Test_DataSelectQuery(QObject *parent)
    : QObject(parent)
{
}

void Test_DataSelectQuery::test_defaultConstructor()
{
    DataSelectQuery query;
    QCOMPARE(query.network(), (QString()));
    QCOMPARE(query.station(), (QString()));
    QCOMPARE(query.location(), (QString()));
    QCOMPARE(query.channel(), (QString()));
    QCOMPARE(query.startTime(), (QDateTime()));
    QCOMPARE(query.endTime(), (QDateTime()));
    QCOMPARE(query.url(), (QUrl()));
}

void Test_DataSelectQuery::test_setGet()
{
    DataSelectQuery query;
    query.setNetwork(QString("Ne"));
    query.setStation(QString("Stati"));
    query.setLocation(QString("Lo"));
    query.setChannel(QString("Cha"));
    query.setStartTime(QDateTime(QDate(2001, 2, 3), QTime(4, 5, 6), Qt::UTC));
    query.setEndTime(QDateTime(QDate(2007, 8, 9), QTime(10, 11, 12), Qt::UTC));
    query.setUrl(QUrl("http://localhost.xyz/"));
    QCOMPARE(query.network(), QString("Ne"));
    QCOMPARE(query.station(), QString("Stati"));
    QCOMPARE(query.location(), QString("Lo"));
    QCOMPARE(query.channel(), QString("Cha"));
    QCOMPARE(query.startTime(), QDateTime(QDate(2001, 2, 3), QTime(4, 5, 6), Qt::UTC));
    QCOMPARE(query.endTime(), QDateTime(QDate(2007, 8, 9), QTime(10, 11, 12), Qt::UTC));
    QCOMPARE(query.url(), QUrl("http://localhost.xyz/query"));
}

void Test_DataSelectQuery::test_buildQueryUrl()
{
    DataSelectQuery query;
    query.setUrl(QUrl("http://localhost.xyz/"));
    query.setNetwork(QString("NE"));
    query.setStation(QString("STATI"));
    query.setLocation(QString("LO"));
    query.setChannel(QString("CHA"));
    query.setStartTime(QDateTime(QDate(2000, 1, 2), QTime(3, 4, 5), Qt::UTC));
    query.setEndTime(QDateTime(QDate(2006, 7, 8), QTime(9, 10, 11), Qt::UTC));

    QCOMPARE(query.buildQueryUrl(),
             QUrl("http://localhost.xyz/query?"
                  "net=NE&"
                  "sta=STATI&"
                  "loc=LO&"
                  "cha=CHA&"
                  "starttime=2000-01-02T03:04:05&"
                  "endtime=2006-07-08T09:10:11"));
}

void Test_DataSelectQuery::test_setUrl()
{
    DataSelectQuery query;
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
