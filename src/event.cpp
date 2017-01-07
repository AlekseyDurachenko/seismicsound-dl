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
#include "event.h"


Event::Event()
{
    m_latitude = 0.0;
    m_longitude = 0.0;
    m_depth = 0.0;
    m_magnitudeValue = 0.0;
}

Event::Event(const QString &id,
             const QDateTime &time,
             double latitude,
             double longitude,
             double depth,
             const QString &magnitudeType,
             double magnitudeValue,
             const QString &description)
{
    m_id = id;
    m_time = time;
    m_latitude = latitude;
    m_longitude = longitude;
    m_depth = depth;
    m_magnitudeType = magnitudeType;
    m_magnitudeValue = magnitudeValue;
    m_description = description;
}

void Event::setId(const QString &id)
{
    m_id = id;
}

void Event::setTime(const QDateTime &time)
{
    m_time = time;
}

void Event::setLatitude(double latitude)
{
    m_latitude = latitude;
}

void Event::setLongitude(double longitude)
{
    m_longitude = longitude;
}

void Event::setDepth(double depth)
{
    m_depth = depth;
}

void Event::setMagnitudeType(const QString &magnitudeType)
{
    m_magnitudeType = magnitudeType;
}

void Event::setMagnitudeValue(double magnitudeValue)
{
    m_magnitudeValue = magnitudeValue;
}

void Event::setDescription(const QString &description)
{
    m_description = description;
}
