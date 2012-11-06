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
#include <QDebug>
#include <QTimer>

#include "getobject.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("SimpleGet");

    if (argc != 3) {
        qDebug() << "Use :getobject \'access token\' \'id\'";
        return 1;
    }

    GetObject getObject;
    QTimer::singleShot(0, &getObject, SLOT(load()));

    return a.exec();
}
