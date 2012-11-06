#include "facebookstatusdata.h"

FacebookStatusData::FacebookStatusData(QObject *parent) :
    QObject(parent)
{
}

QString FacebookStatusData::statusMessage() const
{
    return m_statusMessage;
}

QString FacebookStatusData::created() const
{
    return m_created;
}

QString FacebookStatusData::userPicture() const {
    return m_userPictureUrl;
}

void FacebookStatusData::setStatusMessage(const QString &message)
{
    if (message != m_statusMessage) {
        m_statusMessage = message;
        emit statusMessageChanged(m_statusMessage);
    }
}

void FacebookStatusData::setCreated(const QString &created)
{
    if (created != m_created) {
        m_created = created;
        emit createdChanged(m_created);
    }
}

void FacebookStatusData::setUserPictureUrl(const QString &userPicture)
{
    if (userPicture != m_userPictureUrl) {
        m_userPictureUrl = userPicture;
        emit userPictureChanged(m_userPictureUrl);
    }
}

