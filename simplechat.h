#ifndef SIMPLECHAT_H
#define SIMPLECHAT_H

#include <QMainWindow>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtWebSockets/QWebSocket>
#include<QList>
#include <QMap>
#include<QStandardItemModel>
#include <QMetaType>
#include "itemdef.h"
#include "itemdelegate.h"
#include "chatmessage.h"
#include "chatmainwindow.h"
#include <QtSql>

namespace Ui {
class SimpleChat;
}

class SimpleChat : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimpleChat(QWidget *parent = nullptr);
    ~SimpleChat();
    void setSocket(QWebSocket*);
    void setDB(QSqlDatabase);
    void FriendList(QJsonArray);
    void setLoginUser(QString email);
    QMap<QString, User*> Manager;
    CHATMainWindow *chat;
private slots:
    void listClicked(QModelIndex);
    void sendMessage(QString);
private:
    /* 目前的登入帳號 */
    QString loginUser;
    QString loginUserID;
    /* 選中的好友 */
    QString currentUserID;
    QString currentUserEmail;
    ItemDelegate *m_delegate;
    Ui::SimpleChat *ui;
    QWebSocket *socket;
    QSqlDatabase db;
    QList<User*> users;
    QStandardItemModel *userModel;
    void showEvent(QShowEvent*);
    void getUserList();
//    void keyPressEvent(QKeyEvent *e);
    void loadMessage();
    void writeDatabase(QString);
    void resizeEvent(QResizeEvent *event);
};

#endif // SIMPLECHAT_H
