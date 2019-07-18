#ifndef CHATMAINWINDOW_H
#define CHATMAINWINDOW_H
#include <iostream>
#include <QMainWindow>
#include <QListWidgetItem>
#include <QKeyEvent>
#include "chatmessage.h"
#include "mylabel.h"
using namespace std;


namespace Ui {
class CHATMainWindow;
}

class CHATMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CHATMainWindow(QWidget *parent = 0);
    ~CHATMainWindow();

    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);
    void dealMessageTime(QString curMsgTime);
protected:
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event); // 按數字鍵盤和鍵盤的 Enter鍵事件
private slots:
    //void on_pushButton_clicked();

private:
    Ui::CHATMainWindow *ui;
    Nolabel *link;
};
#endif // CHATMAINWINDOW_H
