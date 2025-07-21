#include "http.h"

Http::Http(QObject *parent)
    : QObject{parent}
{}



bool Http::post_sync(QString Url,QMap<QString, QString> header, QByteArray requestData, QByteArray &replyData){

    //发送请求的对象
    QNetworkAccessManager manager;

    //请求对象
    QNetworkRequest request;
    request.setUrl(Url);
    QMapIterator<QString, QString> it(header);      //迭代器
    while (it.hasNext()){           //遍历
        it.next();
        request.setRawHeader(it.key().toLatin1(), it.value().toLatin1());
    }

    QNetworkReply *reply = manager.post(request, requestData);
    QEventLoop l;
    //一旦服务器返回，reply会发出信号
    connect(reply, &QNetworkReply::finished, &l, &QEventLoop::quit);
    l.exec();        //死循环，reply发出信号，结束循环

    if(reply != nullptr && reply->error() == QNetworkReply::NoError){
        replyData = reply->readAll();   //读取服务器返回的数据
        //qDebug() << replyData;
        //qDebug() << header;
        //qDebug() << requestData;
        //qDebug() << "请求成功";
        return true;
    }
    else{
        qDebug() << "请求失败";
        if (reply->error() == QNetworkReply::NoError) {
            replyData = reply->readAll();

            // 解析JSON并打印err_no
            QJsonParseError parseError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(replyData, &parseError);

            if (parseError.error == QJsonParseError::NoError && jsonDoc.isObject()) {
                QJsonObject jsonObj = jsonDoc.object();

                if (jsonObj.contains("err_no")) {
                    int errNo = jsonObj["err_no"].toInt();
                    qDebug() << "err_no:" << errNo;

                    // 添加错误描述
                    if (errNo == 0) {
                        // 识别成功，打印结果
                        if (jsonObj.contains("result")) {
                            QString result = jsonObj["result"].toString();
                            qDebug() << "识别结果:" << result;
                        }
                    } else {
                        // 处理错误情况
                        qDebug() << "识别失败，错误码:" << errNo;

                        // 可选：获取错误详情
                        if (jsonObj.contains("err_msg")) {
                            QString errMsg = jsonObj["err_msg"].toString();
                            qDebug() << "错误详情:" << errMsg;
                        }
                    }
                } else {
                    qDebug() << "JSON中未找到err_no字段";
                    qDebug() << "完整响应:" << QString::fromUtf8(replyData);
                }
            } else {
                qDebug() << "JSON解析错误:" << parseError.errorString();
                qDebug() << "原始响应数据:" << QString::fromUtf8(replyData);
            }
        } else {
            qDebug() << "网络请求错误:" << reply->errorString();
            qDebug() << "HTTP状态码:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        }
        return false;
    }

}
