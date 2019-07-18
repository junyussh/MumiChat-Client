#include "simplechat.h"
#include "ui_simplechat.h"
#include<QVariant>

SimpleChat::SimpleChat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimpleChat)
{
    ui->setupUi(this);
    ui->UserList->setSpacing(0);
    ui->UserList->setDragEnabled(false);
    connect(ui->UserList, SIGNAL(clicked(QModelIndex)), this, SLOT(listClicked(QModelIndex)));
}
void SimpleChat::listClicked(QModelIndex index)
{
    QVariant variant = index.data(Qt::UserRole+1);
    User data = variant.value<User>();
    qDebug() << data.ID;
    qDebug() << data.Email;
}
void SimpleChat::setSocket(QWebSocket *socket)
{
    this->socket = socket;
}
void SimpleChat::showEvent(QShowEvent *)
{
//    ui->UserList->removeAl
//    ui->UserList->setStringList(QStringList{});
    this->getUserList();
    m_delegate = new ItemDelegate(this);
    ui->UserList->setItemDelegate(m_delegate);
}
void SimpleChat::getUserList()
{
    QJsonObject json;
    json["type"] = "action";
    json["action"] = "query";
    QJsonObject data;
    json.insert("data", data);
    QJsonDocument doc(json);
    qDebug() << doc.toJson();
    socket->sendTextMessage(doc.toJson(QJsonDocument::Compact));
}
void SimpleChat::FriendList(QJsonArray accounts)
{
    this->users.clear();
    this->Manager.clear();
    int i = 0;
    userModel = new QStandardItemModel;
    foreach (const QJsonValue & value, accounts) {
        QStandardItem *userItem = new QStandardItem;

        QJsonObject obj = value.toObject();

        struct User *user = new User;
        user->ID = obj["id"].toString();
        user->Email = obj["email"].toString();
        user->firstName = obj["firstName"].toString();
        user->lastName = obj["lastName"].toString();
        user->isLogin = obj["isLogin"].toBool();
        this->users.append(user);
        Manager.insert(user->ID, user);
//        struct User item;
//        item.ID = obj["id"].toString();
//        item.Email = obj["email"].toString();
//        item.firstName = obj["firstName"].toString();
//        item.lastName = obj["lastName"].toString();
//        item.isLogin = obj["isLogin"].toBool();

        userItem->setData(QVariant::fromValue<User>(*user),Qt::UserRole+1);
        userModel->appendRow(userItem);
        i++;
    }
    ui->UserList->setModel(userModel);
    ui->listView->setItemDelegate(m_delegate);
}
SimpleChat::~SimpleChat()
{
    delete ui;
}
