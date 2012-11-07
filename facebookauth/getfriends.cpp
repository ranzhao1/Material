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

#include "Crypto/AbstractGroup/PairingG1Group.hpp"
#include "Crypto/AbstractGroup/PairingGTGroup.hpp"
#include "Crypto/CryptoFactory.hpp"
#include "Crypto/CppHash.hpp"
#include "Crypto/PkgServer.hpp"
#include "Crypto/IBEPublicKey.hpp"
#include <QByteArray>
#include <QDebug>
#include"Crypto/AbstractGroup/ByteElementData.hpp"



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

        else{
            ui->StoreResult->setText("You already get your IBE Private Key");
        }
//        QTextStream in(&file);
//        while (!in.atEnd()) {
//            strings += in.readLine().split(";");
//        }
    }


}

void GetFriends::on_EncryptButton_clicked()
{

    qDebug()<<"You click encrypt button"<<endl;

}

void GetFriends::on_DecryptButton_clicked()
{
    qDebug()<<"You click decrypt button"<<endl;
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

           //Fake facebookID
           qDebug()<<"The IDDD is "<<buddy.toUtf8().constData();;
           //    const char ID[]=buddy.toUtf8().constData();
               //Original Message
               const char message[]="It is good for you!";
               Hash *hash=CryptoFactory::GetInstance().GetLibrary()->GetHashAlgorithm();
               //Compute the message hash
               QByteArray MessageHash=hash->ComputeHash(message).toHex();


               qDebug()<<"Pkg Server Set Up..."<<endl;
               PkgServer Pkg=PkgServer("Param.txt");





                IBEPublicKey PublicKey(buddy.toUtf8().constData(),Pkg.getParam());
               qDebug()<<"Get the PrivateKey from Pkg Server..."<<endl;
               IBEPrivateKey PrivateKey=Pkg.GetPrivateKey(buddy.toUtf8().constData());
               QByteArray data;
               QDataStream stream(&data,QIODevice::WriteOnly);
               stream<<PrivateKey;

                   QFile file("Private_key.txt");
                  if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
                      QTextStream out(&file);
                      out << data;
                  }


                  // optional, as QFile destructor will already do it:
                  file.close();




//        QListWidgetItem *item = new QListWidgetItem(ui->listFriends);
//        item->setText(buddy);
    }
}

