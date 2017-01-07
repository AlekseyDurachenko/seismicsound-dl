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
#ifndef TEST_APPARGUMENT_H
#define TEST_APPARGUMENT_H


#include <QObject>
#include <QtTest/QtTest>


class Test_AppArgument : public QObject
{
    Q_OBJECT
public:
    explicit Test_AppArgument(QObject *parent = 0);

private slots:
    void test_defaultConstructor();
    void test_setGet();
    void test_validate_bool();
    void test_validate_integer();
    void test_validate_double();
    void test_validate_string();
    void test_validate_dateTime();
    void test_validate_url();
    void test_argument_to_types();
};


#endif // TEST_APPARGUMENT_H
