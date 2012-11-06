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

#ifndef GETCONNECTION2_H
#define GETCONNECTION2_H

#include <QObject>
#include <QStringList>

#include "qfacebook.h"
#include "qfacebookreply.h"

class PutObject : public QObject
{
    Q_OBJECT
public:
    explicit PutObject(QObject *parent = 0);
    void setToken(QString token);
    void setId(QString id);

signals:
    void finished();

public slots:
    int push(QString message);

private slots:
    void onDataReady();

private:
    QFacebook *qfaceBook;
    QFacebookReply *m_reply;
    QString m_token;
    QString m_id;
};

#endif // GETCONNECTION_H
