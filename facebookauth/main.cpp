#include <QtDeclarative>
#include <QtGui/QApplication>
#include <QGraphicsObject>

#include <QtDebug>

#include "qmlapplicationviewer.h"
#include "oauth2authorizer.h"
#include "facebookmanager.h"
#include "getfriends.h"

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


//using namespace Dissent::Crypto;
//using namespace Dissent::Crypto::AbstractGroup;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    QmlApplicationViewer viewer;
//    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
//    viewer.setMainQmlFile(QLatin1String("../../qfacebook-qfacebook/facebookauth/qml/facebookauth/main.qml"));

//    OAuth2Authorizer authorizer;
//    viewer.rootContext()->setContextProperty("authorizer", &authorizer);

//    QObject *rootItem = viewer.rootObject();

//    QObject::connect(rootItem, SIGNAL(loadStarted(QUrl)),
//                     &authorizer, SLOT(onWebLoadStarted(QUrl)));
////    QObject::connect(rootItem, SIGNAL(loadFinished(QUrl)),
////                     &authorizer, SLOT(onWebLoadFinished(QUrl)));

//    FacebookManager fManager;
//    fManager.setRootContext(viewer.rootContext());
//    QObject::connect(&authorizer, SIGNAL(accessTokenChanged(QString)),
//                     &fManager, SLOT(onAccessTokenChanged(QString)));

//    viewer.showExpanded();


    GetFriends w;
    w.show();

    //Fake facebookID
    const char ID[]="1223989894530";
    //Original Message
    const char message[]="It is good for you!";
    Hash *hash=CryptoFactory::GetInstance().GetLibrary()->GetHashAlgorithm();
    //Compute the message hash
    QByteArray MessageHash=hash->ComputeHash(message).toHex();


    qDebug()<<"Pkg Server Set Up..."<<endl;
    PkgServer Pkg=PkgServer("Param.txt");
//    QFile file("Private_Key.dat");
//     QByteArray Compact;
//    if(file.open(QIODevice::ReadOnly)) {
//        qDebug()<<"Hello World!"<<endl;
//        Compact=file.readAll();
//      //  Compact=QByteArray::fromHex(Compact);
//        qDebug()<<Compact.constData()<<endl;
//        file.close();
//    }

//#########################TEST system parameter serilization#############
//     QByteArray byteArray;
//     SystemParam example;
//     QDataStream stream(&byteArray, QIODevice::WriteOnly);
//     stream << Pkg.getParam();

//      QDataStream stream1(byteArray);
//      stream1>>example;


    IBEPublicKey PublicKey(ID,SystemParam(QString("System_Parameter.txt")));
//    //Get the PrivateKey from the PkgServer based on user ID
    qDebug()<<"Get the PrivateKey from Pkg Server..."<<endl;
    IBEPrivateKey PrivateKey=Pkg.GetPrivateKey(ID);
//    //###################TEST Private Key serilization###############
//    QByteArray Barray;
//    QDataStream stream2(&Barray,QIODevice::WriteOnly);
//    stream2<<PrivateKey;
//    IBEPrivateKey exampleKey;
//     QDataStream stream3(Barray);
//     stream3>>exampleKey;
//qDebug()<<"After Private Key serilization"<<endl;
//     //##############TEST Public Key serilization######################
//     QByteArray BArray;
//     QDataStream stream4(&BArray,QIODevice::WriteOnly);
//     stream4<<PublicKey;
//     IBEPublicKey examplePKey;
//      QDataStream stream5(&BArray,QIODevice::ReadOnly);
//      stream5>>examplePKey;



    qDebug()<<"Original Message: \n"<<message<<endl;
    qDebug()<<"Original Message Hash:\n"<<MessageHash.constData();
    QByteArray Ciphertext=PublicKey.Encrypt(MessageHash);
    qDebug()<<"The ciphertext: \n"<<Ciphertext.constData()<<endl;
    QByteArray text=PrivateKey.Decrypt(Ciphertext);


    qDebug()<<"The length of text is "<<strlen(text.constData());

    qDebug()<<"Original Message Hash:\n"<<MessageHash.constData();
    qDebug()<<"Decrpted Message Hash:\n"<<text.constData();
    if(QString(text.constData())==QString(MessageHash.constData())){
        qDebug()<<"\nCongratulations! Sucessfully Decrypted the Message Hash!"<<endl;
    }



    return app.exec();
}
