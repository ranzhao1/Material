#ifndef OAUTH2AUTHORIZER_H
#define OAUTH2AUTHORIZER_H

#include <QObject>
#include <QUrl>

class OAuth2Authorizer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString accessToken READ accessToken WRITE setAccessToken NOTIFY accessTokenChanged)

public:
    static const QString SUCCESSFUL_REDIRECT_URL;

    explicit OAuth2Authorizer(QObject *parent = 0);
    QString accessToken() const;
    void setAccessToken(const QString &accessToken);

signals:
    void accessTokenChanged(QString accessToken);

public slots:
    void onWebLoadFinished(const QUrl &url);
    void onWebLoadStarted(const QUrl &url);


private:
    QString m_accessToken;


};

#endif // OAUTH2AUTHORIZER_H
