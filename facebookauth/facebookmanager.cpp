#include <QString>
#include <QDateTime>

#include <QtDebug>

#include "facebookmanager.h"
#include "facebookstatusdata.h"

#include "parser.h"  // JSON Parser

const QString FacebookManager::FB_URL_MYFEED = "https://graph.facebook.com/me?fields=id";

FacebookManager::FacebookManager(QObject *parent) :
    QObject(parent),
    m_rootContext(0),
    m_networkManager(new QNetworkAccessManager)
{
}

void FacebookManager::onAccessTokenChanged(const QString &accessToken)
{
    m_accessToken = accessToken;

    QUrl newsFeedRequest = QString(FB_URL_MYFEED);
    newsFeedRequest.addQueryItem(QLatin1String("access_token"), m_accessToken);

    QNetworkRequest request;
    request.setUrl(newsFeedRequest);

    qDebug() << "Sending to Facebook: " << newsFeedRequest;
    m_networkManager->get(request);
    connect(m_networkManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}

void FacebookManager::setRootContext(QDeclarativeContext *rootContext)
{
    qDebug() << "FacebookManager: Got root context from QML.";
    m_rootContext = rootContext;
}

void FacebookManager::replyFinished(QNetworkReply *reply)
{
    QByteArray facebookResponse = reply->readAll();

    QJson::Parser parser;
    bool ok;
    QVariantMap result = parser.parse(facebookResponse, &ok).toMap();
    QList<QVariant> facebookUpdates = result.value("data").toList();

    QList<QObject*> tmpUpdates;
    foreach (const QVariant &facebookUpdate, facebookUpdates) {
        QVariantMap updateData = facebookUpdate.toMap();

        QString type = updateData.value("type").toString();
        if (type == QString("status")) {
            FacebookStatusData *statusMessage = new FacebookStatusData;
            statusMessage->setStatusMessage(updateData.value("message").toString());

            QDateTime createdDateTime = QDateTime::fromString(updateData.value("created_time").toString(),
                                                              Qt::ISODate);
            statusMessage->setCreated(createdDateTime.toString("dd MMM yyyy, hh:mm"));

            QVariantMap from = updateData.value("from").toMap();
            statusMessage->setUserPictureUrl(QString("https://graph.facebook.com/%1/picture?access_token=%2")
                                             .arg(from.value("id").toString())
                                             .arg(m_accessToken));
            tmpUpdates.append(statusMessage);
        }
    }

    qDebug() << "Got Facebook updates: " << tmpUpdates.size();

    if (tmpUpdates.size() != statusUpdatesModel.size()) {
        statusUpdatesModel = tmpUpdates;
        m_rootContext->setContextProperty("statusModel", QVariant::fromValue(statusUpdatesModel));
    }

    reply->deleteLater();
}

void FacebookManager::slotError(QNetworkReply::NetworkError error)
{
    qDebug() << "Network error:" << error;
}

QList<QObject *> FacebookManager::statusModel() const
{
    return statusUpdatesModel;
}

