#include <QtDebug>
#include <QStringList>

#include "oauth2authorizer.h"

const QString OAuth2Authorizer::SUCCESSFUL_REDIRECT_URL = "http://www.facebook.com/connect/login_success.html";

OAuth2Authorizer::OAuth2Authorizer(QObject *parent) :
    QObject(parent)
{
}

void OAuth2Authorizer::setAccessToken(const QString &accessToken)
{
    if (accessToken != m_accessToken) {
        qDebug() << "Set access token as: " << accessToken;
        m_accessToken = accessToken;
        emit accessTokenChanged(m_accessToken);
    }
}

QString OAuth2Authorizer::accessToken() const
{
    return m_accessToken;
}

void OAuth2Authorizer::onWebLoadFinished(const QUrl &url)
{
}

void OAuth2Authorizer::onWebLoadStarted(const QUrl &url)
{
    qDebug() << "Web loading started: " << url;
    qDebug() << "Outside {}";
    if (!url.isEmpty() && url.toString().startsWith(OAuth2Authorizer::SUCCESSFUL_REDIRECT_URL)) {
        qDebug() << "Come into {}";
        QString accessToken = url.encodedFragment();        // Get the URL fragment part
        accessToken = accessToken.split("&").first();       // Remove the "expires_in" part.
        accessToken = accessToken.split("=").at(1);         // Split by "access_token=..." and take latter part

        setAccessToken(accessToken);
    }
}
