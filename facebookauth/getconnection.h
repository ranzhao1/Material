#ifndef GETCONNECTION_H
#define GETCONNECTION_H

#include <QObject>
#include <QStringList>

#include "qfacebook.h"
#include "qfacebookreply.h"

class GetConnection : public QObject
{
    Q_OBJECT
public:
    explicit GetConnection(QObject *parent = 0);
    void setToken(QString token);
    void setId(QString id);

signals:
    void finished(QStringList list);

public slots:
    int load();

private slots:
    void onDataReady();

private:
    QFacebook *qfaceBook;
    QFacebookReply *m_reply;
    QString m_token;
    QString m_id;
};
#endif // GETCONNECTION_H
