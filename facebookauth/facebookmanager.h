#ifndef FACEBOOKMANAGER_H
#define FACEBOOKMANAGER_H

#include <QObject>
#include <QtDeclarative>
#include <QtNetwork>

class FacebookManager : public QObject
{
    Q_OBJECT
public:
    explicit FacebookManager(QObject *parent = 0);

    void setRootContext(QDeclarativeContext *rootContext);
    QList<QObject *> statusModel() const;

signals:

public slots:
    void onAccessTokenChanged(const QString &accessToken);

private slots:
    void replyFinished(QNetworkReply *reply);
    void slotError(QNetworkReply::NetworkError error);

private:
    static const QString FB_URL_MYFEED;

    QString m_accessToken;
    QDeclarativeContext *m_rootContext;
    QNetworkAccessManager *m_networkManager;

    QList<QObject *> statusUpdatesModel;
};

#endif // FACEBOOKMANAGER_H
