#ifndef FACEBOOKLOGIN_H
#define FACEBOOKLOGIN_H

#include <QObject>
#include <QUrl>

#include <QtDeclarative>
#include <QtGui/QApplication>
#include <QGraphicsObject>

#include <QtDebug>

#include "qmlapplicationviewer.h"
#include "oauth2authorizer.h"
#include "facebookmanager.h"

class FacebookLogin : public QObject
{
    Q_OBJECT


public:


signals:


public slots:
    void LoginPage();



};



#endif // FACEBOOKLOGIN_H
