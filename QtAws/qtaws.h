#ifndef QTAWS_H
#define QTAWS_H

#include "qtaws_global.h"

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QDateTime>
#include <QDebug>
#include <QCryptographicHash>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageAuthenticationCode>
#include <QFile>
#include <QDir>

class QTAWSSHARED_EXPORT QtAws : public QObject
{
    Q_OBJECT

public:
    QtAws(QByteArray AcessKey, QByteArray SecretKey);
    bool Lock() const;
    QString getText() const;
private slots:
    void requestFinished(QNetworkReply * reply);
    QByteArray getSignatureKey(QByteArray key, QByteArray dateStamp, QByteArray regionName, QByteArray serviceName);
    QByteArray sign(const QByteArray & key, const QByteArray & data);
    void requestAWS(QByteArray service, QByteArray method, QByteArray api, QByteArray postBody, QByteArray objectData = QByteArray());

public slots:
    void requestPolly(QString Text, QString Voice = "Joanna", QString Method = "POST");
    void requestTranscribe(QString Text, QString Voice = "Joanna", QString Method = "POST");
    void requestURL(QString url_Req);
    void clear();
    void setRawHeader(QString, QString);
    void setRawParam(QString, QString);
    void sendPacket(QString base);

signals:
    void requestStream(QByteArray);
    void requestURLFinished(QString url, QString response);
    void requestReply(QNetworkReply * reply);

private:

    QByteArray region = "us-west-1";

    QByteArray access_key;
    QByteArray secret_key;

    QString endpoint = "apigateway.us-west-1.amazonaws.com";
    QString url;
    QList<QByteArray> headers;
    QList<QByteArray> posting_data;
    QNetworkAccessManager * m_manager;
    bool bLock = false;
    QString requestString;
};

#endif // QTAWS_H
