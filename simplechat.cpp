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
    ui->gridLayout->setSpacing(0);
    ui->MessageBox->setPlaceholderText("Write a message…");
    QPixmap pix(":/images/icon/link.png");
    QPixmap dest=pix.scaled(ui->attachment->size(),Qt::KeepAspectRatio);
    ui->attachment->setScaledContents(true);
    ui->attachment->setPixmap(dest);
    chat = new CHATMainWindow(this);
    /* 好友列表點擊 */
    connect(ui->UserList, SIGNAL(clicked(QModelIndex)), this, SLOT(listClicked(QModelIndex)));
    /* 發送訊息訊號 */
    connect(chat, SIGNAL(sendMessage(QString)), this, SLOT(sendMessage(QString)));
    int startX = ui->UserList->x()+ui->UserList->width();
    int startY = ui->UserList->y()-ui->Name->height();
    ui->attachment->hide();

    int width = ui->listWidget->width();
    int height = ui->listWidget->height()+ui->MessageBox->height();
    chat->setGeometry(271, 66, width, height);
    chat->show();
    chat->hideWidget();
}
//void SimpleChat::keyPressEvent(QKeyEvent *event)
//{
//    if(event->modifiers() == Qt::ControlModifier && (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter))
//    {
//        sendMessage();
//    }
//}
void SimpleChat::sendMessage(QString message)
{
    QJsonObject json, data;
    json["type"] = "message";
    data["recipient"] = currentUserID;
    data["content"] = message;
    json["data"] = data;
    writeDatabase(message);
    QJsonDocument doc(json);
    qDebug() << "send: " << doc.toJson(QJsonDocument::Compact);
    socket->sendTextMessage(doc.toJson(QJsonDocument::Compact));
    ui->MessageBox->clear();
}
/* 點擊好友清單 */
void SimpleChat::listClicked(QModelIndex index)
{
    QVariant variant = index.data(Qt::UserRole+1);
    User data = variant.value<User>();
    ui->Name->setText(data.firstName+" "+data.lastName);
    if(currentUserID != data.ID)
    {
        chat->clearMessage();
        currentUserID = data.ID;
        currentUserEmail = data.Email;
        loadMessage();
    }
    qDebug() << "current userid: " << currentUserID;
    chat->showWidget();
}
/* 載入訊息 */
void SimpleChat::loadMessage()
{
    QSqlQuery selectQuery(db);
    /* 一般訊息獲取 */
    QString sql = QString("select * from message where (sender='%1' and recipient='%2') or (sender='%3' and recipient='%4')")
            .arg(loginUserID)
            .arg(currentUserID)
            .arg(currentUserID)
            .arg(loginUserID);

    qDebug() << sql;
    selectQuery.exec(sql);
    while (selectQuery.next())
    {
        qDebug() << QString("sender: %1, recipient: %2, content: %3, created_at: %4")
                    .arg(selectQuery.value("sender").toString())
                    .arg(selectQuery.value("recipient").toString())
                    .arg(selectQuery.value("content").toString())
                    .arg(selectQuery.value("created_at").toString());
        bool isMe = selectQuery.value("sender").toString() == loginUserID;
        chat->drawMessage(selectQuery.value("content").toString(), selectQuery.value("created_at").toString(), isMe);
    }
}
/* 設定資料庫 */
void SimpleChat::setDB(QSqlDatabase _db)
{
    this->db = _db;
}
void SimpleChat::setSocket(QWebSocket *socket)
{
    this->socket = socket;
}
/* 當顯示畫面時的事件 */
void SimpleChat::showEvent(QShowEvent *)
{
//    ui->UserList->removeAl
//    ui->UserList->setStringList(QStringList{});
    this->getUserList();
    m_delegate = new ItemDelegate(this);
    ui->UserList->setItemDelegate(m_delegate);
    qDebug() << loginUser;
    ui->Username->setText(loginUser);
    qDebug() << "set done";
    QPixmap pix = QPixmap(":/images/icon/CustomerCopy.png");

    ui->Profile->setPixmap(pix.scaled(ui->Profile->size(),Qt::KeepAspectRatio));
}
/* 獲取所有使用者 */
void SimpleChat::getUserList()
{
    QJsonObject json;
    json["type"] = "action";
    json["action"] = "query";
    QJsonObject data;
    json.insert("data", data);
    QJsonDocument doc(json);
//    qDebug() << doc.toJson();
    socket->sendTextMessage(doc.toJson(QJsonDocument::Compact));
}
void SimpleChat::setLoginUser(QString email)
{
    loginUser = email;
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

        if(obj["email"].toString() == loginUser)
        {
            loginUserID = obj["id"].toString();
            continue;
        }
        if(obj["isLogin"] == false)
        {
            continue;
        }
        struct User *user = new User;
        user->ID = obj["id"].toString();
        user->Email = obj["email"].toString();
        user->firstName = obj["firstName"].toString();
        user->lastName = obj["lastName"].toString();
        user->isLogin = obj["isLogin"].toBool();
        this->users.append(user);
        Manager.insert(user->ID, user);
        userItem->setData(QVariant::fromValue<User>(*user),Qt::UserRole+1);
        userModel->appendRow(userItem);
        i++;
    }
    ui->UserList->setModel(userModel);
    ui->UserList->setItemDelegate(m_delegate);
}
/* 將發送的訊息存入資料庫 */
void SimpleChat::writeDatabase(QString message)
{
    QSqlQuery insertQuery(db);
    QString time = QDateTime::currentDateTime().toString(Qt::ISODate);
    QString sql = QString("INSERT INTO message(sender, recipient, content, created_at) VALUES ('%1', '%2', '%3', '%4')")
            .arg(loginUserID)
            .arg(currentUserID)
            .arg(message)
            .arg(time);
    qDebug() << message;
    insertQuery.exec(sql);
}
void SimpleChat::resizeEvent(QResizeEvent *event)
{
    int width = ui->listWidget->width();
    int height = ui->listWidget->height()+ui->MessageBox->height();
    chat->setGeometry(270, 63, width, height);
}
SimpleChat::~SimpleChat()
{
    delete ui;
}
