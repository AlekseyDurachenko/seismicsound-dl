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
#include "info.h"
#include "apparguments.h"
#include "version.h"
#include "appargumentconsts.h"
#include <iostream>


void fail_print(const QString &msg)
{
    std::cout << "FAIL: " << msg.toStdString() << std::endl;
}

void info_print(const QString &msg)
{
    std::cout << "INFO: " << msg.toStdString() << std::endl;
}


void info_print_error_message(const QString &errstr)
{
    std::cout << appName() << ": " << errstr.toStdString() << std::endl;
    std::cout << QObject::tr("Try \'%1 %2\' for more information.").arg(appName()).arg(ArgHelp).toStdString() << std::endl;
}
