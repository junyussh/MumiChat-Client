#include "mylabel.h"
#include <QCoreApplication>
#include <QLabel>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QWidget>
Mylabel::Mylabel(const QString &text, QWidget *parent)
    : QLabel(parent)
{
    this->setText(text);
    //connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
}
/*
void Mylabel::slotClicked()
{

}
*/
void Mylabel::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mylabel mousePressEvent";
    setStyleSheet("QLabel {background-color: white;"
                  " color:rgb(102, 184, 255);"
                  " border: 1px solid rgb(102, 184, 255);}");
}

void Mylabel::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "mylabel mouseMoveEvent";
    setStyleSheet("QLabel {background-color: white;"
                  " color:rgb(102, 184, 255);"
                  " border: 1px solid rgb(102, 184, 255);}");
}

void Mylabel::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "mylabel mouseReleaseEvent";
    setStyleSheet("QLabel {background-color:rgb(102, 184, 255); color:white;}");

    // 延遲執行時間，看到按壓效果
    QTime reachTime = QTime::currentTime().addMSecs(200); // 200 毫秒
    while (QTime::currentTime() < reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.2sec
    }

    emit clicked(this->text());
    qDebug() << "emit click";
}
void Mylabel::enterEvent(QEvent *)
{
    setStyleSheet("QLabel {background-color:rgb(120, 199, 255);color:white;}");
    qDebug() << "mylabel enter";
}
void Mylabel::leaveEvent(QEvent *)
{
    setStyleSheet("QLabel {background-color:rgb(102, 184, 255); color:white;}");
    qDebug() << "mylabel leave";
}
REDlabel::REDlabel(const QString &text, QWidget *parent)
    : QLabel(parent)
{
    this->setText(text);
    //connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
}

void REDlabel::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mylabel mousePressEvent";
    setStyleSheet("QLabel {background-color: red;"
                  " color:white;"
                  " border: 1px solid red;}");
}

void REDlabel::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "mylabel mouseMoveEvent";
    setStyleSheet("QLabel {background-color: red;"
                  " color:white;"
                  " border: 1px solid red;}");
}

void REDlabel::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "mylabel mouseReleaseEvent";
    setStyleSheet("QLabel {background-color:rgb(255, 84, 84); color:white;}");

    // 延遲執行時間，看到按壓效果
    QTime reachTime = QTime::currentTime().addMSecs(200); // 200 毫秒
    while (QTime::currentTime() < reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.2sec
    }

    emit clicked(this->text());
    qDebug() << "emit click";
}
void REDlabel::enterEvent(QEvent *)
{
    setStyleSheet("QLabel {background-color:red;color:white;}");
    qDebug() << "mylabel enter";
}
void REDlabel::leaveEvent(QEvent *)
{
    setStyleSheet("QLabel {background-color:rgb(255, 84, 84); color:white;}");
    qDebug() << "mylabel leave";
}
Nolabel::Nolabel(const QString &text, QWidget *parent)
    : QLabel(parent)
{
    this->setText(text);
    //connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
}

void Nolabel::mousePressEvent(QMouseEvent *event)
{
    qDebug() <<"Nolabel is click";
    emit clicked(tr("setting"));
}

whitelabel::whitelabel(const QString &text, QWidget *parent)
    : QLabel(parent)
{
    this->setText(text);
    //connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
}

void whitelabel::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "whitelabel mousePressEvent";
    setStyleSheet("QLabel {background-color: rgb(230, 230, 230);color:black;padding:15px;}");
}

void whitelabel::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "whitelabel mouseMoveEvent";
    setStyleSheet("QLabel {background-color: rgb(230, 230, 230);color:black;padding:15px;}");
}

void whitelabel::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "whitelabel mouseReleaseEvent";
    setStyleSheet("QLabel {background-color:rgb(255, 255, 255); color:black;padding:15px;}");

    // 延遲執行時間，看到按壓效果
    QTime reachTime = QTime::currentTime().addMSecs(200); // 200 毫秒
    while (QTime::currentTime() < reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.2sec
    }

    emit clicked(this->text());
    qDebug() << "emit click";
}
void whitelabel::enterEvent(QEvent *)
{
    setStyleSheet("QLabel {background-color:rgb(236, 236, 236);color:black;padding:15px;}");
    qDebug() << "whitelabel enter";
}
void whitelabel::leaveEvent(QEvent *)
{
    setStyleSheet("QLabel {background-color:white; color:black;padding:15px;}");
    qDebug() << "whitelabel leave";
}

whiteToRedlabel::whiteToRedlabel(const QString &text, QWidget *parent)
    : QLabel(parent)
{
    this->setText(text);
    //connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
}

void whiteToRedlabel::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "whitelabel mousePressEvent";
    setStyleSheet("QLabel {background-color: rgb(255, 0, 0);color:white;padding:15px;}");
}

void whiteToRedlabel::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "whitelabel mouseMoveEvent";
    setStyleSheet("QLabel {background-color: rgb(255, 0, 0);color:white;padding:15px;}");
}

void whiteToRedlabel::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "whitelabel mouseReleaseEvent";
    setStyleSheet("QLabel {background-color:rgb(255, 255, 255); color:black;padding:15px;}");

    // 延遲執行時間，看到按壓效果
    QTime reachTime = QTime::currentTime().addMSecs(200); // 200 毫秒
    while (QTime::currentTime() < reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.2sec
    }

    emit clicked(this->text());
    qDebug() << "emit RED click";
}
void whiteToRedlabel::enterEvent(QEvent *)
{
    setStyleSheet("QLabel {background-color:rgb(255, 84, 84);color:white;padding:15px;}");
    qDebug() << "white RED label enter";
}
void whiteToRedlabel::leaveEvent(QEvent *)
{
    setStyleSheet("QLabel {background-color:white; color:black;padding:15px;}");
    qDebug() << "white RED label leave";
}


FRIENDlabel::FRIENDlabel(const QString &text, QWidget *parent)
    : QLabel(parent)
{
    this->setText(text);
    //connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
}

void FRIENDlabel::mousePressEvent(QMouseEvent *event)
{
    qDebug() <<"Nolabel is click";
    emit clicked(tr("friendManage"));
}
