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
#include "dataselectquery.h"
#if QT_VERSION >= 0x050000
#include <QUrlQuery>
#endif


DataSelectQuery::DataSelectQuery()
{
}

void DataSelectQuery::setNetwork(const QString &network)
{
    m_network = network;
}

void DataSelectQuery::setStation(const QString &station)
{
    m_station = station;
}

void DataSelectQuery::setLocation(const QString &location)
{
    m_location = location;
}

void DataSelectQuery::setChannel(const QString &channel)
{
    m_channel = channel;
}

void DataSelectQuery::setStartTime(const QDateTime &startTime)
{
    m_startTime = startTime;
}

void DataSelectQuery::setEndTime(const QDateTime &endTime)
{
    m_endTime = endTime;
}

void DataSelectQuery::setUrl(const QUrl &url)
{
    m_url = url;
    if (!m_url.path().endsWith("/query")) {
        if (!m_url.path().endsWith("/")) {
            m_url.setPath(m_url.path() + "/");
        }

        m_url.setPath(m_url.path() + "query");
    }
}

QUrl DataSelectQuery::buildQueryUrl() const
{
#if QT_VERSION >= 0x050000
    QUrl url_ = m_url;
    QUrlQuery url;
#else
    QUrl url = m_url;
#endif

    url.addQueryItem("net", m_network);
    url.addQueryItem("sta", m_station);
    url.addQueryItem("loc", m_location.isEmpty() ? "--" : m_location);
    url.addQueryItem("cha", m_channel);
    url.addQueryItem("starttime", m_startTime.toString("yyyy-MM-ddTHH:mm:ss"));
    url.addQueryItem("endtime", m_endTime.toString("yyyy-MM-ddTHH:mm:ss"));

#if QT_VERSION >= 0x050000
    url_.setQuery(url);
    return url_;
#else
    return url;
#endif
}
