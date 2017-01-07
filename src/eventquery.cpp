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
#include "eventquery.h"
#include "consts.h"
#if QT_VERSION >= 0x050000
#include <QUrlQuery>
#endif


EventQuery::EventQuery()
{
    m_searchTerms = All;
    m_minimumMagnitude = InvalidMagnitude;
    m_maximumMagnitude = InvalidMagnitude;
    m_minimumDepth = InvalidDepth;
    m_maximumDepth = InvalidDepth;
    m_minimumLatitude = InvalidLatitude;
    m_maximumLatitude = InvalidLatitude;
    m_minimumLongitude = InvalidLongitude;
    m_maximumLongitude = InvalidLongitude;
    m_latitude = InvalidLatitude;
    m_longitude = InvalidLongitude;
    m_minimumRadius = InvalidRadius;
    m_maximumRadius = InvalidRadius;
    m_limit = InvalidLimit;
    m_offset = InvalidOffset;
}

void EventQuery::setSearchTerms(EventQuery::SearchTerms searchTerms)
{
    m_searchTerms = searchTerms;
}

void EventQuery::setId(const QString &id)
{
    m_id = id;
}

void EventQuery::setStartTime(const QDateTime &startTime)
{
    m_startTime = startTime;
}

void EventQuery::setEndTime(const QDateTime &endTime)
{
    m_endTime = endTime;
}

void EventQuery::setMinimumMagnitude(double minimumMagnitude)
{
    m_minimumMagnitude = minimumMagnitude;
}

void EventQuery::setMaximumMagnitude(double maximumMagnitude)
{
    m_maximumMagnitude = maximumMagnitude;
}

void EventQuery::setMinimumDepth(double minimumDepth)
{
    m_minimumDepth = minimumDepth;
}

void EventQuery::setMaximumDepth(double maximumDepth)
{
    m_maximumDepth = maximumDepth;
}

void EventQuery::setMinimumLatitude(double minimumLatitude)
{
    m_minimumLatitude = minimumLatitude;
}

void EventQuery::setMaximumLatitude(double maximumLatitude)
{
    m_maximumLatitude = maximumLatitude;
}

void EventQuery::setMinimumLongitude(double minimumLongitude)
{
    m_minimumLongitude = minimumLongitude;
}

void EventQuery::setMaximumLongitude(double maximumLongitude)
{
    m_maximumLongitude = maximumLongitude;
}

void EventQuery::setLatitude(double latitude)
{
    m_latitude = latitude;
}

void EventQuery::setLongitude(double longitude)
{
    m_longitude = longitude;
}

void EventQuery::setMinimumRadius(double radius)
{
    m_minimumRadius = radius;
}

void EventQuery::setMaximumRadius(double radius)
{
    m_maximumRadius = radius;
}

void EventQuery::setUrl(const QUrl &url)
{
    m_url = url;
    if (!m_url.path().endsWith("/query")) {
        if (!m_url.path().endsWith("/")) {
            m_url.setPath(m_url.path() + "/");
        }

        m_url.setPath(m_url.path() + "query");
    }
}

void EventQuery::setLimit(int limit)
{
    m_limit = limit;
}

void EventQuery::setOffset(int offset)
{
    m_offset = offset;
}

QUrl EventQuery::buildQueryUrl() const
{
#if QT_VERSION >= 0x050000
    QUrl url_ = m_url;
    QUrlQuery url;
#else
    QUrl url = m_url;
#endif

    url.addQueryItem("format", "xml");

    if (!m_id.isEmpty()) {
        url.addQueryItem("eventid", m_id);
    }
    else {
        if (!m_startTime.isNull()) {
            url.addQueryItem("starttime", m_startTime.toString("yyyy-MM-ddThh:mm:ss"));
        }
        if (!m_endTime.isNull()) {
            url.addQueryItem("endtime", m_endTime.toString("yyyy-MM-ddThh:mm:ss"));
        }
        if (!qFuzzyCompare(m_minimumMagnitude, InvalidMagnitude)) {
            url.addQueryItem("minmagnitude", QString::number(m_minimumMagnitude, 'f', 6));
        }
        if (!qFuzzyCompare(m_maximumMagnitude, InvalidMagnitude)) {
            url.addQueryItem("maxmagnitude", QString::number(m_maximumMagnitude, 'f', 6));
        }
        if (!qFuzzyCompare(m_minimumDepth, InvalidDepth)) {
            url.addQueryItem("mindepth", QString::number(m_minimumDepth, 'f', 6));
        }
        if (!qFuzzyCompare(m_maximumDepth, InvalidDepth)) {
            url.addQueryItem("maxdepth", QString::number(m_maximumDepth, 'f', 6));
        }
        if (m_searchTerms == Box) {
            url.addQueryItem("minlatitude", QString::number(m_minimumLatitude, 'f', 6));
            url.addQueryItem("maxlatitude", QString::number(m_maximumLatitude, 'f', 6));
            url.addQueryItem("minlongitude", QString::number(m_minimumLongitude, 'f', 6));
            url.addQueryItem("maxlongitude", QString::number(m_maximumLongitude, 'f', 6));
        }
        else if (m_searchTerms == Radial) {
            url.addQueryItem("latitude", QString::number(m_latitude, 'f', 6));
            url.addQueryItem("longitude", QString::number(m_longitude, 'f', 6));
            url.addQueryItem("minradius", QString::number(m_minimumRadius, 'f', 6));
            url.addQueryItem("maxradius", QString::number(m_maximumRadius, 'f', 6));
        }
        if (m_limit != InvalidLimit) {
            url.addQueryItem("limit", QString::number(m_limit));
        }
        if (m_offset != InvalidOffset) {
            url.addQueryItem("offset", QString::number(m_offset));
        }
    }

#if QT_VERSION >= 0x050000
    url_.setQuery(url);
    return url_;
#else
    return url;
#endif
}
