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
#include "test_trace.h"
#include "trace.h"


Test_Trace::Test_Trace(QObject *parent)
    : QObject(parent)
{
}

void Test_Trace::test_defaultConstructor()
{
    Trace trace;
    QCOMPARE(trace.isNull(), true);
    QCOMPARE(trace.network(), QString());
    QCOMPARE(trace.station(), QString());
    QCOMPARE(trace.location(), QString());
    QCOMPARE(trace.channel(), QString());
    QVERIFY(trace.latitude() < 0.001);
    QVERIFY(trace.longitude() < 0.001);
    QCOMPARE(trace.startTime(), QDateTime());
    QCOMPARE(trace.endTime(), QDateTime());
    QVERIFY(trace.elevation() < 0.001);
    QVERIFY(trace.depth() < 0.001);
    QCOMPARE(trace.siteName(), QString());
}

void Test_Trace::test_setGet()
{
    Trace trace;
    trace.setNetwork(QString("N"));
    trace.setStation(QString("S"));
    trace.setLocation(QString("L"));
    trace.setChannel(QString("C"));
    trace.setLatitude(10.0);
    trace.setLongitude(11.0);
    trace.setStartTime(QDateTime(QDate(2000, 1, 1), QTime(20, 20, 10), Qt::UTC));
    trace.setEndTime(QDateTime(QDate(2002, 1, 1), QTime(20, 20, 10), Qt::UTC));
    trace.setElevation(12.0);
    trace.setDepth(13.0);
    trace.setSiteName(QString("Site"));
    QCOMPARE(trace.isNull(), false);
    QCOMPARE(trace.network(), QString("N"));
    QCOMPARE(trace.station(), QString("S"));
    QCOMPARE(trace.location(), QString("L"));
    QCOMPARE(trace.channel(), QString("C"));
    QVERIFY(qFuzzyCompare(trace.latitude(), 10.0));
    QVERIFY(qFuzzyCompare(trace.longitude(), 11.0));
    QCOMPARE(trace.startTime(), (QDateTime(QDate(2000, 1, 1), QTime(20, 20, 10), Qt::UTC)));
    QCOMPARE(trace.endTime(), (QDateTime(QDate(2002, 1, 1), QTime(20, 20, 10), Qt::UTC)));
    QVERIFY(qFuzzyCompare(trace.elevation(), 12.0));
    QVERIFY(qFuzzyCompare(trace.depth(), 13.0));
    QCOMPARE(trace.siteName(), QString("Site"));
}

void Test_Trace::test_isNull()
{
    Trace trace;
    trace.setNetwork(QString("N"));
    QCOMPARE(trace.isNull(), true);

    trace.setStation(QString("S"));
    QCOMPARE(trace.isNull(), true);

    trace.setLocation(QString("L"));
    QCOMPARE(trace.isNull(), true);

    trace.setChannel(QString("C"));
    QCOMPARE(trace.isNull(), false);
}
