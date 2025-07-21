#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <audio.h>
#include <speech.h>
#include <QComboBox>
#include <sqlite.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_pressed();
    void on_pushButton_released();
    void on_clearButton_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void displayResultsInTable();
    void on_deleteButton_clicked();

private:
    Ui::Widget *ui;
    Audio *audio;
    Speech m_speech;
    sqlite m_sqlite;
};
#endif // WIDGET_H
