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
#include <QCoreApplication>
#include "test_soundtags.h"
#include "test_appargument.h"
#include "test_dataselectquery.h"
#include "test_stationquery.h"
#include "test_eventquery.h"
#include "test_trace.h"
#include "test_event.h"
#include "test_fdsnwslist.h"
#include "test_appargument.h"
#include "test_apparguments.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    int retval = QTest::qExec(new Test_SoundTags, argc, argv);
    if (retval) {
        return retval;
    }

    retval = QTest::qExec(new Test_DataSelectQuery, argc, argv);
    if (retval) {
        return retval;
    }

    retval = QTest::qExec(new Test_StationQuery, argc, argv);
    if (retval) {
        return retval;
    }

    retval = QTest::qExec(new Test_EventQuery, argc, argv);
    if (retval) {
        return retval;
    }

    retval = QTest::qExec(new Test_Trace, argc, argv);
    if (retval) {
        return retval;
    }

    retval = QTest::qExec(new Test_Event, argc, argv);
    if (retval) {
        return retval;
    }

    retval = QTest::qExec(new Test_FdsnwsList, argc, argv);
    if (retval) {
        return retval;
    }

    retval = QTest::qExec(new Test_AppArgument, argc, argv);
    if (retval) {
        return retval;
    }

    retval = QTest::qExec(new Test_AppArguments, argc, argv);
    if (retval) {
        return retval;
    }

    return 0;
}
