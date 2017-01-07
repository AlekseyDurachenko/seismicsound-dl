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
#include "xmlutils.h"
#include <QStringList>


QString value_from_xml_path(const QDomNode &root, const QString &path)
{
    QStringList nodeNamePath = path.split("/");

    QString nodeName = nodeNamePath.takeFirst();
    QDomNode node = root.firstChild();
    while (!node.isNull()) {
        if (node.nodeName() == nodeName) {
            if (nodeNamePath.count()) {
                nodeName = nodeNamePath.takeFirst();
                node = node.firstChild();
                continue;
            }
            else {
                return node.toElement().text();
            }
        }

        node = node.nextSibling();
    }

    return QString();
}
