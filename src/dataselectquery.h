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
#ifndef DATASELECTQUERY_H
#define DATASELECTQUERY_H


#include <QUrl>
#include <QDateTime>


class DataSelectQuery
{
public:
    DataSelectQuery();

    inline const QString &network() const;
    void setNetwork(const QString &network);

    inline const QString &station() const;
    void setStation(const QString &station);

    inline const QString &location() const;
    void setLocation(const QString &location);

    inline const QString &channel() const;
    void setChannel(const QString &channel);

    inline const QDateTime &startTime() const;
    void setStartTime(const QDateTime &startTime);

    inline const QDateTime &endTime() const;
    void setEndTime(const QDateTime &endTime);

    inline const QUrl &url() const;
    void setUrl(const QUrl &url);

    QUrl buildQueryUrl() const;

private:
    QString m_network;
    QString m_station;
    QString m_location;
    QString m_channel;
    QDateTime m_startTime;
    QDateTime m_endTime;
    QUrl m_url;
};

const QString &DataSelectQuery::network() const
{
    return m_network;
}

const QString &DataSelectQuery::station() const
{
    return m_station;
}

const QString &DataSelectQuery::location() const
{
    return m_location;
}

const QString &DataSelectQuery::channel() const
{
    return m_channel;
}

const QDateTime &DataSelectQuery::startTime() const
{
    return m_startTime;
}

const QDateTime &DataSelectQuery::endTime() const
{
    return m_endTime;
}

const QUrl &DataSelectQuery::url() const
{
    return m_url;
}


#endif // DATASELECTQUERY_H
