#ifndef GETFRIENDS_H
#define GETFRIENDS_H

#include <QMainWindow>
#include <getconnection.h>
#include "qmlapplicationviewer.h"

namespace Ui {
    class GetFriends;
}

class GetFriends : public QMainWindow
{
    Q_OBJECT

public:
    explicit GetFriends(QWidget *parent = 0);
    QByteArray ReadFile(const QString& filename);
    void WriteFile(const QString& filename,const QByteArray &data);
    ~GetFriends();

private:
    Ui::GetFriends *ui;
    GetConnection *getFriends;
    const char* ID;


public slots:
    void receiveToken(QString accesstoken);

private slots:
    void on_loadButton_clicked();
    void on_pushButton_clicked();
    void on_EncryptButton_clicked();
    void on_DecryptButton_clicked();
    void on_idEdit_editingFinished();
    void on_tokenEdit_editingFinished();
    void onFriendsReady(QStringList friends);
};

#endif // GETFRIENDS_H
