#include "getfriends.h"
#include "ui_getfriends.h"
#include <QtDebug>
#include <QtDeclarative>
#include <QtGui/QApplication>
#include <QGraphicsObject>
#include <QFile>

#include "qmlapplicationviewer.h"
#include "oauth2authorizer.h"
#include "facebookmanager.h"



QmlApplicationViewer* viewer;
GetFriends::GetFriends(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GetFriends)
{
    ui->setupUi(this);

    getFriends = new GetConnection(this);
    getFriends->setId("me");
    ui->idEdit->setText("");
    ui->tokenEdit->setText("");



    connect(getFriends, SIGNAL(finished(QStringList)), this, SLOT(onFriendsReady(QStringList)));
}

GetFriends::~GetFriends()
{
    delete ui;
}

void GetFriends::on_pushButton_clicked()
{

    QFile file("Private_key.txt");
    QStringList strings;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        if(file.size()==0){
            ui->StoreResult->setText("Sorry! You do not have a private key!");

        }
        QTextStream in(&file);
        while (!in.atEnd()) {
            strings += in.readLine().split(";");
        }
    }


}

void GetFriends::on_tokenEdit_editingFinished()
{

    qDebug()<<"Something in on_tokenEdit_editing";
    getFriends->setToken(ui->tokenEdit->text());
}

void GetFriends::on_idEdit_editingFinished()
{
     qDebug()<<"Something is on_idEdit_editing";
    getFriends->setId(ui->idEdit->text());
}

void GetFriends::on_loadButton_clicked()
{
    qDebug()<<"Good!!!\n";

    viewer=QmlApplicationViewer::create();

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setMainQmlFile(QLatin1String("../../qfacebook-qfacebook/facebookauth/qml/facebookauth/main.qml"));

    OAuth2Authorizer* authorizer=new OAuth2Authorizer();
    viewer->rootContext()->setContextProperty("authorizer", authorizer);

    QObject *rootItem = viewer->rootObject();

    QObject::connect(rootItem, SIGNAL(loadStarted(QUrl)),
                     authorizer, SLOT(onWebLoadStarted(QUrl)));

    FacebookManager* fManager=new FacebookManager();
    fManager->setRootContext(viewer->rootContext());
    QObject::connect(authorizer, SIGNAL(accessTokenChanged(QString)),
                     this, SLOT(receiveToken(QString)));

    QObject::connect(authorizer, SIGNAL(accessTokenChanged(QString)),
                       fManager, SLOT(onAccessTokenChanged(QString)));


    viewer->showExpanded();
    qDebug()<<getFriends->load();
//    if (!getFriends->load())

//        ui->loadButton->setText("Loading ...");

}


void GetFriends::receiveToken(QString accesstoken)
{
    getFriends->setToken(accesstoken);
    getFriends->load();
    ui->tokenEdit->setText(accesstoken);

    viewer->closeWindow();


}

void GetFriends::onFriendsReady(QStringList friends)
{
    ui->loadButton->setText("Load");
   // ui->listFriends->clear();
    foreach(QString buddy, friends) {
           ui->idEdit->setText(buddy);
//        QListWidgetItem *item = new QListWidgetItem(ui->listFriends);
//        item->setText(buddy);
    }
}

