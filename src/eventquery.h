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
#ifndef EVENTQUERY_H
#define EVENTQUERY_H


#include <QDateTime>
#include <QUrl>


class EventQuery
{
public:
    enum SearchTerms {
        All,
        Box,
        Radial
    };

    EventQuery();

    inline SearchTerms searchTerms() const;
    void setSearchTerms(SearchTerms searchTerms);

    inline const QString &id() const;
    void setId(const QString &id);

    inline const QDateTime &startTime() const;
    void setStartTime(const QDateTime &startTime);

    inline const QDateTime &endTime() const;
    void setEndTime(const QDateTime &endTime);

    inline double minimumMagnitude() const;
    void setMinimumMagnitude(double minimumMagnitude);

    inline double maximumMagnitude() const;
    void setMaximumMagnitude(double maximumMagnitude);

    inline double minimumDepth() const;
    void setMinimumDepth(double minimumDepth);

    inline double maximumDepth() const;
    void setMaximumDepth(double maximumDepth);

    inline double minimumLatitude() const;
    void setMinimumLatitude(double minimumLatitude);

    inline double maximumLatitude() const;
    void setMaximumLatitude(double maximumLatitude);

    inline double minimumLongitude() const;
    void setMinimumLongitude(double minimumLongitude);

    inline double maximumLongitude() const;
    void setMaximumLongitude(double maximumLongitude);

    inline double latitude() const;
    void setLatitude(double latitude);

    inline double longitude() const;
    void setLongitude(double longitude);

    inline double minimumRadius() const;
    void setMinimumRadius(double radius);

    inline double maximumRadius() const;
    void setMaximumRadius(double radius);

    inline const QUrl &url() const;
    void setUrl(const QUrl &url);

    inline int limit() const;
    void setLimit(int limit);

    inline int offset() const;
    void setOffset(int offset);

    QUrl buildQueryUrl() const;

private:
    QString m_id;
    SearchTerms m_searchTerms;
    QDateTime m_startTime;
    QDateTime m_endTime;
    double m_minimumMagnitude;
    double m_maximumMagnitude;
    double m_minimumDepth;
    double m_maximumDepth;
    double m_minimumLatitude;
    double m_maximumLatitude;
    double m_minimumLongitude;
    double m_maximumLongitude;
    double m_latitude;
    double m_longitude;
    double m_minimumRadius;
    double m_maximumRadius;
    QUrl m_url;
    int m_limit;
    int m_offset;
};


EventQuery::SearchTerms EventQuery::searchTerms() const
{
    return m_searchTerms;
}

const QString &EventQuery::id() const
{
    return m_id;
}

const QDateTime &EventQuery::startTime() const
{
    return m_startTime;
}

const QDateTime &EventQuery::endTime() const
{
    return m_endTime;
}

double EventQuery::minimumMagnitude() const
{
    return m_minimumMagnitude;
}

double EventQuery::maximumMagnitude() const
{
    return m_maximumMagnitude;
}

double EventQuery::minimumDepth() const
{
    return m_minimumDepth;
}

double EventQuery::maximumDepth() const
{
    return m_maximumDepth;
}

double EventQuery::minimumLatitude() const
{
    return m_minimumLatitude;
}

double EventQuery::maximumLatitude() const
{
    return m_maximumLatitude;
}

double EventQuery::minimumLongitude() const
{
    return m_minimumLongitude;
}

double EventQuery::maximumLongitude() const
{
    return m_maximumLongitude;
}

double EventQuery::latitude() const
{
    return m_latitude;
}

double EventQuery::longitude() const
{
    return m_longitude;
}

double EventQuery::minimumRadius() const
{
    return m_minimumRadius;
}

double EventQuery::maximumRadius() const
{
    return m_maximumRadius;
}

const QUrl &EventQuery::url() const
{
    return m_url;
}

int EventQuery::limit() const
{
    return m_limit;
}

int EventQuery::offset() const
{
    return m_offset;
}


#endif // EVENTQUERY_H
