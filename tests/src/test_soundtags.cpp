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
#include "test_soundtags.h"
#include "soundtags.h"


Test_SoundTags::Test_SoundTags(QObject *parent)
    : QObject(parent)
{
}

void Test_SoundTags::test_setGet()
{
    SoundTags soundTags;
    QCOMPARE(soundTags.title(), QString());
    QCOMPARE(soundTags.copyright(), QString());
    QCOMPARE(soundTags.software(), QString());
    QCOMPARE(soundTags.artist(), QString());
    QCOMPARE(soundTags.comment(), QString());
    QCOMPARE(soundTags.date(), QString());
    QCOMPARE(soundTags.genre(), QString());

    soundTags.setTitle("1");
    soundTags.setCopyright("2");
    soundTags.setSoftware("3");
    soundTags.setArtist("4");
    soundTags.setComment("5");
    soundTags.setDate("6");
    soundTags.setGenre("10");
    QCOMPARE(soundTags.title(), QString("1"));
    QCOMPARE(soundTags.copyright(), QString("2"));
    QCOMPARE(soundTags.software(), QString("3"));
    QCOMPARE(soundTags.artist(), QString("4"));
    QCOMPARE(soundTags.comment(), QString("5"));
    QCOMPARE(soundTags.date(), QString("6"));
    QCOMPARE(soundTags.genre(), QString("10"));
}
