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
#ifndef EVENT_H
#define EVENT_H


#include <QDateTime>


class Event
{
public:
    Event();
    Event(const QString &id,
          const QDateTime &time,
          double latitude,
          double longitude,
          double depth,
          const QString &magnitudeType,
          double magnitudeValue,
          const QString &description);

    inline bool isNull() const;

    inline const QString &id() const;
    void setId(const QString &id);

    inline const QDateTime &time() const;
    void setTime(const QDateTime &time);

    inline double latitude() const;
    void setLatitude(double latitude);

    inline double longitude() const;
    void setLongitude(double longitude);

    inline double depth() const;
    void setDepth(double depth);

    inline const QString &magnitudeType() const;
    void setMagnitudeType(const QString &magnitudeType);

    inline double magnitudeValue() const;
    void setMagnitudeValue(double magnitudeValue);

    inline const QString &description() const;
    void setDescription(const QString &description);

private:
    QString m_id;
    QDateTime m_time;
    double m_latitude;
    double m_longitude;
    double m_depth;
    QString m_magnitudeType;
    double m_magnitudeValue;
    QString m_description;
};

bool Event::isNull() const
{
    return m_time.isNull();
}

const QString &Event::id() const
{
    return m_id;
}

const QDateTime &Event::time() const
{
    return m_time;
}

double Event::latitude() const
{
    return m_latitude;
}

double Event::longitude() const
{
    return m_longitude;
}

double Event::depth() const
{
    return m_depth;
}

const QString &Event::magnitudeType() const
{
    return m_magnitudeType;
}

double Event::magnitudeValue() const
{
    return m_magnitudeValue;
}

const QString &Event::description() const
{
    return m_description;
}


#endif // EVENT_H
