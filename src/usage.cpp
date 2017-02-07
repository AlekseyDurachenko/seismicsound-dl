// Copyright 2017, Durachenko Aleksey V. <durachenko@gs.sbras.ru>
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
#include "usage.h"
#include "version.h"
#include <QFile>
#include <QLocale>
#include <QStringList>
#include <stdio.h>


void show_usage()
{
    const QStringList usageFilePaths
        = QStringList()
          << QString(":/usage/%1.txt").arg(QLocale::system().name())
          << QString(":/usage/%1.txt").arg(QLocale::system().name().left(2))
          << QString(":/usage/en.txt");

    QByteArray usageText;
    foreach (const QString &usageFilePath, usageFilePaths) {
        QFile file(usageFilePath);
        if (file.open(QIODevice::ReadOnly)) {
            usageText = file.readAll();
            break;
        }
    }


    if (appBuildDate()) {
        printf("%s Ver %s (%s) %s\n", appName(), appVersion(), appBuildDate(), appShortName());
    }
    else {
        printf("%s Ver %s %s\n", appName(), appVersion(), appShortName());
    }

    puts(usageText.data());
}


void show_usage_and_exit(int status)
{
    show_usage();
    exit(status);
}
