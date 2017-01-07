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
#include "stationquery.h"
#include "consts.h"
#if QT_VERSION >= 0x050000
#include <QUrlQuery>
#endif


StationQuery::StationQuery()
{
    m_searchTerms = All;
    m_minimumLatitude = InvalidLatitude;
    m_maximumLatitude = InvalidLatitude;
    m_minimumLongitude = InvalidLongitude;
    m_maximumLongitude = InvalidLongitude;
    m_latitude = InvalidLatitude;
    m_longitude = InvalidLongitude;
    m_minimumRadius = InvalidRadius;
    m_maximumRadius = InvalidRadius;
}

void StationQuery::setSearchTerms(StationQuery::SearchTerms searchTerms)
{
    m_searchTerms = searchTerms;
}

void StationQuery::setNetwork(const QString &network)
{
    m_network = network;
}

void StationQuery::setStation(const QString &station)
{
    m_station = station;
}

void StationQuery::setChannel(const QString &channel)
{
    m_channel = channel;
}

void StationQuery::setLocation(const QString &location)
{
    m_location = location;
}

void StationQuery::setStartTime(const QDateTime &startTime)
{
    m_startTime = startTime;
}

void StationQuery::setEndTime(const QDateTime &endTime)
{
    m_endTime = endTime;
}

void StationQuery::setMinimumLatitude(double minimumLatitude)
{
    m_minimumLatitude = minimumLatitude;
}

void StationQuery::setMaximumLatitude(double maximumLatitude)
{
    m_maximumLatitude = maximumLatitude;
}

void StationQuery::setMinimumLongitude(double minimumLongitude)
{
    m_minimumLongitude = minimumLongitude;
}

void StationQuery::setMaximumLongitude(double maximumLongitude)
{
    m_maximumLongitude = maximumLongitude;
}

void StationQuery::setLatitude(double latitude)
{
    m_latitude = latitude;
}

void StationQuery::setLongitude(double longitude)
{
    m_longitude = longitude;
}

void StationQuery::setMinimumRadius(double radius)
{
    m_minimumRadius = radius;
}

void StationQuery::setMaximumRadius(double radius)
{
    m_maximumRadius = radius;
}

void StationQuery::setUrl(const QUrl &url)
{
    m_url = url;
    if (!m_url.path().endsWith("/query")) {
        if (!m_url.path().endsWith("/")) {
            m_url.setPath(m_url.path() + "/");
        }

        m_url.setPath(m_url.path() + "query");
    }
}

QUrl StationQuery::buildQueryUrl() const
{
#if QT_VERSION >= 0x050000
    QUrl url_ = m_url;
    QUrlQuery url;
#else
    QUrl url = m_url;
#endif

    url.addQueryItem("level", "channel");
    url.addQueryItem("includecomments", "false");
    url.addQueryItem("format", "xml");

    if (!m_network.isEmpty()) {
        url.addQueryItem("network", m_network);
    }
    if (!m_station.isEmpty()) {
        url.addQueryItem("station", m_station);
    }
    if (!m_channel.isEmpty()) {
        url.addQueryItem("channel", m_channel);
    }
    if (!m_location.isEmpty()) {
        url.addQueryItem("location", m_location);
    }
    if (!m_startTime.isNull()) {
        url.addQueryItem("starttime", m_startTime.toString("yyyy-MM-ddThh:mm:ss"));
    }
    if (!m_endTime.isNull()) {
        url.addQueryItem("endtime", m_endTime.toString("yyyy-MM-ddThh:mm:ss"));
    }
    if (m_searchTerms == SearchTerms::Box) {
        url.addQueryItem("minlatitude", QString::number(m_minimumLatitude, 'f', 6));
        url.addQueryItem("maxlatitude", QString::number(m_maximumLatitude, 'f', 6));
        url.addQueryItem("minlongitude", QString::number(m_minimumLongitude, 'f', 6));
        url.addQueryItem("maxlongitude", QString::number(m_maximumLongitude, 'f', 6));
    }
    else if (m_searchTerms == SearchTerms::Radial) {
        url.addQueryItem("latitude", QString::number(m_latitude, 'f', 6));
        url.addQueryItem("longitude", QString::number(m_longitude, 'f', 6));
        url.addQueryItem("minradius", QString::number(m_minimumRadius, 'f', 6));
        url.addQueryItem("maxradius", QString::number(m_maximumRadius, 'f', 6));
    }

#if QT_VERSION >= 0x050000
    url_.setQuery(url);
    return url_;
#else
    return url;
#endif
}
