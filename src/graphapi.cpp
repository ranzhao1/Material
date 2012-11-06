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

#include <QNetworkRequest>
#include <QUrl>
#include <QDebug>

#include "graphapi.h"

GraphAPI::GraphAPI(QString accessToken, QObject *parent)
    : QObject(parent),
    m_accessToken(accessToken),
    m_networkManager( new QNetworkAccessManager(this))
{
}

QFacebookReply *GraphAPI::getObject(QString id)
{
    return request(GraphAPI::GET, id);
}

QFacebookReply *GraphAPI::getConnections(QString id, QString connectionName)
{
    return request(GraphAPI::GET, connectionName);
}

QFacebookReply *GraphAPI::putObject(QString id, QString connection, QByteArray data)
{
    // You need extended permissions to do it.
    // http://developers.facebook.com/docs/authentication/
    return request(GraphAPI::POST, id + "/" + connection, data);
}

QFacebookReply *GraphAPI::deleteObject(QString id)
{
    return request(GraphAPI::DELETE, id);
}

QFacebookReply *GraphAPI::request(HttpMethod method, QString path, QByteArray postArgs)
{
    QString query="https://graph.facebook.com/me?field="+path;
    QUrl url(query);
  //  url.setPath(path);


    switch (method) {
    case GraphAPI::GET:
    case GraphAPI::DELETE:
        url.addQueryItem("access_token", m_accessToken);
        break;
    case GraphAPI::POST:
        postArgs.append("&access_token=" + m_accessToken);
        break;
    default:
        qWarning() << "Request method is not supported.";
        return 0;
    }

    return new QFacebookReply(request(method, url, postArgs), this);
}

QNetworkReply *GraphAPI::get(QUrl url)
{
    return request(GraphAPI::GET, url);
}

QNetworkReply *GraphAPI::put(QUrl url, QByteArray data)
{
    return request(GraphAPI::POST, url, data);
}

QNetworkReply *GraphAPI::del(QUrl url)
{
    return request(GraphAPI::DELETE, url);
}

QNetworkReply *GraphAPI::request(HttpMethod method, QUrl url, QByteArray postArgs)
{
    QNetworkRequest request;
    QNetworkReply *reply(0);
    request.setUrl(url);

    switch (method) {
    case GraphAPI::GET:
        reply = m_networkManager->get(request);
        break;
    case GraphAPI::POST:
        reply = m_networkManager->post(request, postArgs);
        break;
    case GraphAPI::DELETE:
        reply = m_networkManager->deleteResource(request);
        break;
    default:
        qWarning() << "Request method is not supported.";
        return 0;
    }

    return reply;
}
