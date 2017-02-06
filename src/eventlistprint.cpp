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
#include "eventlistprint.h"
#include <QObject>
#include <iostream>


static QString create_header(const QString &format)
{
    QString result = format;
    result.replace("%eid%",     QString("%1").arg(QObject::tr("ID"), 9));
    result.replace("%type%",    QString("%1").arg(QObject::tr("TYPE"), 4));
    result.replace("%val%",     QString("%1").arg(QObject::tr("MAG"), 4));
    result.replace("%lat%",     QString("%1").arg(QObject::tr("LATITUDE"), 9));
    result.replace("%lon%",     QString("%1").arg(QObject::tr("LONGITUDE"), 9));
    result.replace("%depth%",   QString("%1").arg(QObject::tr("DEPTH"), 9));
    result.replace("%time%",    QString("%1").arg(QObject::tr("TIME"), 19));
    result.replace("%desc%",    QObject::tr("DESCRIPTION"));
    return result;
}


static QString create_splitter_line(const QString &format)
{
    return QString().fill('-', create_header(format).length());
}


static QString create_event_line(const Event &event, const QString &format)
{
    QString result = format;
    result.replace("%eid%",     QString("%1").arg(event.id(), 9));
    result.replace("%type%",    QString("%1").arg(event.magnitudeType(), 4));
    result.replace("%val%",     QString("%1").arg(event.magnitudeValue(), 4, 'f', 1));
    result.replace("%lat%",     QString("%1").arg(event.latitude(), 9, 'f', 4));
    result.replace("%lon%",     QString("%1").arg(event.longitude(), 9, 'f', 4));
    result.replace("%depth%",   QString("%1").arg(event.depth() / 1000.0, 9, 'f', 3));
    result.replace("%time%",    QString("%1").arg(event.time().toString(DisplayDateTimeFormat)));
    result.replace("%desc%",    event.description());
    return result;
}


void event_list_print(const QList<Event> &events, const QString &format)
{
    std::cout << create_splitter_line(format).toStdString();
    std::cout << std::endl;
    std::cout << QObject::tr("List of Events").toStdString();
    std::cout << std::endl;
    std::cout << create_splitter_line(format).toStdString();
    std::cout << std::endl;
    std::cout << create_header(format).toStdString();
    std::cout << std::endl;
    std::cout << create_splitter_line(format).toStdString();
    std::cout << std::endl;
    foreach (const Event &event, events) {
        std::cout << create_event_line(event, format).toStdString();
        std::cout << std::endl;
    }
    std::cout << create_splitter_line(format).toStdString();
    std::cout << std::endl;
    std::cout << QObject::tr("Total: %1").arg(events.count()).toStdString();
    std::cout << std::endl;
}
