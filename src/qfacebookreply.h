/*
 * Copyright (C) 2011 Ragner Magalhaes <ragner.magalhaes@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef QFACEBOOKREPLY_H
#define QFACEBOOKREPLY_H

#include "qfacebook_global.h"
#include "graphapi.h"

#include <QObject>
#include <QNetworkReply>
#include <QSslError>

class QFACEBOOKSHARED_EXPORT QFacebookReply : public QObject
{
    Q_OBJECT
protected:
    explicit QFacebookReply(QNetworkReply *reply, QObject *parent = 0);

public:
    QVariant data();
    QNetworkReply::NetworkError error() const;

signals:
    void finished();
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);

private slots:
    void onParseData();
    void doParse();
    void onError(QNetworkReply::NetworkError code);
    void onSslErrors(const QList<QSslError> &errors);

private:
    QNetworkReply *m_reply;
    QVariant m_data;

friend class GraphAPI;
};

#endif // QFACEBOOKREPLY_H
