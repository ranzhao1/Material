#include <QtDeclarative>
#include <QtGui/QApplication>
#include <QGraphicsObject>

#include <QtDebug>

#include "qmlapplicationviewer.h"
#include "oauth2authorizer.h"
#include "facebookmanager.h"
#include "getfriends.h"

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

    return app.exec();
}
