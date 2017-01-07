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
#include "stationlistdownload.h"
#include "urldownloader.h"
#include "xmlutils.h"
#include "info.h"
#include "debug.h"
#include <QBuffer>


// --------------------------------------------------------------------------
// The FDSNStationXML example:
// --------------------------------------------------------------------------
//<FDSNStationXML xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns="http://www.fdsn.org/xml/station/1" schemaVersion="1.0" xsi:schemaLocation="http://www.f
//  <Source>IRIS-DMC</Source>
//  <Sender>IRIS-DMC</Sender>
//  <Module>IRIS WEB SERVICE: fdsnws-station | version: 1.0.9</Module>
//  <ModuleURI>
//    http://service.iris.edu/fdsnws/station/1/query?starttime=2014-01-01T16:03:30&endtime=2014-01-01T16:03:30&level=channel&matchtimeseries=true&format=xml&channel=?
//  </ModuleURI>
//  <Created>2014-01-12T05:00:09</Created>
//  <Network code="G" startDate="1982-01-01T00:00:00" endDate="2500-12-12T23:59:59" restrictedStatus="open">
//  <Description>GEOSCOPE</Description>
//  <TotalNumberStations>55</TotalNumberStations>
//  <SelectedNumberStations>1</SelectedNumberStations>
//  <Station code="SANVU" startDate="2011-11-01T00:00:00" endDate="2599-12-31T23:59:59" restrictedStatus="open">
//    <Comment>
//      <Value>Station is down.</Value>
//      <BeginEffectiveTime>2012-01-22T11:00:00</BeginEffectiveTime>
//      <EndEffectiveTime>2012-01-27T01:00:00</EndEffectiveTime>
//    </Comment>
//    <Latitude>-15.447148</Latitude>
//    <Longitude>167.203231</Longitude>
//    <Elevation>56.0</Elevation>
//    <Site>
//      <Name>Espiritu Santo, Vanuatu</Name>
//    </Site>
//    <CreationDate>2011-11-01T00:00:00</CreationDate>
//    <TotalNumberChannels>17</TotalNumberChannels>
//    <SelectedNumberChannels>12</SelectedNumberChannels>
//    <Channel locationCode="00" startDate="2011-11-01T00:00:00" restrictedStatus="open" endDate="2599-12-31T23:59:59" code="BHE">
//    ...
//    </Channel>
//  </Station>
//</FDSNStationXML>
// --------------------------------------------------------------------------


static Trace node_to_trace(const QDomNode &networkNode,
                           const QDomNode &stationNode,
                           const QDomNode &channelNode)
{
    Trace trace;
    trace.setNetwork(networkNode.toElement().attribute("code"));
    trace.setStation(stationNode.toElement().attribute("code"));
    trace.setSiteName(value_from_xml_path(stationNode, "Site/Name"));
    trace.setLatitude(value_from_xml_path(stationNode, "Latitude").toDouble());
    trace.setLongitude(value_from_xml_path(stationNode, "Longitude").toDouble());
    trace.setElevation(value_from_xml_path(stationNode, "Elevation").toDouble());
    trace.setChannel(channelNode.toElement().attribute("code"));
    trace.setLocation(channelNode.toElement().attribute("locationCode"));
    trace.setStartTime(QDateTime::fromString(channelNode.toElement().attribute("startDate"), "yyyy-MM-ddTHH:mm:ss"));
    trace.setEndTime(QDateTime::fromString(channelNode.toElement().attribute("endDate"), "yyyy-MM-ddTHH:mm:ss"));
    trace.setDepth(value_from_xml_path(channelNode, "Depth").toDouble());
    return trace;
}


static bool parse_xml(const QByteArray &stationXml, QList<Trace> &traces, QString *reason)
{
    try {
        QDomDocument doc("FDSNStationXML");
        if (!doc.setContent(stationXml)) {
            throw QObject::tr("invalid FDSNStationXML format");
        }

        // we cannot parse the unknow xml format
        const QDomElement rootElem = doc.documentElement();
        if (rootElem.nodeName() != "FDSNStationXML") {
            throw QObject::tr("invalid FDSNStationXML format");
        }

        QDomNode networkNode = rootElem.firstChild();
        while (!networkNode.isNull()) {
            if (networkNode.nodeName() == "Network") {
                QDomNode stationNode = networkNode.firstChild();
                while (!stationNode.isNull()) {
                    if (stationNode.nodeName() == "Station") {
                        QDomNode channelNode = stationNode.firstChild();
                        while (!channelNode.isNull()) {
                            if (channelNode.nodeName() == "Channel") {
                                traces.append(node_to_trace(networkNode,
                                                            stationNode,
                                                            channelNode));
                            }

                            channelNode = channelNode.nextSibling();
                        }
                    }

                    stationNode = stationNode.nextSibling();
                }
            }

            networkNode = networkNode.nextSibling();
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



QList<Trace> station_list_download(const AppArguments &arguments, const StationQuery &query)
{
    info_print(QObject::tr("Downloading the station list..."));
    debug_print(arguments, query);

    // temporary buffers for FDSNStationXML
    QByteArray bytes;
    QBuffer buffer(&bytes);
    if (!buffer.open(QIODevice::WriteOnly)) {
        fail_print(QObject::tr("can't open temporary buffer for write \'%1\'").arg(buffer.errorString()));
        exit(EXIT_FAILURE);
    }

    // download the FDSNStationXML
    QString errstr;
    UrlDownloader urlDownloader;
    if (urlDownloader.download(query.buildQueryUrl(), &buffer, &errstr) != UrlDownloader::NoError) {
        fail_print(errstr);
        exit(EXIT_FAILURE);
    }

    // parse the FDSNStationXML to trace list
    QList<Trace> traces;
    if (!parse_xml(bytes, traces, &errstr)) {
        fail_print(errstr);
        exit(EXIT_FAILURE);
    }

    return traces;
}
