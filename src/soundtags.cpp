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
#include "soundtags.h"
#include "consts.h"
#include "version.h"


SoundTags::SoundTags()
{
}

void SoundTags::setTitle(const QString &title)
{
    m_title = title;
}

void SoundTags::setCopyright(const QString &copyright)
{
    m_copyright = copyright;
}

void SoundTags::setSoftware(const QString &software)
{
    m_software = software;
}

void SoundTags::setArtist(const QString &artist)
{
    m_artist = artist;
}

void SoundTags::setComment(const QString &comment)
{
    m_comment = comment;
}

void SoundTags::setDate(const QString &date)
{
    m_date = date;
}

void SoundTags::setGenre(const QString &genre)
{
    m_genre = genre;
}

SoundTags SoundTags::fromDataSelectQuery(const DataSelectQuery &query)
{
    SoundTags tags;
    tags.setComment(query.buildQueryUrl().toString());
    tags.setGenre(DefaultSoundGenre);
    tags.setArtist(DefaultNoneEventIdName);
    tags.setTitle(QString("%1.%2.%3.%4 (%5 - %6)")
                  .arg(query.network())
                  .arg(query.station())
                  .arg(query.location())
                  .arg(query.channel())
                  .arg(query.startTime().toString(DisplayDateTimeFormat))
                  .arg(query.endTime().toString(DisplayDateTimeFormat)));
    if (appBuildDate()) {
        tags.setSoftware(QString("%1 Ver %2 (%3)")
                         .arg(appName())
                         .arg(appVersion())
                         .arg(appBuildDate()));
    }
    else {
        tags.setSoftware(QString("%1 Ver %2s")
                         .arg(appName())
                         .arg(appVersion()));
    }

    return tags;
}


SoundTags SoundTags::fromDataSelectQuery(const Event &event, const DataSelectQuery &query)
{
    SoundTags tags = SoundTags::fromDataSelectQuery(query);
    tags.setArtist(QString("ID_%1").arg(event.id()));
    return tags;
}
