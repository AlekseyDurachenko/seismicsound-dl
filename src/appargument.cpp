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
#include "appargument.h"
#include <numeric>


AppArgument::AppArgument(Type type)
{
    m_isFound = false;
    m_type = type;
    m_intMin = std::numeric_limits<qint64>::min();
    m_intMax = std::numeric_limits<qint64>::max();
    m_doubleMin = std::numeric_limits<double>::min();
    m_doubleMax = std::numeric_limits<double>::max();
}

void AppArgument::setFound(bool found)
{
    m_isFound = found;
}

void AppArgument::setType(AppArgument::Type type)
{
    m_type = type;
}

void AppArgument::setKey(const QString &key)
{
    m_key = key;
}

void AppArgument::setValue(const QVariant &value)
{
    m_value = value;
}

void AppArgument::setIntegerRange(qint64 min, qint64 max)
{
    if (min < max) {
        m_intMin = min;
        m_intMax = max;
    }
    else {
        m_intMin = max;
        m_intMax = min;
    }
}

void AppArgument::setDoubleRange(double min, double max)
{
    if (min < max) {
        m_doubleMin = min;
        m_doubleMax = max;
    }
    else {
        m_doubleMin = max;
        m_doubleMax = min;
    }
}

void AppArgument::setStringRegExp(const QRegExp &regExp)
{
    m_stringRegExp = regExp;
}

void AppArgument::setDateTimeFormat(const QString &format)
{
    m_dateTimeFormat = format;
}

void AppArgument::setDateTimeRange(const QDateTime &minTime, const QDateTime &maxTime)
{
    if (minTime < maxTime) {
        m_dateTimeMin = minTime;
        m_dateTimeMax = maxTime;
    }
    else {
        m_dateTimeMin = maxTime;
        m_dateTimeMax = minTime;
    }
}

bool AppArgument::validate(QString *reason) const
{
    try {
        if (isFound()) {
            switch (type()) {
            case Bool:
                validateBool();
                break;
            case Integer:
                validateInteger();
                break;
            case Double:
                validateDouble();
                break;
            case String:
                validateString();
                break;
            case DateTime:
                validateDateTime();
                break;
            case Url:
                validateUrl();
                break;
            }
        }

        return true;
    }
    catch (const QString &errorString) {
        if (reason) {
            *reason = errorString;
        }
    }

    return false;
}

bool AppArgument::toBool() const
{
    Q_ASSERT(m_type == AppArgument::Bool);
    return m_isFound;
}

int AppArgument::toInt() const
{
    Q_ASSERT(m_type == AppArgument::Integer);
    Q_ASSERT(m_isFound);
    return m_value.toInt();
}

double AppArgument::toDouble() const
{
    Q_ASSERT(m_type == AppArgument::Double);
    Q_ASSERT(m_isFound);
    return m_value.toDouble();
}

QString AppArgument::toString() const
{
    Q_ASSERT(m_type == AppArgument::String);
    Q_ASSERT(m_isFound);
    return m_value.toString();
}

QDateTime AppArgument::toDateTime() const
{
    Q_ASSERT(m_type == AppArgument::DateTime);
    Q_ASSERT(m_isFound);

    QDateTime dateTime = QDateTime::fromString(m_value.toString(), m_dateTimeFormat);
    dateTime.setTimeSpec(Qt::UTC);
    return dateTime;
}

QUrl AppArgument::toUrl() const
{
    Q_ASSERT(m_type == AppArgument::Url);
    Q_ASSERT(m_isFound);
    return m_value.toUrl();
}

void AppArgument::validateBool() const
{
}

void AppArgument::validateInteger() const
{
    bool ok;
    const qint64 val = value().toLongLong(&ok);
    if (!ok) {
        throw QObject::tr("\'%1\' must be an integer number").arg(key());
    }

    if (val < minimumInteger() || val > maximumInteger()) {
        throw QObject::tr("\'%1\' out of range").arg(key());
    }
}

void AppArgument::validateDouble() const
{
    bool ok;
    const double val = value().toDouble(&ok);
    if (!ok) {
        throw QObject::tr("\'%1\' must be a real number").arg(key());
    }

    if (val < minimumDouble() || val > maximumDouble()) {
        throw QObject::tr("\'%1\' out of range").arg(key());
    }
}

void AppArgument::validateString() const
{
    if (!stringRegExp().isEmpty()) {
        const QString v = value().toString();
        if (!stringRegExp().exactMatch(v)) {
            throw QObject::tr("\'%1\' invalid string format").arg(key());
        }
    }
}

void AppArgument::validateDateTime() const
{
    const QString str = value().toString();
    QDateTime dateTime = dateTimeFormat().isEmpty()
                         ? QDateTime::fromString(str)
                         : QDateTime::fromString(str, dateTimeFormat());
    dateTime.setTimeSpec(Qt::UTC);

    if (!dateTime.isValid()) {
        throw QObject::tr("\'%1\' invalid time format").arg(key());
    }

    if ((minimumDateTime().isValid() && (dateTime < minimumDateTime()))
            || (maximumDateTime().isValid() && (dateTime > maximumDateTime()))) {
        throw QObject::tr("\'%1\' out of range").arg(key());
    }
}

void AppArgument::validateUrl() const
{
    const QUrl url = value().toUrl();
    if (!url.isValid()) {
        throw QObject::tr("\'%1\' invalid url format").arg(key());
    }
}
