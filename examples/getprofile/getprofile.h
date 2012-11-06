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

#ifndef GETPROFILE_H
#define GETPROFILE_H

#include <QMainWindow>
#include <userprofile.h>

namespace Ui {
    class GetProfile;
}

class GetProfile : public QMainWindow
{
    Q_OBJECT

public:
    explicit GetProfile(QWidget *parent = 0);
    ~GetProfile();

private:
    Ui::GetProfile *ui;
    UserProfile *userProfile;

private slots:
    void on_pushButton_clicked();
    void on_idEdit_editingFinished();
    void on_tokenEdit_editingFinished();
    void onDataReady();
};

#endif // GETPROFILE_H
