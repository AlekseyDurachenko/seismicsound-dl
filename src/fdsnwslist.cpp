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
#include "fdsnwslist.h"
#include <QObject>
#include <sstream>
#include <iostream>
#include <iomanip>


typedef struct {
    const char *code;
    const char *url;
    const char *desc;
} ServiceUrl;


const int DataselectServiceCount = 15;
static ServiceUrl DataselectServices[DataselectServiceCount] = {
    "0010", "http://service.iris.edu/fdsnws/dataselect/1/", "IRIS Data Management Center",
    "0020", "http://service.ncedc.org/fdsnws/dataselect/1/", "Northern California Earthquake Data Center",
    "0030", "http://service.scedc.caltech.edu/fdsnws/dataselect/1/", "Southern California Earthquake Data Center",
    "0050", "http://eida.bgr.de/fdsnws/dataselect/1/", "BGR Hannover, Germany",
    "0060", "http://eida-service.koeri.boun.edu.tr/fdsnws/dataselect/1/", "Boğaziçi University, Kandilli Observatory",
    "0070", "http://eida.ethz.ch/fdsnws/dataselect/1/", "ETHZ",
    "0080", "http://geofon.gfz-potsdam.de/fdsnws/dataselect/1/", "GEOFON Program, GFZ",
    "0090", "http://eida.ipgp.fr/fdsnws/dataselect/1/", "IPGP Data Center",
    "0100", "http://webservices.rm.ingv.it/fdsnws/dataselect/1/", "INGV",
    "0120", "http://erde.geophysik.uni-muenchen.de/fdsnws/dataselect/1/", "LMU Munich, Germany",
    "0130", "http://eida-sc3.infp.ro/fdsnws/dataselect/1/", "NIEP, Romania",
    "0140", "http://eida.gein.noa.gr/fdsnws/dataselect/1/", "NOA, Greece",
    "0150", "http://www.orfeus-eu.org/fdsnws/dataselect/1/", "ORFEUS Data Center",
    "0160", "http://ws.resif.fr/fdsnws/dataselect/1/", "RESIF",
    "0170", "http://seisrequest.iag.usp.br/fdsnws/dataselect/1/", "USP Seismological Center, Brazil"
};


const int StationServiceCount = 15;
static ServiceUrl StationServices[StationServiceCount] = {
    "0010", "http://service.iris.edu/fdsnws/station/1/", "IRIS Data Management Center",
    "0020", "http://service.ncedc.org/fdsnws/station/1/", "Northern California Earthquake Data Center",
    "0030", "http://service.scedc.caltech.edu/fdsnws/station/1/", "Southern California Earthquake Data Center",
    "0050", "http://eida.bgr.de/fdsnws/station/1/", "BGR Hannover, Germany",
    "0060", "http://eida-service.koeri.boun.edu.tr/fdsnws/station/1/", "Boğaziçi University, Kandilli Observatory",
    "0070", "http://eida.ethz.ch/fdsnws/station/1/", "ETHZ",
    "0080", "http://geofon.gfz-potsdam.de/fdsnws/station/1/", "GEOFON Program, GFZ",
    "0090", "http://eida.ipgp.fr/fdsnws/station/1/", "IPGP Data Center",
    "0100", "http://webservices.rm.ingv.it/fdsnws/station/1/", "INGV",
    "0120", "http://erde.geophysik.uni-muenchen.de/fdsnws/station/1/", "LMU Munich, Germany",
    "0130", "http://eida-sc3.infp.ro/fdsnws/station/1/", "NIEP, Romania",
    "0140", "http://eida.gein.noa.gr/fdsnws/station/1/", "NOA, Greece",
    "0150", "http://www.orfeus-eu.org/fdsnws/station/1/", "ORFEUS Data Center",
    "0160", "http://ws.resif.fr/fdsnws/station/1/", "RESIF",
    "0170", "http://seisrequest.iag.usp.br/fdsnws/station/1/", "USP Seismological Center, Brazil"
};


const int EventServiceCount = 7;
static ServiceUrl EventServices[EventServiceCount] = {
    "0010", "http://service.iris.edu/fdsnws/event/1/", "IRIS Data Management Center",
    "0020", "http://service.ncedc.org/fdsnws/event/1/", "Northern California Earthquake Data Center",
    "0030", "http://service.scedc.caltech.edu/fdsnws/event/1/", "Southern California Earthquake Data Center",
    "0040", "http://earthquake.usgs.gov/fdsnws/event/1/", "United States Geological Survey",
    "0070", "http://arclink.ethz.ch/fdsnws/event/1/", "ETHZ",
    "0100", "http://webservices.rm.ingv.it/fdsnws/event/1/", "INGV",
    "0110", "http://www.isc.ac.uk/fdsnws/event/1/", "ISC (International Seismological Centre)"
};


static int find_index_by_code(const QString &code, ServiceUrl *services, int count)
{
    for (int i = 0; i < count; ++i) {
        if (code == services[i].code) {
            return i;
        }
    }

    return -1;
}


static QString create_header()
{
    QString result = QString(" %code% | %url% | %desc% ");
    result.replace("%code%", QString("%1").arg(QObject::tr("CODE"), -4));
    result.replace("%url%", QString("%1").arg(QObject::tr("URL"), -60));
    result.replace("%desc%", QObject::tr("DESC"));
    return result;
}


static QString create_url_line(const ServiceUrl &url)
{
    QString result = QString(" %code% | %url% | %desc% ");
    result.replace("%code%", QString("%1").arg(url.code, -4));
    result.replace("%url%", QString("%1").arg(url.url, -60));
    result.replace("%desc%", url.desc);
    return result;
}


static QString create_splitter_line()
{
    return QString().fill('-', create_header().length());
}


void fdsnws_dataselect_services_print()
{
    std::cout << create_splitter_line().toStdString() << std::endl;
    std::cout << QObject::tr("List of known FDSNWS dataselect Web Services").toStdString() << std::endl;
    std::cout << create_splitter_line().toStdString() << std::endl;
    std::cout << create_header().toStdString() << std::endl;
    std::cout << create_splitter_line().toStdString() << std::endl;
    for (int i = 0; i < DataselectServiceCount; ++i) {
        std::cout << create_url_line(DataselectServices[i]).toStdString() << std::endl;
    }
}


void fdsnws_station_services_print()
{
    std::cout << create_splitter_line().toStdString() << std::endl;
    std::cout << QObject::tr("List of known FDSNWS station Web Services").toStdString() << std::endl;
    std::cout << create_splitter_line().toStdString() << std::endl;
    std::cout << create_header().toStdString() << std::endl;
    std::cout << create_splitter_line().toStdString() << std::endl;
    for (int i = 0; i < StationServiceCount; ++i) {
        std::cout << create_url_line(StationServices[i]).toStdString() << std::endl;
    }
}


void fdsnws_event_services_print()
{
    std::cout << create_splitter_line().toStdString() << std::endl;
    std::cout << QObject::tr("List of known FDSNWS event Web Services").toStdString() << std::endl;
    std::cout << create_splitter_line().toStdString() << std::endl;
    std::cout << create_header().toStdString() << std::endl;
    std::cout << create_splitter_line().toStdString() << std::endl;
    for (int i = 0; i < EventServiceCount; ++i) {
        std::cout << create_url_line(EventServices[i]).toStdString() << std::endl;
    }
}


bool fdsnws_dataselect_contains(const QString &code)
{
    if (find_index_by_code(code, DataselectServices, DataselectServiceCount) != -1) {
        return true;
    }

    return false;
}


bool fdsnws_station_contains(const QString &code)
{
    if (find_index_by_code(code, StationServices, StationServiceCount) != -1) {
        return true;
    }

    return false;
}


bool fdsnws_event_contains(const QString &code)
{
    if (find_index_by_code(code, EventServices, EventServiceCount) != -1) {
        return true;
    }

    return false;
}


QUrl fdsnws_dataselect_url(const QString &code)
{
    const int index = find_index_by_code(code, DataselectServices, DataselectServiceCount);
    if (index == -1) {
        return QUrl();
    }

    return QUrl(DataselectServices[index].url);
}


QUrl fdsnws_station_url(const QString &code)
{
    const int index = find_index_by_code(code, StationServices, StationServiceCount);
    if (index == -1) {
        return QUrl();
    }

    return QUrl(StationServices[index].url);
}


QUrl fdsnws_event_url(const QString &code)
{
    const int index = find_index_by_code(code, EventServices, EventServiceCount);
    if (index == -1) {
        return QUrl();
    }

    return QUrl(EventServices[index].url);
}


QString fdsnws_dataselect_desc(const QString &code)
{
    const int index = find_index_by_code(code, DataselectServices, DataselectServiceCount);
    if (index == -1) {
        return QString();
    }

    return QString(DataselectServices[index].desc);
}


QString fdsnws_station_desc(const QString &code)
{
    const int index = find_index_by_code(code, StationServices, StationServiceCount);
    if (index == -1) {
        return QString();
    }

    return QString(StationServices[index].desc);
}


QString fdsnws_event_desc(const QString &code)
{
    const int index = find_index_by_code(code, EventServices, EventServiceCount);
    if (index == -1) {
        return QString();
    }

    return QString(EventServices[index].desc);
}


QString fdsnws_dataselect_default_code()
{
    return QString(DataselectServices[0].code);
}


QString fdsnws_station_default_code()
{
    return QString(StationServices[0].code);
}


QString fdsnws_event_default_code()
{
    return QString(EventServices[0].code);
}
