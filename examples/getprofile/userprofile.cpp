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

#include "userprofile.h"

UserProfile::UserProfile(QObject *parent) :
        QObject(parent),
        qfaceBook(0),
        m_isLoaded(false)
{

}

int UserProfile::load()
{
    if (!qfaceBook)
        return 1;
    m_isLoaded = false;
    m_name = "";
    m_picture = QImage();

    QFacebookReply *reply;
    QNetworkReply *picReply;

    reply = qfaceBook->getObject(m_id);
    if (reply)
        connect(reply, SIGNAL(finished()), this, SLOT(onDataReady()));

    // Requesting the picture using simple get
    picReply = qfaceBook->get(QUrl("http://graph.facebook.com/" + m_id + "/picture"));
    if (picReply)
        connect(picReply, SIGNAL(finished()), this, SLOT(onPictureReady()));
    return 0;
}

void UserProfile::setToken(QString token)
{
    if (token != m_token) {
        if (qfaceBook)
            qfaceBook->deleteLater();

        qfaceBook = new QFacebook(token, this);
        m_token = token;
    }
}

void UserProfile::setId(QString id)
{
    m_id = id;
}

QString UserProfile::name()
{
    return m_name;
}

QPixmap UserProfile::picture()
{
    return QPixmap::fromImage(m_picture);
}

void UserProfile::onDataReady()
{
    QFacebookReply *reply = qobject_cast<QFacebookReply*>(sender());
    QVariant jsonData;
    if (!reply) {
        qDebug() << "Cast to facebook reply fail!";
        goto onfinished;
    }
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "JSON get fail!";
        reply->deleteLater();
        reply = 0;

        goto onfinished;
    }

    jsonData = reply->data();
    qDebug() << "######### Parsed data:";
    qDebug() << jsonData;

    m_name = jsonData.toMap().value("name").toString();

    onfinished:
    if (m_isLoaded)
        emit finished();
    m_isLoaded = true;
}

void UserProfile::onPictureReady()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    QByteArray data;
    QUrl redir;
    if (!reply) {
        qDebug() << "Cast to qnetwork reply fail!";
        goto onfinished;
    }
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Picture get fail!";
        reply->deleteLater();
        reply = 0;

        goto onfinished;
    }

    redir = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    // Facebook is redirecting the picture request
    if(!redir.isEmpty()) {
        qDebug() << "Redirecting picture request to " + redir.toString();
        reply = qfaceBook->get(redir);
        if (reply)
            connect(reply, SIGNAL(finished()), this, SLOT(onPictureReady()));
        // not finished yet!
        return;
    }

    qDebug() << "######### Parsed picture:";
    data = reply->readAll();
    m_picture = QImage::fromData(data, "JPEG");

    onfinished:
    if (m_isLoaded)
        emit finished();
    m_isLoaded = true;
}
