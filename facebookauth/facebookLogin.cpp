#include "facebookLogin.h"


void facebookLogin:: LoginPage()
{
    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("../../qfacebook-qfacebook/facebookauth/qml/facebookauth/main.qml"));

    OAuth2Authorizer authorizer;
    viewer.rootContext()->setContextProperty("authorizer", &authorizer);

    QObject *rootItem = viewer.rootObject();

    QObject::connect(rootItem, SIGNAL(loadStarted(QUrl)),
                     &authorizer, SLOT(onWebLoadStarted(QUrl)));
//    QObject::connect(rootItem, SIGNAL(loadFinished(QUrl)),
//                     &authorizer, SLOT(onWebLoadFinished(QUrl)));

    FacebookManager fManager;
    fManager.setRootContext(viewer.rootContext());
    QObject::connect(&authorizer, SIGNAL(accessTokenChanged(QString)),
                     &fManager, SLOT(onAccessTokenChanged(QString)));

    viewer.showExpanded();

}

