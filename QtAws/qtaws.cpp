#include "qtaws.h"
#define db qDebug() << this <<

QtAws::QtAws(QByteArray AcessKey, QByteArray SecretKey)
{
    access_key = AcessKey;
    secret_key = SecretKey;
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::finished,
            this, &QtAws::requestFinished);
}

void QtAws::requestFinished(QNetworkReply * reply)
{
    requestStream(reply->readAll());
}

QByteArray QtAws::getSignatureKey(QByteArray key, QByteArray dateStamp, QByteArray regionName, QByteArray serviceName)
{
    QByteArray kDate = sign(QUrl("AWS4" + key).toEncoded(), dateStamp);
    QByteArray kRegion = sign(kDate, regionName);
    QByteArray kService = sign(kRegion, serviceName);
    QByteArray kSigning = sign(kService, "aws4_request");
    return kSigning;
}

QByteArray QtAws::sign(const QByteArray & key, const QByteArray & data)
{
    return QMessageAuthenticationCode::hash(data, key, QCryptographicHash::Sha256);
}

void QtAws::requestAWS(QByteArray service, QByteArray method, QByteArray api, QByteArray postBody, QByteArray objectData)
{
    QByteArray host = service + "." + region + ".amazonaws.com";
    QByteArray endpoint = "https://" + host + api;
    QByteArray request_parameters = "LanguageCode=en-US";
    QByteArray time =  QDateTime::currentDateTimeUtc().toString(Qt::ISODate).toLocal8Bit();
    time.replace("-", "");
    time.replace(":", "");
    QByteArray amz_date = time;
    QByteArray datestamp = amz_date.mid(0, amz_date.indexOf("T"));

    if(method == "GET")
    {
        QByteArray canonical_headers = "host:" + host + "\n";
        QByteArray signed_headers = "host";
        QByteArray algorithm = "AWS4-HMAC-SHA256";
        QByteArray credential_scope = datestamp + "/" + region + "/" + service + "/" + "aws4_request";
        QByteArray canonical_querystring = request_parameters;
        canonical_querystring += "&X-Amz-Algorithm=AWS4-HMAC-SHA256";
        canonical_querystring += "&X-Amz-Credential=" + QByteArray(access_key + QByteArray("/") + credential_scope).replace("/", "%2F");
        canonical_querystring += "&X-Amz-Date=" + amz_date;
        canonical_querystring += "&X-Amz-Expires=30";
        canonical_querystring += "&X-Amz-SignedHeaders=" + signed_headers;
        QByteArray payload_hash = QCryptographicHash::hash("", QCryptographicHash::Sha256).toHex();
        QByteArray canonical_request = method + "\n" + api + "\n" + canonical_querystring + "\n" + canonical_headers + "\n" + signed_headers + "\n" + payload_hash;
        QByteArray string_to_sign = algorithm + "\n" +  amz_date + "\n" +  credential_scope + "\n" + QCryptographicHash::hash(canonical_request, QCryptographicHash::Sha256).toHex();
        QByteArray signing_key = getSignatureKey(secret_key, datestamp, region, service);
        QByteArray signature = sign(signing_key, string_to_sign).toHex();
        canonical_querystring += "&X-Amz-Signature=" + signature;
        requestURL(endpoint + "?" + canonical_querystring);
    }
    else if (method == "POST")
    {
        QByteArray canonical_headers = "content-type:application/x-amz-json-1.0\nhost:" + host + "\n" + "x-amz-date:" + amz_date + "\n";
        QByteArray signed_headers = "content-type;host;x-amz-date";
        QByteArray payload_hash = QCryptographicHash::hash(postBody, QCryptographicHash::Sha256).toHex();
        QByteArray canonical_request = method + "\n" + api + "\n\n" + canonical_headers + "\n" + signed_headers + "\n" + payload_hash;
        QByteArray algorithm = "AWS4-HMAC-SHA256";
        QByteArray credential_scope = datestamp + "/" + region + "/" + service + "/" + "aws4_request";
        QByteArray string_to_sign = algorithm + "\n" +  amz_date + "\n" +  credential_scope + "\n" + QCryptographicHash::hash(canonical_request, QCryptographicHash::Sha256).toHex();
        QByteArray signing_key = getSignatureKey(secret_key, datestamp, region, service);
        QByteArray signature = sign(signing_key, string_to_sign).toHex();
        QString authorization_header = algorithm + " " + "Credential=" + access_key + "/" + credential_scope + ", " +  "SignedHeaders=" + signed_headers + ", " + "Signature=" + signature;
        QByteArray request_url = endpoint;
        clear();
        setRawHeader("Content-Type", "application/x-amz-json-1.0");
        setRawHeader("X-Amz-Date", amz_date);
        setRawHeader("Authorization", authorization_header);
        QNetworkRequest request;
        request.setUrl(QUrl(endpoint));
        QUrlQuery params;
        QByteArray postData;

        for (int i = 0; i < headers.size(); i += 2)
            request.setRawHeader(headers.at(i), headers.at(i + 1));

        m_manager->post(request, postBody);
    }
    else
    {
        qWarning("WARNING: REQUEST METHOD NOT FOUND");
    }
}

bool QtAws::Lock() const
{
    return bLock;
}

QString QtAws::getText() const
{
    return requestString;
}

void QtAws::requestPolly(QString Text, QString Voice, QString Method)
{
    if(bLock) return;

    bLock = true;
    requestString = Text;
    QJsonObject post_data;
    post_data["OutputFormat"] = "mp3";
    post_data["Text"] = Text;
    post_data["VoiceId"] = Voice;
    QJsonDocument doc(post_data);
    requestAWS("polly", Method.toLocal8Bit(), "/v1/speech", doc.toJson(QJsonDocument::Compact));
}

void QtAws::requestTranscribe(QString Text, QString Voice, QString Method)
{
    if(bLock) return;

    bLock = true;
    requestString = Text;
    QJsonObject post_data;
    post_data["LanguageCode"] = "en-US";
    post_data["Media"] = Text;
    post_data["TranscriptionJobName"] = "TranscriptionRequest";
    QJsonDocument doc(post_data);
    requestAWS("polly", Method.toLocal8Bit(), "/v1/speech", doc.toJson(QJsonDocument::Compact));
}

void QtAws::requestURL(QString url_Req)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url_Req));

    for (int i = 0; i < headers.size(); i += 2)
        request.setRawHeader(headers.at(i), headers.at(i + 1));

    m_manager->get(request);
}

void QtAws::clear()
{
    headers.clear();
    posting_data.clear();
}

void QtAws::setRawHeader(QString a, QString b)
{
    headers.append(a.toUtf8());
    headers.append(b.toUtf8());
}

void QtAws::setRawParam(QString a, QString b    )
{
    posting_data.append(a.toUtf8());
    posting_data.append(b.toUtf8());
}

void QtAws::sendPacket(QString base)
{
    QNetworkRequest request;
    request.setUrl((QUrl(base)));
    QUrlQuery params;
    QByteArray postData;

    for (int i = 0; i < headers.size(); i += 2)
        request.setRawHeader(headers.at(i), headers.at(i + 1));

    for (int i = 0; i < posting_data.size(); i += 2)
        params.addQueryItem(posting_data.at(i), posting_data.at(i + 1));

    postData = params.query(QUrl::FullyEncoded).toUtf8();
    m_manager->post(request, postData);
}

