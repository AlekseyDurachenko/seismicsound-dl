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
#ifndef TEST_SOUNDTAGS_H
#define TEST_SOUNDTAGS_H


#include <QObject>
#include <QtTest/QtTest>


class Test_SoundTags : public QObject
{
    Q_OBJECT
public:
    explicit Test_SoundTags(QObject *parent = 0);

private slots:
    void test_setGet();
};


#endif // TEST_SOUNDTAGS_H
