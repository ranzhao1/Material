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
    m_reply(0)
{
    QString token = QCoreApplication::arguments().at(1);

    qfaceBook = new QFacebook(token, this);
}

void GetConnection::load()
{
    QString id = QCoreApplication::arguments().at(2);
    QString connType = QCoreApplication::arguments().at(3);

    m_reply = qfaceBook->getConnections(id, connType);
    if (m_reply)
        connect(m_reply, SIGNAL(finished()), this, SLOT(onDataReady()));
}

void GetConnection::onDataReady()
{
    if (m_reply->error() != QNetworkReply::NoError) {
        qDebug() << "Simple get fail!";
        m_reply->deleteLater();
        m_reply = 0;
        QCoreApplication::instance()->quit();
        return;
    }

    QVariant parsedData = m_reply->data();

    qDebug() << "######### Parsed data:";
    qDebug() << parsedData;

    QCoreApplication::instance()->quit();
}