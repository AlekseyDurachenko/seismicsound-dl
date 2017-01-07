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
#include "test_fdsnwslist.h"
#include "fdsnwslist.h"


Test_FdsnwsList::Test_FdsnwsList(QObject *parent)
    : QObject(parent)
{
}

void Test_FdsnwsList::test_contains()
{
    QCOMPARE(fdsnws_dataselect_contains("0010"), true);
    QCOMPARE(fdsnws_dataselect_contains("0000"), false);
    QCOMPARE(fdsnws_dataselect_contains("9999"), false);

    QCOMPARE(fdsnws_station_contains("0010"), true);
    QCOMPARE(fdsnws_station_contains("0000"), false);
    QCOMPARE(fdsnws_station_contains("9999"), false);

    QCOMPARE(fdsnws_event_contains("0010"), true);
    QCOMPARE(fdsnws_event_contains("0000"), false);
    QCOMPARE(fdsnws_event_contains("9999"), false);
}

void Test_FdsnwsList::test_url()
{
    QCOMPARE(fdsnws_dataselect_url("0010"), QUrl("http://service.iris.edu/fdsnws/dataselect/1/"));
    QCOMPARE(fdsnws_dataselect_url("0000"), QUrl());

    QCOMPARE(fdsnws_station_url("0010"), QUrl("http://service.iris.edu/fdsnws/station/1/"));
    QCOMPARE(fdsnws_station_url("0000"), QUrl());

    QCOMPARE(fdsnws_event_url("0010"), QUrl("http://service.iris.edu/fdsnws/event/1/"));
    QCOMPARE(fdsnws_event_url("0000"), QUrl());
}

void Test_FdsnwsList::test_desc()
{
    QCOMPARE(fdsnws_dataselect_desc("0010"), QString("IRIS Data Management Center"));
    QCOMPARE(fdsnws_dataselect_desc("0000"), QString());

    QCOMPARE(fdsnws_station_desc("0010"), QString("IRIS Data Management Center"));
    QCOMPARE(fdsnws_station_desc("0000"), QString());

    QCOMPARE(fdsnws_event_desc("0010"), QString("IRIS Data Management Center"));
    QCOMPARE(fdsnws_event_desc("0000"), QString());
}

void Test_FdsnwsList::test_default_code()
{
    QCOMPARE(fdsnws_dataselect_default_code(), QString("0010"));
    QCOMPARE(fdsnws_station_default_code(), QString("0010"));
    QCOMPARE(fdsnws_event_default_code(), QString("0010"));
}
