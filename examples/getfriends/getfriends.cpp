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

#include "getfriends.h"
#include "ui_getfriends.h"

GetFriends::GetFriends(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GetFriends)
{
    ui->setupUi(this);

    getFriends = new GetConnection(this);
    getFriends->setId("me");
    ui->idEdit->setText("1257272113");
    ui->tokenEdit->setText("AAAGZAiRqMQn4BAPCMNHL2KuBPTR3432Kd3mo3XJNNh61RcDKOwbaqOTHmt418OiokxPyz1yQciBjMwZAQ0yCjKZC7tRK6B9UYzOZBvGz91ExcbnHbZC6M");


    connect(getFriends, SIGNAL(finished(QStringList)), this, SLOT(onFriendsReady(QStringList)));
}

GetFriends::~GetFriends()
{
    delete ui;
}

void GetFriends::on_tokenEdit_editingFinished()
{
    getFriends->setToken(ui->tokenEdit->text());
}

void GetFriends::on_idEdit_editingFinished()
{
    getFriends->setId(ui->idEdit->text());
}

void GetFriends::on_loadButton_clicked()
{
    if (!getFriends->load())
        ui->loadButton->setText("Loading ...");
}

void GetFriends::onFriendsReady(QStringList friends)
{
    ui->loadButton->setText("Load");
    ui->listFriends->clear();
    foreach(QString buddy, friends) {
        QListWidgetItem *item = new QListWidgetItem(ui->listFriends);
        item->setText(buddy);
    }
}
