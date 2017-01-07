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
#include "urldownloader.h"
#include <QEventLoop>
#include <QNetworkReply>


UrlDownloader::UrlDownloader(QObject *parent)
    : QObject(parent)
{
    m_nam = new QNetworkAccessManager(this);
    m_device = nullptr;
    m_hasError = false;
    m_errorCode = Error::NoError;
}


UrlDownloader::Error UrlDownloader::download(const QUrl &url, QIODevice *device, QString *reason)
{
    Q_ASSERT(device);

    try {
        m_url = url;
        m_device = device;

        m_hasError = false;
        m_errorStr.clear();
        m_errorCode = Error::NoError;

        if (m_url.isEmpty() || !m_url.isValid()) {
            m_errorCode = Error::BadUrl;
            throw tr("url is invalid or not specified");
        }

        QNetworkReply *reply = m_nam->get(QNetworkRequest(m_url));
        connect(reply, SIGNAL(finished()), this, SLOT(reply_finished()));
        connect(reply, SIGNAL(finished()), this, SLOT(deleteLater()));
        connect(reply, SIGNAL(downloadProgress(qint64, qint64)),
                this, SLOT(reply_downloadProgress(qint64, qint64)));

        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        if (loop.exec()) {
            m_errorCode = Error::Other;
            throw tr("oops! something wrong with event loop!");
        }

        if (m_hasError) {
            throw m_errorStr;
        }

        return Error::NoError;
    }
    catch (const QString &errorString) {
        if (reason) {
            *reason = errorString;
        }
    }

    return m_errorCode;
}

void UrlDownloader::reply_finished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!m_hasError) {
        if (reply->error() != QNetworkReply::NoError) {
            m_hasError = true;
            m_errorStr = reply->errorString();
            if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 204
                    || reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 404) {
                m_errorCode = Error::NoData;
            }
            else {
                m_errorCode = Error::Other;
            }
            return;
        }

        const QByteArray bytes = reply->readAll();
        if (m_device->write(bytes) != bytes.size()) {
            m_hasError = true;
            m_errorStr = m_device->errorString();
            m_errorCode = Error::IOError;
        }
    }
}

void UrlDownloader::reply_downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    Q_UNUSED(bytesReceived);
    Q_UNUSED(bytesTotal);

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!m_hasError) {
        const QByteArray bytes = reply->readAll();
        if (m_device->write(bytes) != bytes.size()) {
            m_hasError = true;
            m_errorStr = m_device->errorString();
            m_errorCode = Error::IOError;
            reply->abort();
        }
    }
}
