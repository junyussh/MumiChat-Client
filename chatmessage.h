
#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <QWidget>
#include <QColor>
#include <QLabel>

class QPaintEvent;
class QPainter;
class QLabel;
class QMovie;

class QNChatMessage : public QWidget
{
    Q_OBJECT
public:
    explicit QNChatMessage(QWidget *parent = nullptr);

    // 之後需要調整的部分-用戶類型
    enum User_Type
    {
        User_System, //system
        User_Me,     //me
        User_She,    //Other_usr
        User_Time,   //time
    };

    void setTextSuccess(); // 成功發出消息
    //
    void setText(QString text, QString time, QSize allSize, User_Type userType);

    QSize getRealString(QString src); //返回由文字寬高判斷的氣泡框大小
    QSize fontRect(QString str);

    inline QString text() { return m_msg; }            // 返回訊息
    inline QString time() { return m_time; }           // 返回時間
    inline User_Type userType() { return m_userType; } // 返回用戶類型
protected:
    void paintEvent(QPaintEvent *event); // 輸出
private:
    QString m_msg;     // 傳送的訊息
    QString m_time;    // 傳送時間
    QString m_curTime; // 目前時間

    QSize m_allSize; // 對話窗口大小
    User_Type m_userType = User_System;

    int m_widgetWidth; // 聊天氣泡框
    int m_textWidth;    // 字
    int m_spaceWid;
    int m_lineHeight; // 行高

    // 定義形狀
    QRect m_iconLeftRect;       // 對方的 avatar
    QRect m_iconRightRect;      // 自己的 avater
    QRect m_triangleLeftRect;  // 對方的聊天氣泡三角
    QRect m_triangleRightRect; // 自己的聊天氣泡三角
    QRect m_widgetLeftRect;    // 對方的聊天氣泡框
    QRect m_widgetRightRect;   // 自己的聊天氣泡框
    QRect m_textLeftRect;       // 對方的文字框
    QRect m_textRightRect;      // 自己的文字框

    QRect m_timeText_rect;      // 時間框位置
    QSize m_timeText;           // 時間框大小

    // 聊天用戶之間頭像
    QPixmap m_leftPixmap;  // 對方
    QPixmap m_rightPixmap; // 自己

    // 加載訊息的圖標
    QLabel *m_loading = Q_NULLPTR;
    QMovie *m_loadingMovie = Q_NULLPTR;

    // 判斷訊息送出成功與否
    bool m_isSending = false;

    bool flagfirst = true;
};

#endif // CHATMESSAGE_H
