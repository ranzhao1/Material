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

    m_reply = qfaceBook->getConnections(m_id, "id");
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
  //  listData = jsonData.toMap().value("id").toList();
    qDebug()<<"Before emit"<<jsonData.toMap().value("id").toString();
//    foreach(jsonData, listData) {
//        friends.append(jsonData.toMap().value("id").toString());
//    }

friends.append(jsonData.toMap().value("id").toString());
    emit finished(friends);
}

