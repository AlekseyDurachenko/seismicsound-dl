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
#ifndef STATIONQUERY_H
#define STATIONQUERY_H


#include <QDateTime>
#include <QUrl>


class StationQuery
{
public:
    enum SearchTerms {
        All,
        Box,
        Radial
    };

    StationQuery();

    inline SearchTerms searchTerms() const;
    void setSearchTerms(SearchTerms searchTerms);

    inline const QString &network() const;
    void setNetwork(const QString &network);

    inline const QString &station() const;
    void setStation(const QString &station);

    inline const QString &channel() const;
    void setChannel(const QString &channel);

    inline const QString &location() const;
    void setLocation(const QString &location);

    inline const QDateTime &startTime() const;
    void setStartTime(const QDateTime &startTime);

    inline const QDateTime &endTime() const;
    void setEndTime(const QDateTime &endTime);

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

    QUrl buildQueryUrl() const;

private:
    SearchTerms m_searchTerms;
    QString m_network;
    QString m_station;
    QString m_channel;
    QString m_location;
    QDateTime m_startTime;
    QDateTime m_endTime;
    double m_minimumLatitude;
    double m_maximumLatitude;
    double m_minimumLongitude;
    double m_maximumLongitude;
    double m_latitude;
    double m_longitude;
    double m_minimumRadius;
    double m_maximumRadius;
    QUrl m_url;
};

StationQuery::SearchTerms StationQuery::searchTerms() const
{
    return m_searchTerms;
}

const QString &StationQuery::network() const
{
    return m_network;
}

const QString &StationQuery::station() const
{
    return m_station;
}

const QString &StationQuery::channel() const
{
    return m_channel;
}

const QString &StationQuery::location() const
{
    return m_location;
}

const QDateTime &StationQuery::startTime() const
{
    return m_startTime;
}

const QDateTime &StationQuery::endTime() const
{
    return m_endTime;
}

double StationQuery::minimumLatitude() const
{
    return m_minimumLatitude;
}

double StationQuery::maximumLatitude() const
{
    return m_maximumLatitude;
}

double StationQuery::minimumLongitude() const
{
    return m_minimumLongitude;
}

double StationQuery::maximumLongitude() const
{
    return m_maximumLongitude;
}

double StationQuery::latitude() const
{
    return m_latitude;
}

double StationQuery::longitude() const
{
    return m_longitude;
}

double StationQuery::minimumRadius() const
{
    return m_minimumRadius;
}

double StationQuery::maximumRadius() const
{
    return m_maximumRadius;
}

const QUrl &StationQuery::url() const
{
    return m_url;
}


#endif // STATIONQUERY_H
