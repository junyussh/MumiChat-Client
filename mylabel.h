#ifndef MYLABEL_H
#define MYLABEL_H
#include "QMessageBox"
#include <QDebug>
#include <QDialog>
#include <QEvent>
#include <QLabel>
#include <QMainWindow>
#include <QString>
#include <QTime>
#include <QWidget>

// 有點擊特效
class Mylabel : public QLabel
{
    Q_OBJECT
public:
    Mylabel(const QString &text, QWidget *parent = 0);
    ~Mylabel() {}
signals:
    void clicked(QString);

    /*
public slots:
    void slotClicked();
*/
protected:
    void mousePressEvent(QMouseEvent *event);   // 滑鼠點擊
    void mouseMoveEvent(QMouseEvent *event);    // 滑鼠點擊後移動
    void mouseReleaseEvent(QMouseEvent *event); // 滑鼠釋放
    void enterEvent(QEvent *);                  // 滑鼠移入
    void leaveEvent(QEvent *);                  // 滑鼠移出
};

class REDlabel : public QLabel
{
    Q_OBJECT
public:
    REDlabel(const QString &text, QWidget *parent = 0);
    ~REDlabel() {}
signals:
    void clicked(QString);

    /*
public slots:
    void slotClicked();
*/
protected:
    void mousePressEvent(QMouseEvent *event);   // 滑鼠點擊
    void mouseMoveEvent(QMouseEvent *event);    // 滑鼠點擊後移動
    void mouseReleaseEvent(QMouseEvent *event); // 滑鼠釋放
    void enterEvent(QEvent *);                  // 滑鼠移入
    void leaveEvent(QEvent *);                  // 滑鼠移出
};
// 無點擊特效，專門為 LLK 頁面setting 的label
class Nolabel : public QLabel
{
    Q_OBJECT
public:
    Nolabel(const QString &text, QWidget *parent = 0);
    ~Nolabel() {}
signals:
    void clicked(QString);

    /*
public slots:
    void slotClicked();
*/
protected:
    void mousePressEvent(QMouseEvent *event); // 滑鼠點擊
    /*void mouseMoveEvent(QMouseEvent *event);  // 滑鼠點擊後移動
    void mouseReleaseEvent(QMouseEvent *event); // 滑鼠釋放
    */
};

// 白灰特效
class whitelabel : public QLabel
{
    Q_OBJECT
public:
    whitelabel(const QString &text, QWidget *parent = 0);
    ~whitelabel() {}
signals:
    void clicked(QString);

    /*
public slots:
    void slotClicked();
*/
protected:
    void mousePressEvent(QMouseEvent *event);   // 滑鼠點擊
    void mouseMoveEvent(QMouseEvent *event);    // 滑鼠點擊後移動
    void mouseReleaseEvent(QMouseEvent *event); // 滑鼠釋放
    void enterEvent(QEvent *);                  // 滑鼠移入
    void leaveEvent(QEvent *);                  // 滑鼠移出
};

// 白紅特效
class whiteToRedlabel : public QLabel
{
    Q_OBJECT
public:
    whiteToRedlabel(const QString &text, QWidget *parent = 0);
    ~whiteToRedlabel() {}
signals:
    void clicked(QString);

    /*
public slots:
    void slotClicked();
*/
protected:
    void mousePressEvent(QMouseEvent *event);   // 滑鼠點擊
    void mouseMoveEvent(QMouseEvent *event);    // 滑鼠點擊後移動
    void mouseReleaseEvent(QMouseEvent *event); // 滑鼠釋放
    void enterEvent(QEvent *);                  // 滑鼠移入
    void leaveEvent(QEvent *);                  // 滑鼠移出
};
class FRIENDlabel : public QLabel
{
    Q_OBJECT
public:
    FRIENDlabel(const QString &text, QWidget *parent = 0);
    ~FRIENDlabel() {}
signals:
    void clicked(QString);

    /*
public slots:
    void slotClicked();
*/
protected:
    void mousePressEvent(QMouseEvent *event); // 滑鼠點擊
    /*void mouseMoveEvent(QMouseEvent *event);  // 滑鼠點擊後移動
    void mouseReleaseEvent(QMouseEvent *event); // 滑鼠釋放
    */
};
#endif // MYLABEL_H


