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

#include <QtCore/QCoreApplication>
#include <QStringList>
#include <QString>
#include <QDebug>

#include "getconnection.h"

GetConnection::GetConnection(QObject *parent) :
    QObject(parent),
    qfaceBook(0),
    m_reply(0)
{

}

int GetConnection::load()
{
    if (!qfaceBook)
        return 1;

    m_reply = qfaceBook->getConnections(m_id, "friends");
    if (m_reply)
        connect(m_reply, SIGNAL(finished()), this, SLOT(onDataReady()));
    return 0;
}

void GetConnection::setToken(QString token)
{
    if (token != m_token) {
        if (qfaceBook)
            qfaceBook->deleteLater();

        qfaceBook = new QFacebook(token, this);
        m_token = token;
    }
}

void GetConnection::setId(QString id)
{
    m_id = id;
}

void GetConnection::onDataReady()
{
    QStringList friends;

    if (m_reply->error() != QNetworkReply::NoError) {
        qDebug() << "Simple get fail!";
        m_reply->deleteLater();
        m_reply = 0;

        // Could emit here some error signal!
        emit finished(friends);
        return;
    }

    QVariant jsonData = m_reply->data();
    qDebug() << "######### Parsed data:";
    qDebug() << jsonData;

    QVariantList listData;

    // Parse for friends' list
    listData = jsonData.toMap().value("data").toList();
    foreach(jsonData, listData) {
        friends.append(jsonData.toMap().value("name").toString());
    }

    emit finished(friends);
}
