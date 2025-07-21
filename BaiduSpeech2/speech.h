#ifndef SPEECH_H
#define SPEECH_H

#include <QObject>
#include <http.h>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QHostInfo>
#include <QFile>
#include <QMessageBox>

// 获取 access_token 相关
const QString baiduTokenUrl = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2&";
const QString client_id = "U4bDd3MFDJ1uvUMSO3VsKFnL";
const QString client_secret = "UWJpk11CaMvp0IiyR8VBrD8HnXMRUIHx";

// 语音识别相关
const QString baiduSpeechUrl1 = "http://vop.baidu.com/server_api?dev_pid=1537&cuid=%1&token=%2";
const QString baiduSpeechUrl2 = "http://vop.baidu.com/server_api?dev_pid=1737&cuid=%1&token=%2";

class Speech : public QObject
{
    Q_OBJECT
public:
    explicit Speech(QObject *parent = nullptr);

    QString speechIdentify(QString fileName);
    QString getJsonValue(QByteArray ba, QString key);
    void setSpeechUrlType(int type); // 添加设置 URL 类型的函数

private:
    int speechUrlType = 1; // 默认使用普通话 URL
};

#endif // SPEECH_H
