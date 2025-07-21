#include "speech.h"
#include <QJsonArray>
#include <QJsonValue>

Speech::Speech(QObject *parent)
    : QObject{parent}
{}

void Speech::setSpeechUrlType(int type)
{
    speechUrlType = type;
}

QString Speech::speechIdentify(QString fileName)
{
    QString accessToken;
    // 获取 access_token
    QString tokenUrl = QString(baiduTokenUrl).arg(client_id, client_secret);

    QMap<QString, QString> header;
    header.insert(QString("Content-Type"), QString("audio/pcm;rate=16000"));

    QByteArray requstData;           // 发送的内容
    QByteArray replyData;            // 服务器返回的内容

    Http m_http;
    bool result = m_http.post_sync(tokenUrl, header, requstData, replyData);
    if (result) {
        QString key = "access_token";
        accessToken = getJsonValue(replyData, key);
    }
    else {
        // 处理获取 access_token 失败的情况
    }

    // 根据 URL 类型选择不同的识别 URL
    QString speechUrl;
    if (speechUrlType == 1) {
        speechUrl = QString(baiduSpeechUrl1).arg(QHostInfo::localHostName()).arg(accessToken);
    } else if (speechUrlType == 2) {
        speechUrl = QString(baiduSpeechUrl2).arg(QHostInfo::localHostName()).arg(accessToken);
    }

    // 把文件转换为 QByteArray
    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::ReadOnly);
    requstData = file.readAll();
    file.close();

    replyData.clear();

    // 再次发起请求
    result = m_http.post_sync(speechUrl, header, requstData, replyData);
    if (result) {
        QString key = "result";
        QString text = getJsonValue(replyData, key);
        return text;
    }
    else {
        QMessageBox::warning(NULL, "识别失败", "语音识别失败");
    }
    return "";
}

QString Speech::getJsonValue(QByteArray ba, QString key)
{
    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(ba, &parseError);
    if (parseError.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject()) {
            // jsonDocument 转换成 json 对象
            QJsonObject jsonObj = jsonDocument.object();
            if (jsonObj.contains(key)) {
                QJsonValue jsonVal = jsonObj.value(key);
                if (jsonVal.isString()) {    // 字符串
                    return jsonVal.toString();
                }
                else if (jsonVal.isArray()) {      // 数组
                    QJsonArray arr = jsonVal.toArray();     // 转换成 JsonArray
                    QJsonValue jv = arr.at(0);              // 获取第一个元素
                    return jv.toString();
                }
            }
        }
    }
    return "";
}
