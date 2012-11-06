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

#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QObject>
#include <QStringList>
#include <QPixmap>

#include "qfacebook.h"
#include "qfacebookreply.h"

class UserProfile : public QObject
{
    Q_OBJECT
public:
    explicit UserProfile(QObject *parent = 0);
    void setToken(QString token);
    void setId(QString id);

    QString name();
    QPixmap picture();

signals:
    void finished();

public slots:
    int load();

private slots:
    void onDataReady();
    void onPictureReady();

private:
    QFacebook *qfaceBook;
    QString m_token;
    QString m_id;
    bool m_isLoaded;
    QString m_name;
    QImage m_picture;
};

#endif // USERPROFILE_H
