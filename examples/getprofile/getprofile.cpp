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

#include "getprofile.h"
#include "ui_getprofile.h"

GetProfile::GetProfile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GetProfile)
{
    ui->setupUi(this);

    userProfile = new UserProfile(this);
    userProfile->setId("ragnermagalhaes");
    ui->idEdit->setText("ragnermagalhaes");

    connect(userProfile, SIGNAL(finished()), this, SLOT(onDataReady()));
}

GetProfile::~GetProfile()
{
    delete ui;
}

void GetProfile::on_tokenEdit_editingFinished()
{
    userProfile->setToken(ui->tokenEdit->text());
}

void GetProfile::on_idEdit_editingFinished()
{
    userProfile->setId(ui->idEdit->text());
}

void GetProfile::on_pushButton_clicked()
{
    if (!userProfile->load())
        ui->pushButton->setText("Loading ...");
}

void GetProfile::onDataReady()
{
    ui->pushButton->setText("Load");
    ui->nameEdit->setText(userProfile->name());
    ui->labelPicture->setPixmap(userProfile->picture());
}
