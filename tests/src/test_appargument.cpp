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
#include "test_appargument.h"
#include "appargument.h"
#include <sndfile.h>
#include <numeric>


Test_AppArgument::Test_AppArgument(QObject *parent)
    : QObject(parent)
{
}

void Test_AppArgument::test_defaultConstructor()
{
    AppArgument argument;
    QCOMPARE(argument.isFound(), false);
    QCOMPARE(argument.type(), AppArgument::Bool);
    QCOMPARE(argument.key(), QString());
    QCOMPARE(argument.value(), QVariant());
    QCOMPARE(argument.minimumInteger(), std::numeric_limits<qint64>::min());
    QCOMPARE(argument.maximumInteger(), std::numeric_limits<qint64>::max());
    QCOMPARE(argument.minimumDouble(), std::numeric_limits<double>::min());
    QCOMPARE(argument.maximumDouble(), std::numeric_limits<double>::max());
    QCOMPARE(argument.stringRegExp(), QRegExp());
    QCOMPARE(argument.dateTimeFormat(), QString());
    QCOMPARE(argument.minimumDateTime(), QDateTime());
    QCOMPARE(argument.maximumDateTime(), QDateTime());
}


void Test_AppArgument::test_setGet()
{
    AppArgument argument;
    argument.setFound(true);
    argument.setType(AppArgument::String);
    argument.setKey(QString("key"));
    argument.setValue(QVariant("value"));
    argument.setIntegerRange(-10, 10);
    argument.setDoubleRange(-100.0, 100.0);
    argument.setStringRegExp(QRegExp("abcde"));
    argument.setDateTimeFormat(QString("HH:mm:ss"));
    argument.setDateTimeRange(QDateTime(QDate(2000, 1, 1), QTime(1, 1, 1)),
                              QDateTime(QDate(2001, 1, 1), QTime(1, 1, 1)));
    QCOMPARE(argument.isFound(), true);
    QCOMPARE(argument.type(), AppArgument::String);
    QCOMPARE(argument.key(), QString("key"));
    QCOMPARE(argument.value(), QVariant("value"));
    QCOMPARE(argument.minimumInteger(), Q_INT64_C(-10));
    QCOMPARE(argument.maximumInteger(), Q_INT64_C(10));
    QVERIFY(qFuzzyCompare(argument.minimumDouble(), -100.0));
    QVERIFY(qFuzzyCompare(argument.maximumDouble(), 100.0));
    QCOMPARE(argument.stringRegExp(), QRegExp("abcde"));
    QCOMPARE(argument.dateTimeFormat(), QString("HH:mm:ss"));
    QCOMPARE(argument.minimumDateTime(), QDateTime(QDate(2000, 1, 1), QTime(1, 1, 1)));
    QCOMPARE(argument.maximumDateTime(), QDateTime(QDate(2001, 1, 1), QTime(1, 1, 1)));
}

void Test_AppArgument::test_validate_bool()
{
    AppArgument argument;
    argument.setType(AppArgument::Bool);

    argument.setFound(false);
    QCOMPARE(argument.validate(), true);
    argument.setFound(true);
    QCOMPARE(argument.validate(), true);
}

void Test_AppArgument::test_validate_integer()
{
    AppArgument argument;
    argument.setFound(true);
    argument.setType(AppArgument::Integer);
    argument.setIntegerRange(100, 200);

    argument.setValue(99);
    QCOMPARE(argument.validate(), false);
    argument.setValue(100);
    QCOMPARE(argument.validate(), true);
    argument.setValue(200);
    QCOMPARE(argument.validate(), true);
    argument.setValue(201);
    QCOMPARE(argument.validate(), false);
    argument.setFound(false);
    QCOMPARE(argument.validate(), true);
}

void Test_AppArgument::test_validate_double()
{
    AppArgument argument;
    argument.setFound(true);
    argument.setType(AppArgument::Integer);
    argument.setIntegerRange(300.0, 400.0);

    argument.setValue(299.0);
    QCOMPARE(argument.validate(), false);
    argument.setValue(300.0);
    QCOMPARE(argument.validate(), true);
    argument.setValue(400.0);
    QCOMPARE(argument.validate(), true);
    argument.setValue(501.0);
    QCOMPARE(argument.validate(), false);
    argument.setFound(false);
    QCOMPARE(argument.validate(), true);
}

void Test_AppArgument::test_validate_string()
{
    AppArgument argument;
    argument.setFound(true);
    argument.setType(AppArgument::String);

    argument.setValue(QString("abcdef"));
    QCOMPARE(argument.validate(), true);

    argument.setStringRegExp(QRegExp("(i1)|(i2)|(i3)"));
    argument.setValue(QString("i1"));
    QCOMPARE(argument.validate(), true);
    argument.setValue(QString("i4"));
    QCOMPARE(argument.validate(), false);
    argument.setFound(false);
    QCOMPARE(argument.validate(), true);
}

void Test_AppArgument::test_validate_dateTime()
{
    AppArgument argument;
    argument.setFound(true);
    argument.setType(AppArgument::DateTime);
    argument.setDateTimeRange(QDateTime(QDate(2010, 1, 1), QTime(1, 1, 1), Qt::UTC),
                              QDateTime(QDate(2020, 1, 1), QTime(1, 1, 1), Qt::UTC));

    argument.setDateTimeFormat("yyyy-MM-ddTHH:mm:ss");
    argument.setValue(QString("2011-01-01 10:10:10"));
    QCOMPARE(argument.validate(), false);
    argument.setDateTimeFormat("yyyy-MM-dd HH:mm:ss");
    QCOMPARE(argument.validate(), true);
    argument.setValue(QString("2010-01-01 01:01:01"));
    QCOMPARE(argument.validate(), true);
    argument.setValue(QString("2010-01-01 01:01:00"));
    QCOMPARE(argument.validate(), false);
    argument.setValue(QString("2020-01-01 01:01:02"));
    QCOMPARE(argument.validate(), false);
    argument.setFound(false);
    QCOMPARE(argument.validate(), true);
}

void Test_AppArgument::test_validate_url()
{
    AppArgument argument;
    argument.setFound(true);
    argument.setType(AppArgument::Url);

    argument.setValue(QUrl::fromUserInput("https://localhost/"));
    QCOMPARE(argument.validate(), true);

    argument.setValue(QUrl::fromUserInput("ht$tpslocal"));
    QCOMPARE(argument.validate(), false);
    argument.setFound(false);
    QCOMPARE(argument.validate(), true);
}

void Test_AppArgument::test_argument_to_types()
{
    AppArgument argument;

    argument.setFound(false);
    argument.setType(AppArgument::Bool);
    QCOMPARE(argument.toBool(), false);
    argument.setFound(true);
    QCOMPARE(argument.toBool(), true);

    argument.setType(AppArgument::Integer);
    argument.setValue(10);
    QCOMPARE(argument.toInt(), 10);

    argument.setType(AppArgument::Double);
    argument.setValue(66.6);
    QCOMPARE(qFuzzyCompare(argument.toDouble(), 66.6), true);

    argument.setType(AppArgument::String);
    argument.setValue(QString("string"));
    QCOMPARE(argument.toString(), QString("string"));

    argument.setType(AppArgument::DateTime);
    argument.setDateTimeFormat("yyyy-MM-dd HH:mm:ss");
    argument.setValue(QString("2010-01-01 20:20:20"));
    QCOMPARE(argument.toDateTime(), QDateTime(QDate(2010, 1, 1), QTime(20, 20, 20), Qt::UTC));

    argument.setType(AppArgument::Url);
    argument.setValue(QUrl("http://localhost/"));
    QCOMPARE(argument.toUrl(), QUrl("http://localhost/"));
}
