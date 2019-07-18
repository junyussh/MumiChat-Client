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
    void FriendList(QJsonArray);
    QMap<QString, User*> Manager;
private slots:
    void listClicked(QModelIndex);
private:
    ItemDelegate *m_delegate;
    Ui::SimpleChat *ui;
    QWebSocket *socket;
    QList<User*> users;
    QString currentUserID;
    QString currentUserEmail;
    QStandardItemModel *userModel;
    void showEvent(QShowEvent*);
    void getUserList();
};

#endif // SIMPLECHAT_H
