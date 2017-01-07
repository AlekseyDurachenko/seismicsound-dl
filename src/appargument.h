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
#ifndef APPARGUMENT_H
#define APPARGUMENT_H


#include "consts.h"
#include <QVariant>
#include <QRegExp>
#include <QDateTime>
#include <QUrl>


class AppArgument
{
public:
    enum Type { Bool, Integer, Double, String, DateTime, Url };

public:
    explicit AppArgument(Type type = Bool);

    inline bool isFound() const;
    void setFound(bool found);

    inline Type type() const;
    void setType(Type type);

    inline const QString &key() const;
    void setKey(const QString &key);

    inline const QVariant &value() const;
    void setValue(const QVariant &value);

    inline qint64 minimumInteger() const;
    inline qint64 maximumInteger() const;
    void setIntegerRange(qint64 min, qint64 max);

    inline double minimumDouble() const;
    inline double maximumDouble() const;
    void setDoubleRange(double min, double max);

    inline const QRegExp &stringRegExp() const;
    void setStringRegExp(const QRegExp &regExp);

    inline const QString &dateTimeFormat() const;
    void setDateTimeFormat(const QString &format);

    inline const QDateTime &minimumDateTime() const;
    inline const QDateTime &maximumDateTime() const;
    void setDateTimeRange(const QDateTime &minTime, const QDateTime &maxTime);

    bool validate(QString *reason = 0) const;

    bool toBool() const;
    int toInt() const;
    double toDouble() const;
    QString toString() const;
    QDateTime toDateTime() const;
    QUrl toUrl() const;

private:
    void validateBool() const;
    void validateInteger() const;
    void validateDouble() const;
    void validateString() const;
    void validateDateTime() const;
    void validateUrl() const;

private:
    bool m_isFound;
    Type m_type;
    QString m_key;
    QVariant m_value;
    qint64 m_intMin;
    qint64 m_intMax;
    double m_doubleMin;
    double m_doubleMax;
    QRegExp m_stringRegExp;
    QString m_dateTimeFormat;
    QDateTime m_dateTimeMin;
    QDateTime m_dateTimeMax;
};

bool AppArgument::isFound() const
{
    return m_isFound;
}

AppArgument::Type AppArgument::type() const
{
    return m_type;
}

const QString &AppArgument::key() const
{
    return m_key;
}

const QVariant &AppArgument::value() const
{
    return m_value;
}

qint64 AppArgument::minimumInteger() const
{
    return m_intMin;
}

qint64 AppArgument::maximumInteger() const
{
    return m_intMax;
}

double AppArgument::minimumDouble() const
{
    return m_doubleMin;
}

double AppArgument::maximumDouble() const
{
    return m_doubleMax;
}

const QRegExp &AppArgument::stringRegExp() const
{
    return m_stringRegExp;
}

const QString &AppArgument::dateTimeFormat() const
{
    return m_dateTimeFormat;
}

const QDateTime &AppArgument::minimumDateTime() const
{
    return m_dateTimeMin;
}

const QDateTime &AppArgument::maximumDateTime() const
{
    return m_dateTimeMax;
}


#endif // APPARGUMENT_H
