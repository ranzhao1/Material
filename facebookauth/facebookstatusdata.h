#ifndef FACEBOOKSTATUSDATA_H
#define FACEBOOKSTATUSDATA_H

#include <QObject>

class FacebookStatusData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString statusMessage READ statusMessage WRITE setStatusMessage NOTIFY statusMessageChanged)
    Q_PROPERTY(QString created READ created WRITE setCreated NOTIFY createdChanged)
    Q_PROPERTY(QString userPictureUrl READ userPicture WRITE setUserPictureUrl NOTIFY userPictureChanged)

public:
    explicit FacebookStatusData(QObject *parent = 0);

    QString statusMessage() const;
    QString created() const;
    QString userPicture() const;

    void setStatusMessage(const QString &message);
    void setCreated(const QString &created);
    void setUserPictureUrl(const QString &userPicture);

signals:
    void createdChanged(QString created);
    void statusMessageChanged(QString message);
    void userPictureChanged(QString newUrl);

public slots:

private:
    QString m_created;
    QString m_statusMessage;
    QString m_userPictureUrl;
};

#endif // FACEBOOKSTATUSDATA_H
