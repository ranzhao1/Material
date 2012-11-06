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

#ifndef QFACEBOOK_H
#define QFACEBOOK_H

#include "qfacebook_global.h"
#include "qfacebookreply.h"
#include "graphapi.h"

class QFACEBOOKSHARED_EXPORT QFacebook : public QObject
{
public:
    QFacebook(QString accessToken, QObject *parent = 0);

    QFacebookReply *getObject(QString id);
    QFacebookReply *getConnections(QString id, QString connectionName);
    QFacebookReply *putObject(QString id, QString connection,
                       QByteArray data = QByteArray());
    QFacebookReply *deleteObject(QString id);

    QNetworkReply *get(QUrl url);
    QNetworkReply *put(QUrl url, QByteArray data);
    QNetworkReply *del(QUrl url);

private:
    GraphAPI *m_graphAPI;
};

#endif // QFACEBOOK_H
