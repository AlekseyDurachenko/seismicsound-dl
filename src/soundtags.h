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
#ifndef SOUNDTAGS_H
#define SOUNDTAGS_H


#include "dataselectquery.h"
#include "event.h"
#include <QString>


class SoundTags
{
public:
    SoundTags();

    inline const QString &title() const;
    void setTitle(const QString &title);

    inline const QString &copyright() const;
    void setCopyright(const QString &copyright);

    inline const QString &software() const;
    void setSoftware(const QString &software);

    inline const QString &artist() const;
    void setArtist(const QString &artist);

    inline const QString &comment() const;
    void setComment(const QString &comment);

    inline const QString &date() const;
    void setDate(const QString &date);

    inline const QString &genre() const;
    void setGenre(const QString &genre);

    inline bool operator == (const SoundTags &other) const;
    inline bool operator != (const SoundTags &other) const;

public:
    static SoundTags fromDataSelectQuery(const DataSelectQuery &query);
    static SoundTags fromDataSelectQuery(const Event &event, const DataSelectQuery &query);
private:
    QString m_title;
    QString m_copyright;
    QString m_software;
    QString m_artist;
    QString m_comment;
    QString m_date;
    QString m_genre;
};

const QString &SoundTags::title() const
{
    return m_title;
}

const QString &SoundTags::copyright() const
{
    return m_copyright;
}

const QString &SoundTags::software() const
{
    return m_software;
}

const QString &SoundTags::artist() const
{
    return m_artist;
}

const QString &SoundTags::comment() const
{
    return m_comment;
}

const QString &SoundTags::date() const
{
    return m_date;
}

const QString &SoundTags::genre() const
{
    return m_genre;
}

bool SoundTags::operator ==(const SoundTags &other) const
{
    return m_title == other.m_title
           && m_copyright == other.m_copyright
           && m_software == other.m_software
           && m_artist == other.m_artist
           && m_comment == other.m_comment
           && m_date == other.m_date
           && m_genre == other.m_genre;
}

bool SoundTags::operator !=(const SoundTags &other) const
{
    return !operator==(other);
}


#endif // SOUND_H
