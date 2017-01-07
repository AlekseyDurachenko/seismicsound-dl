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
//#include "mainwindow.h"
#include "resources.h"
#include "apparguments.h"
#include "info.h"
#include "usage.h"
#include "fdsnwslist.h"
#include "eventlistdownload.h"
#include "eventlistprint.h"
#include "stationlistdownload.h"
#include "stationlistprint.h"
#include "downloaddatabyevent.h"
#include "downloaddatabytime.h"
#include <iostream>
#include <QLocale>
#include <QTranslator>
#include <QCoreApplication>
#include <QLibraryInfo>


static void install_app_translators(QCoreApplication *app)
{
    Q_ASSERT(app);

    // Qt translator
    static QTranslator qtTr;
    qtTr.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app->installTranslator(&qtTr);

    // application translator
    static QTranslator myTr;
    myTr.load(QLocale::system().name(), langsPath());
    app->installTranslator(&myTr);
}


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // app internationalization
    install_app_translators(&app);

    // read app arguments or exit on fail with detail error message
    AppArguments arguments(app.arguments());
    if (arguments.hasError()) {
        info_print_error_message(arguments.lastError());
        exit(EXIT_FAILURE);
    }

    // show usage and exit if command line argument list is empty
    // or arguments has '--help' options
    if (app.arguments().count() < 2 || arguments.hasHelp()) {
        show_usage_and_exit();
    }

    debug_print(arguments);

    // show fdsn service lists but not exit
    if (arguments.hasPrintFdsnwsEventServices()
            || arguments.hasPrintFdsnwsStationServices()
            || arguments.hasPrintFdsnwsDataselectServices()) {
        if (arguments.hasPrintFdsnwsEventServices()) {
            fdsnws_event_services_print();
        }
        if (arguments.hasPrintFdsnwsStationServices()) {
            fdsnws_station_services_print();
        }
        if (arguments.hasPrintFdsnwsDataselectServices()) {
            fdsnws_dataselect_services_print();
        }

        exit(EXIT_SUCCESS);
    }

    // if list of events or station should be displayed than display it and exit
    if (arguments.hasPrintSelectedEvents() || arguments.hasPrintSelectedTraces()) {
        if (arguments.hasPrintSelectedEvents()) {
            event_list_print(event_list_download(arguments, arguments.eventQuery()),
                             arguments.selectedEventsFormat());
        }

        if (arguments.hasPrintSelectedTraces()) {
            station_list_print(station_list_download(arguments, arguments.stationQuery()),
                               arguments.selectedTracesFormat());
        }

        exit(EXIT_SUCCESS);
    }

    // if --start-time and --end-time specify we no need to download the
    // event list
    if (arguments.hasEventQuery()) {
        download_data_by_event(arguments);
    }
    else {
        download_data_by_time(arguments);
    }

    return EXIT_SUCCESS;
}
