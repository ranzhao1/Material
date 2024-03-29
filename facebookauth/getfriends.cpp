#include "getfriends.h"
#include "ui_getfriends.h"
#include <QtDebug>
#include <QtDeclarative>
#include <QtGui/QApplication>
#include <QGraphicsObject>
#include <QTextEdit>
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
#include "Crypto/IBEPrivateKey.hpp"
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
    else{
         ui->StoreResult->setText("Sorry! You do not have a private key!");
    }


}

void GetFriends::on_EncryptButton_clicked()
{
    SystemParam SysParam=SystemParam(QString("System_Parameter.txt"));
    IBEPublicKey PublicKey=IBEPublicKey(UserID.toUtf8().constData(),SysParam);
    Hash *hash=CryptoFactory::GetInstance().GetLibrary()->GetHashAlgorithm();
    //Compute the message hash
    QByteArray MessageHash=hash->ComputeHash(QByteArray(ui->inputText->toPlainText().toUtf8())).toHex();
    OriginalMessageHash=MessageHash;
    ui->messageHash->setText(OriginalMessageHash.constData());
    qDebug()<<"&&&&&&&&&&&Original MessageHash is "<<MessageHash<<endl;
    QByteArray Ciphertext=PublicKey.Encrypt(MessageHash);
    WriteFile("Ciphertext.txt",Ciphertext);

    ui->StoreResult->setText("Well Done! Successfully Encrypted!");


}

void GetFriends::on_DecryptButton_clicked()
{
     IBEPrivateKey Privatekey=IBEPrivateKey(QString("Private_key.txt"));
    QByteArray Ciphertext=ReadFile(QString("Ciphertext.txt"));
    qDebug()<<"The size of Ciphertext is "<<strlen(Ciphertext.constData());
    QByteArray text=Privatekey.Decrypt(Ciphertext);
    if(QString(text.constData())==QString(OriginalMessageHash.constData())){
        ui->StoreResult->setText("Congratulations! You get right message hash!");

}
    else{
        ui->StoreResult->setText("Opps! You are wrong!");
        qDebug()<<"text"<<text.constData();
        qDebug()<<"Oringal"<<OriginalMessageHash.constData();
    }
    WriteFile("DecryptText.txt",text);

    qDebug()<<"Enter into Decrypt"<<endl;
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
           UserID=buddy;

           qDebug()<<"The IDDD is "<<UserID;;
           //    const char ID[]=buddy.toUtf8().constData();
               //Original Message
               const char message[]="It is good for you!";
               Hash *hash=CryptoFactory::GetInstance().GetLibrary()->GetHashAlgorithm();
               //Compute the message hash
               QByteArray MessageHash=hash->ComputeHash(message).toHex();


               qDebug()<<"Pkg Server Set Up..."<<endl;
               PkgServer Pkg=PkgServer("Param.txt");





               IBEPublicKey PublicKey(buddy.toUtf8().constData(),SystemParam(QString("System_Parameter.txt")));
               qDebug()<<"Get the PrivateKey from Pkg Server..."<<endl;
               IBEPrivateKey PrivateKey=Pkg.GetPrivateKey(buddy.toUtf8().constData());
               QFile file("Private_Key.txt");
               if(!file.open(QIODevice::WriteOnly)) {
                 qWarning() << "Error reading files";
               }
               QDataStream stream(&file);
               stream<<PrivateKey;
               file.close();
               ui->StoreResult->setText("Get my private key!");


//                   QFile file("Private_key.txt");
//                  if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
//                      QTextStream out(&file);
//                      out << data;
//                  }



                  // optional, as QFile destructor will already do it:
                 IBEPrivateKey Privatekey=IBEPrivateKey(QString("Private_Key.txt"));




               qDebug()<<"Original Message: \n"<<message<<endl;
               qDebug()<<"Original Message Hash:\n"<<MessageHash.constData();
               QByteArray Ciphertext=PublicKey.Encrypt(MessageHash);
               qDebug()<<"The before ciphertext: \n"<<Ciphertext.size()<<endl;
               WriteFile("Ciphertext.txt",Ciphertext);
               Ciphertext=ReadFile("Ciphertext.txt");
               qDebug()<<"The ciphertext: \n"<<Ciphertext.toHex().constData()<<endl;
               QByteArray text=Privatekey.Decrypt(Ciphertext);


               qDebug()<<"The length of text is "<<strlen(text.constData());

               qDebug()<<"Original Message Hash:\n"<<MessageHash.constData();
               qDebug()<<"Decrpted Message Hash:\n"<<text.constData();
               if(QString(text.constData())==QString(MessageHash.constData())){
                   qDebug()<<"\nCongratulations! Sucessfully Decrypted the Message Hash!"<<endl;
               }




//        QListWidgetItem *item = new QListWidgetItem(ui->listFriends);
//        item->setText(buddy);
    }

}

QByteArray GetFriends::ReadFile(const QString &filename)
{
    QByteArray data;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
      qWarning() << "Error (" << file.error() << ") reading file: " << filename;
    }

    data = file.readAll();
    qDebug()<<"%%%%%%%%%%%%%%%%%%%"<<data.size();
    file.close();
    return data;

}

void GetFriends::WriteFile(const QString& filename, const QByteArray &data)
{
    QFile file(filename);
    qDebug()<<"Before write data "<<data;
    qDebug()<<"The file size is "<<file.size();
    if(!file.open(QIODevice::WriteOnly)) {
      qWarning() << "Error (" << file.error() << ") reading file: " << filename;
    }
   file.write(data);
   file.close();
}
