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

#include "postfeed.h"
#include "ui_postfeed.h"

PostFeed::PostFeed(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PostFeed)
{
    ui->setupUi(this);

    getFriends = new PutObject(this);
    getFriends->setId("me");
    ui->idEdit->setText("me");

    connect(getFriends, SIGNAL(finished()), this, SLOT(onFriendsReady()));
}

PostFeed::~PostFeed()
{
    delete ui;
}

void PostFeed::on_tokenEdit_editingFinished()
{
    getFriends->setToken(ui->tokenEdit->text());
}

void PostFeed::on_idEdit_editingFinished()
{
    getFriends->setId(ui->idEdit->text());
}

void PostFeed::onFriendsReady()
{
    ui->pushButton->setText("Post");
    ui->msgEdit->setText("");
}

void PostFeed::on_pushButton_clicked()
{
    if (!getFriends->push(ui->msgEdit->toPlainText()))
        ui->pushButton->setText("Sending ...");
}
