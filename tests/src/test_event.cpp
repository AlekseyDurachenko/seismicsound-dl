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
#include "test_event.h"
#include "event.h"


Test_Event::Test_Event(QObject *parent)
    : QObject(parent)
{
}

void Test_Event::test_defaultConstructor()
{
    Event event;
    QCOMPARE(event.id(), QString());
    QCOMPARE(event.isNull(), true);
    QCOMPARE(event.time(), (QDateTime()));
    QVERIFY(event.latitude() < 0.001);
    QVERIFY(event.longitude() < 0.001);
    QVERIFY(event.depth() < 0.001);
    QCOMPARE(event.magnitudeType(), (QString()));
    QVERIFY(event.magnitudeValue() < 0.001);
    QCOMPARE(event.description(), (QString()));
}

void Test_Event::test_constructor()
{
    Event event(QString("123456"),
                QDateTime(QDate(2000, 1, 1), QTime(20, 20, 10), Qt::UTC),
                10.0,
                11.0,
                12.0,
                QString("Mw"),
                13.0,
                QString("Text"));
    QCOMPARE(event.id(), QString("123456"));
    QCOMPARE(event.isNull(), false);
    QCOMPARE(event.time(), (QDateTime(QDate(2000, 1, 1), QTime(20, 20, 10), Qt::UTC)));
    QVERIFY(qFuzzyCompare(event.latitude(), 10.0));
    QVERIFY(qFuzzyCompare(event.longitude(), 11.0));
    QVERIFY(qFuzzyCompare(event.depth(), 12.0));
    QCOMPARE(event.magnitudeType(), (QString("Mw")));
    QVERIFY(qFuzzyCompare(event.magnitudeValue(), 13.0));
    QCOMPARE(event.description(), (QString("Text")));
}

void Test_Event::test_setGet()
{
    Event event;
    event.setId(QString("123456"));
    event.setTime(QDateTime(QDate(2000, 1, 1), QTime(20, 20, 10), Qt::UTC));
    event.setLatitude(10.0);
    event.setLongitude(11.0);
    event.setDepth(12.0);
    event.setMagnitudeType(QString("Mw"));
    event.setMagnitudeValue(13.0);
    event.setDescription(QString("Text"));
    QCOMPARE(event.id(), QString("123456"));
    QCOMPARE(event.isNull(), false);
    QCOMPARE(event.time(), (QDateTime(QDate(2000, 1, 1), QTime(20, 20, 10), Qt::UTC)));
    QVERIFY(qFuzzyCompare(event.latitude(), 10.0));
    QVERIFY(qFuzzyCompare(event.longitude(), 11.0));
    QVERIFY(qFuzzyCompare(event.depth(), 12.0));
    QCOMPARE(event.magnitudeType(), (QString("Mw")));
    QVERIFY(qFuzzyCompare(event.magnitudeValue(), 13.0));
    QCOMPARE(event.description(), (QString("Text")));
}

void Test_Event::test_isNull()
{
    Event event;
    event.setTime(QDateTime(QDate(2000, 1, 1), QTime(20, 20, 10), Qt::UTC));
    QCOMPARE(event.isNull(), false);
}
