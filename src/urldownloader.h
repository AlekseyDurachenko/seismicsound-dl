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
#ifndef URLDOWNLOADER_H
#define URLDOWNLOADER_H


#include "consts.h"
#include <QUrl>
#include <QNetworkAccessManager>


class UrlDownloader : public QObject
{
    Q_OBJECT
public:
    enum Error {
        NoError = 0x00,
        NoData  = 0x01,
        BadUrl  = 0x0F,
        IOError = 0x10,
        Other   = 0xFF
    };

public:
    explicit UrlDownloader(QObject *parent = 0);
    Error download(const QUrl &url, QIODevice *device, QString *reason = 0);

private slots:
    void reply_finished();
    void reply_downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    QNetworkAccessManager *m_nam;
    QUrl m_url;
    QIODevice *m_device;
    QString m_errorStr;
    Error m_errorCode;
    bool m_hasError;
};


#endif // URLDOWNLOADER_H
