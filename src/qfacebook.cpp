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

#include "qfacebook.h"

QFacebook::QFacebook(QString accessToken, QObject *parent)
    : QObject(parent),
    m_graphAPI(0)
{
    m_graphAPI = new GraphAPI(accessToken, this);
}

QFacebookReply *QFacebook::getObject(QString id)
{
    return m_graphAPI->getObject(id);
}

QFacebookReply *QFacebook::getConnections(QString id, QString connectionName)
{
    return m_graphAPI->getConnections(id, connectionName);
}

QFacebookReply *QFacebook::putObject(QString id, QString connection, QByteArray data)
{
    return m_graphAPI->putObject(id, connection, data);
}

QFacebookReply *QFacebook::deleteObject(QString id)
{
    return m_graphAPI->deleteObject(id);
}

QNetworkReply *QFacebook::get(QUrl url)
{
    return m_graphAPI->get(url);
}

QNetworkReply *QFacebook::put(QUrl url, QByteArray data)
{
    return m_graphAPI->put(url, data);
}

QNetworkReply *QFacebook::del(QUrl url)
{
    return m_graphAPI->del(url);
}
