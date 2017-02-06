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
#include "stationlistprint.h"
#include <QObject>
#include <iostream>


static QString create_header(const QString &format)
{
    QString result = format;
    result.replace("%net%",     QString("%1").arg(QObject::tr("NET"), 3));
    result.replace("%sta%",     QString("%1").arg(QObject::tr("STA"), 5));
    result.replace("%loc%",     QString("%1").arg(QObject::tr("LOC"), 3));
    result.replace("%chan%",    QString("%1").arg(QObject::tr("CHAN"), 4));
    result.replace("%lat%",     QString("%1").arg(QObject::tr("LATITUDE"), 9));
    result.replace("%lon%",     QString("%1").arg(QObject::tr("LONGITUDE"), 9));
    result.replace("%elevat%",  QString("%1").arg(QObject::tr("ELEVAT"), 6));
    result.replace("%depth%",   QString("%1").arg(QObject::tr("DEPTH"), 5));
    result.replace("%stime%",   QString("%1").arg(QObject::tr("START TIME"), 19));
    result.replace("%etime%",   QString("%1").arg(QObject::tr("END TIME"), 19));
    result.replace("%site%",    QObject::tr("SITE NAME"));
    return result;
}


static QString create_splitter_line(const QString &format)
{
    return QString().fill('-', create_header(format).length());
}


static QString create_channel_line(const Trace &trace, const QString &format)
{
    QString result = format;
    result.replace("%net%",     QString("%1").arg(trace.network(), 3, ' '));
    result.replace("%sta%",     QString("%1").arg(trace.station(), 5, ' '));
    result.replace("%loc%",     QString("%1").arg(trace.location(), 3, ' '));
    result.replace("%chan%",    QString("%1").arg(trace.channel(), 4, ' '));
    result.replace("%lat%",     QString("%1").arg(trace.latitude(), 9, 'f', 4));
    result.replace("%lon%",     QString("%1").arg(trace.longitude(), 9, 'f', 4));
    result.replace("%elevat%",  QString("%1").arg(trace.elevation() / 1000.0, 6, 'f', 3));
    result.replace("%depth%",   QString("%1").arg(trace.depth() / 1000.0, 5, 'f', 3));
    result.replace("%stime%",   QString("%1").arg(trace.startTime().toString(DisplayDateTimeFormat)));
    result.replace("%etime%",   QString("%1").arg(trace.endTime().toString(DisplayDateTimeFormat)));
    result.replace("%site%",    trace.siteName());
    return result;
}


void station_list_print(const QList<Trace> &traces, const QString &format)
{
    std::cout << create_splitter_line(format).toStdString();
    std::cout << std::endl;
    std::cout << QObject::tr("List of Channels").toStdString();
    std::cout << std::endl;
    std::cout << create_splitter_line(format).toStdString();
    std::cout << std::endl;
    std::cout << create_header(format).toStdString();
    std::cout << std::endl;
    std::cout << create_splitter_line(format).toStdString();
    std::cout << std::endl;
    int total = 0;
    foreach (const Trace &trace, traces) {
        std::cout << create_channel_line(trace, format).toStdString();
        std::cout << std::endl;
        total += 1;
    }
    std::cout << create_splitter_line(format).toStdString();
    std::cout << std::endl;
    std::cout << QObject::tr("Total: %1").arg(total).toStdString();
    std::cout << std::endl;
}
