#include "chatmainwindow.h"
#include "ui_chatmainwindow.h"
#include "chatmessage.h"
#include <QDateTime>
#include <QDebug>
CHATMainWindow::CHATMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CHATMainWindow)
{
    ui->setupUi(this);
    ui->widget->setGeometry(this->rect());
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->label_tip->setGeometry(this->width() / 2 - ui->label_tip->width() / 2,
                               this->height() / 2 - ui->label_tip->height() / 2 - 30,
                               ui->label_tip->width(), ui->label_tip->height());
    link = new Nolabel("link", this);
    link->setGeometry(0, this->height() - 60, 60, 60);
    QPixmap *pixmap = new QPixmap(":/images/icon/link.png");
    pixmap->scaled(link->size(), Qt::KeepAspectRatio);
    link->setScaledContents(true);
    link->setPixmap(*pixmap);
    link->setStyleSheet("QLabel {background-color: rgb(255, 255, 255);"
                        "border-bottom: 0.5px solid #d7d6e3;"
                        "border-left: 0.5px solid #d7d6e3;padding: 15px;}");
}

CHATMainWindow::~CHATMainWindow()
{
    delete ui;
}


/*
void CHATMainWindow::on_pushButton_clicked()
{
    QString msg = ui->textEdit->toPlainText();
    ui->textEdit->setText("");
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳

    bool isSending = true; // 发送中

    qDebug()<<"addMessage" << msg << time << ui->listWidget->count();
    if(ui->listWidget->count()%2) {
        if(isSending) {
            dealMessageTime(time);

            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
        } else {
            bool isOver = true;
            for(int i = ui->listWidget->count() - 1; i > 0; i--) {
                QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
                if(messageW->text() == msg) {
                    isOver = false;
                    messageW->setTextSuccess();
                }
            }
            if(isOver) {
                dealMessageTime(time);

                QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
                QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
                dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
                messageW->setTextSuccess();
            }
        }
    } else {
        if(msg != "") {
            dealMessageTime(time);

            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            dealMessage(messageW, item, msg, time, QNChatMessage::User_She);
        }
    }
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
}
*/
void CHATMainWindow::dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time,  QNChatMessage::User_Type type)
{
    messageW->setFixedWidth(this->width());
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, time, size, type);
    ui->listWidget->setItemWidget(item, messageW);
}

void CHATMainWindow::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    if(ui->listWidget->count() > 0) {
        QListWidgetItem* lastItem = ui->listWidget->item(ui->listWidget->count() - 1);
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
        //        isShowTime = true;
    } else {
        isShowTime = true;
    }
    if(isShowTime) {
        QNChatMessage* messageTime = new QNChatMessage(ui->listWidget->parentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(ui->listWidget);

        QSize size = QSize(this->width(), 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, QNChatMessage::User_Time);
        ui->listWidget->setItemWidget(itemTime, messageTime);
    }
}

void CHATMainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    ui->widget->setGeometry(0, 0,this->width(), this->height());
    ui->listWidget->setGeometry(0,0, this->width(), this->height() - 60);
    ui->textEdit->setGeometry(60, this->height() - 60, this->width() - 60, 60);
    link->setGeometry(0, this->height() - 60, 60, 60);
    //ui->pushButton->move(ui->textEdit->width()+ui->textEdit->x() - ui->pushButton->width() - 10,
    //                     ui->textEdit->height()+ui->textEdit->y() - ui->pushButton->height() - 10);
    ui->label_tip->setGeometry(this->width() / 2 - ui->label_tip->width() / 2,
                               this->height() / 2 - ui->label_tip->height() / 2 - 30,
                               ui->label_tip->width(), ui->label_tip->height());
    for(int i = 0; i < ui->listWidget->count(); i++) {
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
        QListWidgetItem* item = ui->listWidget->item(i);

        dealMessage(messageW, item, messageW->text(), messageW->time(), messageW->userType());
    }
}

// 輸出訊息
void CHATMainWindow::keyPressEvent(QKeyEvent *event)
{
    //ctrl + 數字鍵盤的Enter键
    //ctrl + Enter键
    if (event->modifiers() == Qt::ControlModifier && (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter))
    {
        ui->label_tip->setVisible(false);
        QString msg = ui->textEdit->toPlainText();
        string tempMSG = msg.toStdString();
        // 去 ctrl 和 \n
        //tempMSG += " ";
        tempMSG.erase(tempMSG.end() - 1);
        tempMSG.erase(tempMSG.end() - 1);
        ui->textEdit->setText("");
        QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //時間截

        bool isSending = true; // 發送中

        qDebug() << "addMessage" << msg << time << ui->listWidget->count();
        if (ui->listWidget->count() % 2)
        {
            if (isSending)
            {
                dealMessageTime(time);

                QNChatMessage *messageW = new QNChatMessage(ui->listWidget->parentWidget());
                QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
                dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
            }
            else
            {
                bool isOver = true;
                // 處理輸入文字
                for (int i = ui->listWidget->count() - 1; i > 0; i--)
                {
                    QNChatMessage *messageW = (QNChatMessage *)ui->listWidget->itemWidget(ui->listWidget->item(i));
                    if (messageW->text() == msg)
                    {
                        isOver = false;
                        messageW->setTextSuccess();
                    }
                }
                // 處理時間文字
                if (isOver)
                {
                    dealMessageTime(time);

                    QNChatMessage *messageW = new QNChatMessage(ui->listWidget->parentWidget());
                    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
                    dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
                    messageW->setTextSuccess();
                }
            }
        }
        else
        {
            if (msg != "")
            {
                dealMessageTime(time);

                QNChatMessage *messageW = new QNChatMessage(ui->listWidget->parentWidget());
                QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
                dealMessage(messageW, item, msg, time, QNChatMessage::User_She);
            }
        }
        ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);
    }
}

