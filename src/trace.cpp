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
#include "trace.h"


Trace::Trace()
{
    m_latitude = 0.0;
    m_longitude = 0.0;
    m_elevation = 0.0;
    m_depth = 0.0;
}

void Trace::setNetwork(const QString &network)
{
    m_network = network;
}

void Trace::setStation(const QString &station)
{
    m_station = station;
}

void Trace::setLocation(const QString &location)
{
    m_location = location;
}

void Trace::setChannel(const QString &channel)
{
    m_channel = channel;
}

void Trace::setLatitude(double latitude)
{
    m_latitude = latitude;
}

void Trace::setLongitude(double longitude)
{
    m_longitude = longitude;
}

void Trace::setStartTime(const QDateTime &startTime)
{
    m_startTime = startTime;
}

void Trace::setEndTime(const QDateTime &endTime)
{
    m_endTime = endTime;
}

void Trace::setElevation(double elevation)
{
    m_elevation = elevation;
}

void Trace::setDepth(double depth)
{
    m_depth = depth;
}

void Trace::setSiteName(const QString &siteName)
{
    m_siteName = siteName;
}
