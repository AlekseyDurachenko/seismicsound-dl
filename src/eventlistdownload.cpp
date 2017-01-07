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
#include "eventlistdownload.h"
#include "urldownloader.h"
#include "info.h"
#include "debug.h"
#include <QBuffer>
#include "urldownloader.h"
#include "xmlutils.h"
#include "apparguments.h"
#include <QBuffer>
#include <QByteArray>
#include <QDomDocument>
#include <QStringList>
#include <QDebug>

// --------------------------------------------------------------------------
// The QuakeML example:
// --------------------------------------------------------------------------
//<event xmlns:iris="http://service.iris.edu/fdsnws/event/1/" publicID="smi:service.iris.edu/fdsnws/event/1/query?eventid=4218658">
//  <type>earthquake</type>
//  <description iris:FEcode="663">
//    <type>Flinn-Engdahl region</type>
//    <text>SEA OF OKHOTSK</text>
//  </description>
//  <preferredMagnitudeID>
//    smi:service.iris.edu/fdsnws/event/1/query?magnitudeid=16614615
//  </preferredMagnitudeID>
//  <preferredOriginID>
//    smi:service.iris.edu/fdsnws/event/1/query?originid=9910843
//  </preferredOriginID>
//  <origin publicID="smi:service.iris.edu/fdsnws/event/1/query?originid=9910843" iris:contributor="NEIC PDE-M" iris:catalog="NEIC PDE">
//    <time>
//      <value>2013-05-24T05:44:48.9800</value>
//    </time>
//    <creationInfo>
//      <author>NEIC</author>
//    </creationInfo>
//    <latitude>
//      <value>54.892</value>
//    </latitude>
//    <longitude>
//      <value>153.221</value>
//    </longitude>
//    <depth>
//      <value>598100.0</value>
//    </depth>
//  </origin>
//  <magnitude publicID="smi:service.iris.edu/fdsnws/event/1/query?magnitudeid=16614615">
//    <originID>
//      smi:service.iris.edu/fdsnws/event/1/query?originid=9910843
//    </originID>
//    <type>MW</type>
//    <mag>
//      <value>8.4</value>
//    </mag>
//    <creationInfo>
//      <author>UCMT</author>
//    </creationInfo>
//  </magnitude>
//</event>
// --------------------------------------------------------------------------

static bool parse_event_xml(const QByteArray &eventXml,
                            QList<Event> &events,
                            QString *reason)
{
    try {
        QDomDocument doc;
        if (!doc.setContent(eventXml)) {
            throw QObject::tr("invalid QuakeML format");
        }

        // we cannot parse the unknow xml format
        const QDomElement rootElem = doc.documentElement();
        if (rootElem.nodeName() != "q:quakeml") {
            throw QObject::tr("invalid QuakeML format");
        }

        // we cannot parse the unknow xml format
        const QDomNode eventParameters = rootElem.firstChild();
        if (eventParameters.nodeName() != "eventParameters") {
            throw QObject::tr("invalid QuakeML format");
        }

        QDomNode eventNode = eventParameters.firstChild();
        while (!eventNode.isNull()) {
            if (eventNode.nodeName() == "event") {
                Event event;
                event.setId(eventNode.toElement().attribute("publicID").split("?eventid=").last());
                event.setDescription(value_from_xml_path(eventNode, "description/text"));
                QDateTime dateTime = QDateTime::fromString(value_from_xml_path(eventNode, "origin/time").split(".").first(), "yyyy-MM-ddTHH:mm:ss");
                dateTime.setTimeSpec(Qt::UTC);
                event.setTime(dateTime);
                event.setLatitude(value_from_xml_path(eventNode, "origin/latitude/value").toDouble());
                event.setLongitude(value_from_xml_path(eventNode, "origin/longitude/value").toDouble());
                event.setDepth(value_from_xml_path(eventNode, "origin/depth/value").toDouble());
                event.setMagnitudeType(value_from_xml_path(eventNode, "magnitude/type"));
                event.setMagnitudeValue(value_from_xml_path(eventNode, "magnitude/mag/value").toDouble());
                events.append(event);
            }

            eventNode = eventNode.nextSibling();
        }

        return true;
    }
    catch (const QString &error) {
        if (reason) {
            *reason = error;
        }
    }

    return false;
}


QList<Event> event_list_download(const AppArguments &arguments, const EventQuery &query)
{
    info_print(QObject::tr("Downloading the event list..."));
    debug_print(arguments, query);

    // temporary buffers for QuakeML
    QByteArray bytes;
    QBuffer buffer(&bytes);
    if (!buffer.open(QIODevice::WriteOnly)) {
        fail_print(QObject::tr("can't open temporary buffer for write \'%1\'").arg(buffer.errorString()));
        exit(EXIT_FAILURE);
    }

    // download the QuakeML
    QString errstr;
    UrlDownloader urlDownloader;
    if (urlDownloader.download(query.buildQueryUrl(), &buffer, &errstr) != UrlDownloader::NoError) {
        fail_print(errstr);
        exit(EXIT_FAILURE);
    }

    // parse the QuakeML to event list
    QList<Event> events;
    if (!parse_event_xml(bytes, events, &errstr)) {
        fail_print(errstr);
        exit(EXIT_FAILURE);
    }

    return events;
}
