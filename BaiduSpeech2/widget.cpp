#include "widget.h"
#include "ui_widget.h"
#include <QPropertyAnimation>
#include <QFontDatabase>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 设置窗口标题
    setWindowTitle("语音识别系统");


        // 加载幼圆字体
        int fontId = QFontDatabase::addApplicationFont(":/fonts/幼圆.ttf");
        if (fontId != -1) {
            QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
            QFont buttonFont(fontFamily);
            buttonFont.setBold(true); // 字体加粗
            // 应用到所有按钮
            ui->pushButton->setFont(buttonFont);
            ui->clearButton->setFont(buttonFont);
            ui->deleteButton->setFont(buttonFont);
        } else {
            // 如果加载失败，使用系统默认字体并加粗
            QFont defaultFont;
            defaultFont.setFamily("幼圆"); // 尝试直接设置字体名称
            defaultFont.setBold(true);
            ui->pushButton->setFont(defaultFont);
            ui->clearButton->setFont(defaultFont);
            ui->deleteButton->setFont(defaultFont);
        }


    ui->pushButton->setText("按住说话");

    // 连接下拉框的信号到槽函数
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_currentIndexChanged(int)));

    // 程序启动时显示识别结果
    displayResultsInTable();

    // 设置按钮样式
    // 设置按钮样式 - 变淡后的颜色
    // --------------------- 主按钮（更浅的绿色） ---------------------
    ui->pushButton->setStyleSheet("QPushButton {"
                                  "    background-color: #A5D6A7;" // 浅薄荷绿
                                  "    color: #000000;" // 黑色文字
                                  "    border: none;"
                                  "    padding: 12px 24px;"
                                  "    text-align: center;"
                                  "    text-decoration: none;"
                                  "    display: inline-block;"
                                  "    font-size: 18px;"
                                  "    margin: 4px 2px;"
                                  "    cursor: pointer;"
                                  "    border-radius: 8px;"
                                  "    transition: background-color 0.3s ease;"
                                  "}"
                                  "QPushButton:hover {"
                                  "    background-color: #81C784;" // 稍深的薄荷绿
                                  "}"
                                  "QPushButton:pressed {"
                                  "    background-color: #66BB6A;" // 更深的薄荷绿
                                  "}");

    // --------------------- 清除按钮（更浅的橙色） ---------------------
    ui->clearButton->setStyleSheet("QPushButton {"
                                   "    background-color: #FFAB91;" // 浅珊瑚色
                                   "    color: #000000;" // 黑色文字
                                   "    border: none;"
                                   "    padding: 12px 24px;"
                                   "    text-align: center;"
                                   "    text-decoration: none;"
                                   "    display: inline-block;"
                                   "    font-size: 18px;"
                                   "    margin: 4px 2px;"
                                   "    cursor: pointer;"
                                   "    border-radius: 8px;"
                                   "    transition: background-color 0.3s ease;"
                                   "}"
                                   "QPushButton:hover {"
                                   "    background-color: #FF8A65;" // 稍深的珊瑚色
                                   "}"
                                   "QPushButton:pressed {"
                                   "    background-color: #FF7043;" // 更深的珊瑚色
                                   "}");

    // --------------------- 删除按钮（更浅的淡黄色） ---------------------
    ui->deleteButton->setStyleSheet("QPushButton {"
                                    "    background-color: #FFF8E1;" // 极淡的米黄色
                                    "    color: #000000;" // 黑色文字
                                    "    border: 1px solid #FFECB3;" // 极浅的黄边框
                                    "    padding: 10px 20px;"
                                    "    text-align: center;"
                                    "    text-decoration: none;"
                                    "    display: inline-block;"
                                    "    font-size: 16px;"
                                    "    margin: 4px 2px;"
                                    "    cursor: pointer;"
                                    "    border-radius: 6px;"
                                    "    transition: background-color 0.3s ease;"
                                    "}"
                                    "QPushButton:hover {"
                                    "    background-color: #FFF3E0;" // 稍深的米黄色
                                    "    border-color: #FFE0B2;"
                                    "}"
                                    "QPushButton:pressed {"
                                    "    background-color: #FFECB3;" // 更深的米黄色
                                    "    border-color: #FFE0B2;"
                                    "}");
    // 设置表格样式
    ui->tableWidget->setStyleSheet("QTableWidget {"
                                   "    border: 2px solid #dee2e6;"
                                   "    border-radius: 8px;"
                                   "    background-color: white;"
                                   "    color: #495057;"
                                   "}"
                                   "QTableWidget::item {"
                                   "    padding: 8px;"
                                   "}"
                                   "QHeaderView::section {"
                                   "    background-color: #f8f9fa;"
                                   "    border: none;"
                                   "    padding: 8px;"
                                   "    font-weight: bold;"
                                   "    color: #495057;"
                                   "}"
                                   "QTableWidget::item:selected {"
                                   "    background-color: #007BFF;"
                                   "    color: white;"
                                   "}");

    // 设置文本编辑框样式
    ui->textEdit->setStyleSheet("QTextEdit {"
                                "    border: 2px solid #dee2e6;"
                                "    border-radius: 8px;"
                                "    padding: 8px;"
                                "    background-color: white;"
                                "    color: #495057;"
                                "}"
                                "QTextEdit:focus {"
                                "    border-color: #007BFF;"
                                "    outline: none;"
                                "}");

    // 设置下拉框样式
    ui->comboBox->setStyleSheet("QComboBox {"
                                "    border: 2px solid #dee2e6;"
                                "    border-radius: 8px;"
                                "    padding: 8px;"
                                "    background-color: white;"
                                "    color: #495057;"
                                "}"
                                "QComboBox::drop-down {"
                                "    subcontrol-origin: padding;"
                                "    subcontrol-position: top right;"
                                "    width: 24px;"
                                "    border-left-width: 2px;"
                                "    border-left-color: #dee2e6;"
                                "    border-left-style: solid;"
                                "    border-top-right-radius: 8px;"
                                "    border-bottom-right-radius: 8px;"
                                "}"
                                "QComboBox::down-arrow {"
                                "    image: none;"
                                "}"
                                "QComboBox::hover {"
                                "    border-color: #007BFF;"
                                "}"
                                "QComboBox::focus {"
                                "    border-color: #007BFF;"
                                "    outline: none;"
                                "}");

    // 添加按钮动画效果
    QPropertyAnimation *animation = new QPropertyAnimation(ui->pushButton, "geometry");
    animation->setDuration(500);
    animation->setStartValue(ui->pushButton->geometry());
    animation->setEndValue(ui->pushButton->geometry().adjusted(-5, -5, 5, 5));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->setLoopCount(-1);
    animation->start();

    // 设置窗口背景为奶绿色渐变
    this->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #E8F5E9, stop:1 #FFFFFF);");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_pressed()
{
    ui->pushButton->setText("松开识别");

    // 开始录音
    audio = new Audio;
    audio->startAudio("F:\\1.pcm");
}

void Widget::on_pushButton_released()
{
    // 停止录音
    audio->stopAudio();
    // 修改按钮文本
    ui->pushButton->setText("开始识别");
    // 开始识别
    QString text = m_speech.speechIdentify("F:\\1.pcm");

    ui->textEdit->setText(text);

    // 插入识别结果到数据库
    if (!text.isEmpty()) {
        m_sqlite.insertResult(text);
        displayResultsInTable();
    }

    ui->pushButton->setText("按住说话");
}

void Widget::on_clearButton_clicked()
{
    ui->textEdit->clear();
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    if (index == 0) { // 普通话
        m_speech.setSpeechUrlType(1);
    } else if (index == 1) { // 英文
        m_speech.setSpeechUrlType(2);
    }
}

void Widget::displayResultsInTable() {
    QList<QString> results = m_sqlite.getAllResults();
    int tableHeight = ui->tableWidget->height();
    int rowHeight = 24;
    int maxRows = tableHeight / rowHeight;
    int targetRowCount = qMax(results.size(), maxRows);

    ui->tableWidget->setRowCount(targetRowCount);
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setHorizontalHeaderLabels({"识别结果"});

    // 关键：让列宽自动拉伸，填满表格水平空间
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < targetRowCount; ++i) {
        if (i < results.size()) {
            QTableWidgetItem *item = new QTableWidgetItem(results[i]);
            // 让单元格内容自动换行（可选，若内容过长）
            item->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
            item->setFlags(item->flags() | Qt::ItemIsEditable); // 可选：允许编辑
            ui->tableWidget->setItem(i, 0, item);
        } else {
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(""));
        }
    }
}

void Widget::on_deleteButton_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow != -1) {
        // 获取当前行的识别结果
        QString result = ui->tableWidget->item(currentRow, 0)->text();
        // 查询该结果对应的 id
        QSqlQuery query;
        query.prepare("SELECT id FROM SpeechResults WHERE result = :result");
        query.bindValue(":result", result);
        if (query.exec() && query.next()) {
            int id = query.value(0).toInt();
            if (m_sqlite.deleteSingleResult(id)) {
                displayResultsInTable(); // 更新表格显示
            }
        }
    }
}
