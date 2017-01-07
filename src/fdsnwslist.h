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
#ifndef FDSNWSLIST_H
#define FDSNWSLIST_H


#include <QString>
#include <QUrl>

void fdsnws_dataselect_services_print();
void fdsnws_station_services_print();
void fdsnws_event_services_print();

bool fdsnws_dataselect_contains(const QString &code);
bool fdsnws_station_contains(const QString &code);
bool fdsnws_event_contains(const QString &code);

QUrl fdsnws_dataselect_url(const QString &code);
QUrl fdsnws_station_url(const QString &code);
QUrl fdsnws_event_url(const QString &code);

QString fdsnws_dataselect_desc(const QString &code);
QString fdsnws_station_desc(const QString &code);
QString fdsnws_event_desc(const QString &code);

QString fdsnws_dataselect_default_code();
QString fdsnws_station_default_code();
QString fdsnws_event_default_code();


#endif // FDSNWSLIST_H
