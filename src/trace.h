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
#ifndef TRACE_H
#define TRACE_H


#include <QString>
#include <QDateTime>


class Trace
{
public:
    Trace();

    inline bool isNull() const;

    inline const QString &network() const;
    void setNetwork(const QString &network);

    inline const QString &station() const;
    void setStation(const QString &station);

    inline const QString &location() const;
    void setLocation(const QString &location);

    inline const QString &channel() const;
    void setChannel(const QString &channel);

    inline double latitude() const;
    void setLatitude(double latitude);

    inline double longitude() const;
    void setLongitude(double longitude);

    inline const QDateTime &startTime() const;
    void setStartTime(const QDateTime &startTime);

    inline const QDateTime &endTime() const;
    void setEndTime(const QDateTime &endTime);

    inline double elevation() const;
    void setElevation(double elevation);

    inline double depth() const;
    void setDepth(double depth);

    inline const QString &siteName() const;
    void setSiteName(const QString &siteName);

private:
    QString m_network;
    QString m_station;
    QString m_location;
    QString m_channel;
    double m_latitude;
    double m_longitude;
    QDateTime m_startTime;
    QDateTime m_endTime;
    double m_elevation;
    double m_depth;
    QString m_siteName;
};

bool Trace::isNull() const
{
    return m_network.isNull()
           || m_station.isNull()
           || m_location.isNull()
           || m_channel.isNull();
}

const QString &Trace::network() const
{
    return m_network;
}

const QString &Trace::station() const
{
    return m_station;
}

const QString &Trace::location() const
{
    return m_location;
}

const QString &Trace::channel() const
{
    return m_channel;
}

double Trace::latitude() const
{
    return m_latitude;
}

double Trace::longitude() const
{
    return m_longitude;
}

const QDateTime &Trace::startTime() const
{
    return m_startTime;
}

const QDateTime &Trace::endTime() const
{
    return m_endTime;
}

double Trace::elevation() const
{
    return m_elevation;
}

double Trace::depth() const
{
    return m_depth;
}

const QString &Trace::siteName() const
{
    return m_siteName;
}


#endif // TRACE_H
