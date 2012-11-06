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

#include <QDebug>

#include "qfacebookreply.h"

#include "parser.h"

QFacebookReply::QFacebookReply(QNetworkReply *reply, QObject *parent)
    : QObject(parent),
    m_reply(reply),
    m_data(QVariant())
{
    if (m_reply) {
        connect(m_reply, SIGNAL(uploadProgress(qint64,qint64)), this, SIGNAL(uploadProgress(qint64,qint64)));
        connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
        connect(m_reply, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(onSslErrors(QList<QSslError>)));
        connect(m_reply, SIGNAL(finished()), this, SLOT(onParseData()));
    }
}

QVariant QFacebookReply::data()
{
    return m_data;
}

QNetworkReply::NetworkError QFacebookReply::error() const
{
    if (m_reply)
        return m_reply->error();

    return QNetworkReply::NoError;
}

void QFacebookReply::onParseData()
{
    if (m_reply->error() != QNetworkReply::NoError) {
        qDebug() << "Request fail " << m_reply->errorString();
    } else {
        qDebug() << "Request success.";
        //TODO: Check about put and delete requests
        // before do the parse.
        doParse();
    }

    emit finished();
}

void QFacebookReply::doParse()
{
    bool ok;
    QJson::Parser parser;
    QByteArray replyResult = m_reply->readAll();

    QVariant parsedResult = parser.parse(replyResult, &ok);

    if (!ok) {
        qWarning() << "Error while parsing network reply: " << replyResult;
        return;
    }

    m_data = parsedResult;
}
void QFacebookReply::onError(QNetworkReply::NetworkError code)
{
    qDebug() << "Error: " << code;
}

void QFacebookReply::onSslErrors(const QList<QSslError> &errors)
{
    qDebug() << "Ssl errors:";
    foreach(QSslError error, errors) {
        qDebug() << error.errorString();
    }
    qDebug() << "Ignoring ssl errors ...";
    m_reply->ignoreSslErrors();
}
