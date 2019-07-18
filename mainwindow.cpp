#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "page.h"
#include <QLabel>
#include <QGroupBox>
#include <QRadioButton>
#include <QJsonObject>
#include<QJsonDocument>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    webSocket = new QWebSocket();
    ui->setupUi(this);
    centralWidget = new QWidget(this);
    connect(webSocket, &QWebSocket::connected, this, &MainWindow::onConnected);
    connect(webSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onConnectError(QAbstractSocket::SocketError)));

    stackedWidget = new QStackedWidget;

    /* 1. 歡迎畫面 */
    Page *page1 = new Page;

    QLabel *page1_info = new QLabel;
    page1_info->setText("<h1>MumiChat</h1>"
                  "<p>Welcome to use offical MumiChat Desktop app.</p>");
    page1_info->setAlignment(Qt::AlignCenter);
    startMessaging = new QPushButton("Start Messaging");
    connect(startMessaging, SIGNAL(clicked()), this, SLOT(nextPage()));
    page1->box->addWidget(page1_info);
    page1->box->addWidget(startMessaging);
    stackedWidget->addWidget(page1);


    /* 2. 伺服器連接頁面 */
    Page *connectServer = new Page;
    QLabel *connectServer_info = new QLabel;
    /* 連接伺服器說明屬性 */
    connectServer_info->setText("<h2>Connect to server</h2>"
                                "<p>Oops, it seems to be that you haven't establish a connection with server.</p>");
    connectServer_info->setWordWrap(true);
    connectServer_info->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    /* radiobutton 的 groupbox */
    QGroupBox *groupBox = new QGroupBox(tr("Websockets type"));
    QRadioButton *ws = new QRadioButton(tr("WS"));
    QRadioButton *wss = new QRadioButton(tr("WSS"));
    QPushButton *connectButton = new QPushButton(tr("Connect"));

    QVBoxLayout *radioButtonsBox = new QVBoxLayout;
    QHBoxLayout *hosts = new QHBoxLayout;

    errMsg = new QLabel;
    ip = new QLineEdit;
    port = new QLineEdit;

    ws->setChecked(true);

    /* 錯誤訊息欄設定 */
    errMsg->setStyleSheet("QLabel { color : #ff0000; }");
    errMsg->setText("Failed to connect server.");
    errMsg->hide();

    /* ip, port 屬性設定 */
    ip->setPlaceholderText("IP");
    port->setValidator(new QIntValidator(0, 65535, this));
    port->setPlaceholderText("Port");

    /* 連線類型放入 radioButtonBox 這個垂直佈局 */
    radioButtonsBox->addWidget(ws);
    radioButtonsBox->addWidget(wss);

    /* 把單選方塊的 GroupBox 佈局設成放單選方塊的垂直佈局 radioButtonBox */
    groupBox->setLayout(radioButtonsBox);
    groupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    /* 把 ip 和 port 放進 hosts 這個水平佈局 */
    hosts->setSpacing(5);
    hosts->addWidget(ip);
    hosts->addWidget(port);

    /* 設定 ip 和 port 的比例為 2:1 */
    hosts->setStretchFactor(ip, 2);
    hosts->setStretchFactor(port, 1);

    /* 把所有元素放入頁面中 */
    connectServer->box->addWidget(connectServer_info);
    connectServer->box->addWidget(groupBox);
    connectServer->box->addWidget(errMsg);
    connectServer->box->addLayout(hosts);
    connectServer->box->addWidget(connectButton);
    stackedWidget->addWidget(connectServer);

    /* radiobox 信號槽連接 */
    connect(groupBox, SIGNAL(clicked()), this, SLOT(setConnectionType()));
    /* conntect 按鈕連接 */
    connect(connectButton, SIGNAL(clicked()), this, SLOT(serverNextPage()));


    /* 3. 登入頁面 */
    Page *loginPage = new Page;

    loginButton = new QPushButton("Login");
    showRegisterPageButton = new QPushButton("Register");
    QLabel *loginPage_info = new QLabel;
    loginPage_info->setText("<h2>Login</h2>"
                        "Enter your Email and password.");
    loginError = new QLabel;
    regSuccess = new QLabel;

    /* 登入錯誤訊息 */
    loginError->setText("User not found.");
    loginError->setStyleSheet("QLabel { color : #ff0000; }");
    loginError->hide();

    /* 註冊成功訊息 */
    regSuccess->setText("Register successful! Now you can login.");
    regSuccess->setStyleSheet("QLabel { color : #00ff00; }");
    regSuccess->hide();

    email = new QLineEdit;
    password = new QLineEdit;
    password->setEchoMode(QLineEdit::Password);
    password->setPlaceholderText("Password");
    email->setPlaceholderText("Email");

    /* 添加元件 */
    loginPage->box->addWidget(loginPage_info);
    loginPage->box->addWidget(regSuccess);
    loginPage->box->addWidget(email);
    loginPage->box->addWidget(password);
    loginPage->box->addWidget(loginError);
    loginPage->box->addWidget(loginButton);
    loginPage->box->addWidget(showRegisterPageButton);

    /* 綁定槽函數 */
    connect(loginButton, SIGNAL(clicked()), this, SLOT(userLogin()));
    connect(showRegisterPageButton, SIGNAL(clicked()), this, SLOT(showRegisterPage()));

    stackedWidget->addWidget(loginPage);

    /* 4. 註冊頁面 */
    Page *registerPage = new Page;
    reg_err1 = new QLabel;
    QLabel *register_info = new QLabel;
    QPushButton *nextBtn = new QPushButton("Next");

    /* 元件屬性 */
    register_info->setText("<h2>Register</h2>"
                           "<p>All fields below are required.");
    reg_err1->setText("All fields are required!");
    reg_err1->setStyleSheet("QLabel { color : #ff0000; }");
    reg_err1->hide();

    /* 註冊頁面元件 */
    reg_email = new QLineEdit;
    reg_password = new QLineEdit;
    reg_con_password = new QLineEdit;
    firstName = new QLineEdit;
    lastName = new QLineEdit;
    registerButton = new QPushButton("Submit");

    /* 元件屬性設定 */
    reg_email->setPlaceholderText("Email");
    firstName->setPlaceholderText("First Name");
    lastName->setPlaceholderText("Last Name");
    reg_password->setPlaceholderText("Password");
    reg_con_password->setPlaceholderText("Confirm Password");

    reg_password->setEchoMode(QLineEdit::Password);
    reg_con_password->setEchoMode(QLineEdit::Password);

    /* 放置元件 */
    registerPage->box->addWidget(register_info);
    registerPage->box->addWidget(reg_err1);
    registerPage->box->addWidget(reg_email);
    registerPage->box->addWidget(firstName);
    registerPage->box->addWidget(lastName);
    registerPage->box->addWidget(nextBtn);

    /* 信號槽綁定 */
    connect(nextBtn, SIGNAL(clicked()), this, SLOT(nextRegisterPage()));

    stackedWidget->addWidget(registerPage);

    /* 5. 註冊頁面 2 */
    Page *registerPage2 = new Page;
    reg_err2 = new QLabel;
    QLabel *register_info2 = new QLabel;

    /* QLabel 屬性設定 */
    reg_err2->setStyleSheet("QLabel { color : #ff0000; }");
    reg_err2->setText("All fields are required!");
    reg_err2->hide();
    register_info2->setText("<h2>Register</h2>"
                           "<p>Enter your password.");

    /* 添加元件 */
    registerPage2->box->addWidget(register_info2);
    registerPage2->box->addWidget(reg_err2);
    registerPage2->box->addWidget(reg_password);
    registerPage2->box->addWidget(reg_con_password);
    registerPage2->box->addWidget(registerButton);

    /* 連接槽函數 */
    connect(registerButton, SIGNAL(clicked()), this, SLOT(userRegister()));

    stackedWidget->addWidget(registerPage2);


    /* 6. 聊天室窗口 */
//    chatMainWindow = new CHATMainWindow;
    simpleChat = new SimpleChat;
    simpleChat->setSocket(webSocket);
//    chatMainWindow = new ChatMainWindow;
//    connect(chatMainWindow, SIGNAL(rejected()), this, SLOT(show()));
    stackedWidget->addWidget(simpleChat);


    // StackedWidget 的容器
    QVBoxLayout *full = new QVBoxLayout(centralWidget);
    full->addWidget(stackedWidget);
    this->setCentralWidget(centralWidget);
}
bool MainWindow::isLogin()
{
    return false;
}
/* 註冊頁面換下一頁 */
void MainWindow::nextRegisterPage()
{
    /* 驗證欄位是否為空 */
    if(reg_email->text() != "" && firstName->text() != "" && lastName->text() != "")
    {
        reg_err1->hide();
        nextPage();
    }
    else {
        reg_err1->show();
    }
}
/* 發送註冊用戶的函式 */
void MainWindow::userRegister()
{
    /* 是否有空欄位 */
    if(reg_password->text() == "" || reg_con_password->text() == "")
    {
        reg_err2->setText("All fields are required!");
        reg_err2->show();
    } else if(reg_password->text() != reg_con_password->text())
    {
        reg_err2->setText("Password is not same.");
        reg_err2->show();
    }
    else {
        QJsonObject json;
        json["type"] = "action";
        json["action"] = "register";
        QJsonObject data;
        data["email"] = reg_email->text();
        data["password"] = reg_password->text();
        data["firstName"] = firstName->text();
        data["lastName"] = lastName->text();
        json["data"] = data;
        QJsonDocument doc(json);
        qDebug() << "login";
        qDebug() << doc.toJson();
        webSocket->sendTextMessage(doc.toJson());
    }
}
/* 顯示註冊頁面 */
void MainWindow::showRegisterPage()
{
    /* 跳到註冊頁面 */
    this->nextPage();
}
/* 當收到錯誤回傳時的錯誤狀態更新 */
void MainWindow::updateErrorStatus(int errCode)
{
//    loginError->show();
    qDebug() << errCode;
    if(errCode == 10000)
    {
        loginError->setText("User not found.");
        loginError->show();
    }
    else if (errCode == 10005) {
        loginError->setText("Multiple user login.");
        loginError->show();
    }
    else if(errCode == 10003)
    {
        reg_err2->hide();
        reg_err1->setText("The Email has been registered before.");
        reg_err1->show();
        /* 跳回註冊頁面 */
        this->stackedWidget->setCurrentIndex(3);
        page = 3;
    }
}
/* 當請求成功時的狀態處理 */
void MainWindow::updateSuccessStatus(int code)
{
    /* 登入成功 */
    if(code == 202)
    {
        /* 跳到聊天界面 */
        this->stackedWidget->setCurrentIndex(5);
        page = 5;
        qDebug("login success");
    } else if (code == 203)
    {
        reg_err1->hide();
        reg_err2->hide();
        regSuccess->show();
        /* 回到登入界面 */
        this->stackedWidget->setCurrentIndex(2);
        page = 2;
    }
}
/* 把登入請求發給後端 */
void MainWindow::userLogin()
{
    QJsonObject json;
    json["type"] = "action";
    json["action"] = "login";
    QJsonObject data;
    data["email"] = email->text();
    data["password"] = password->text();
    json["data"] = data;
    QJsonDocument doc(json);
    qDebug() << "login";
    qDebug() << doc.toJson();
    webSocket->sendTextMessage(doc.toJson());
}
void MainWindow::isUserExist()
{
    QJsonObject json;
    json["type"] = "action";
    json["action"] = "query";
    QJsonObject data;
    data["email"] = email->text();
    json.insert("data", data);
    QJsonDocument doc(json);
    qDebug() << doc.toJson();
    webSocket->sendTextMessage(doc.toJson(QJsonDocument::Compact));
}
/* 當收到後端傳的訊息 */
void MainWindow::onTextMessageReceived(QString data)
{
    qDebug() << data;
    /* 把 json 字串轉物件 */
    QJsonDocument doc =  QJsonDocument::fromJson(data.toLocal8Bit().data());
    QJsonObject json = doc.object();

    /* 是否初次連線所傳的值 */
    if(json["key"].toString() == NULL)
    {
        /* code > 10000 為錯誤 */
        if(json["code"].toInt() < 10000)
        {
            // 判斷是否為查詢結果，若為查詢結果 data 會是陣列
            if(json["data"].isArray())
            {
                /* 查詢使用者成功 */
                QJsonArray users = json["data"].toArray();
                simpleChat->FriendList(users);

            } else
            {
                /* 登入註冊成功 */
                updateSuccessStatus(json["code"].toInt());
            }

        } else
        {
            /* 錯誤處理 */
            qDebug()<<"code: " << json["code"];
            qDebug() << "code convert: " << json["code"].toInt();
            updateErrorStatus(json["code"].toInt());
        }
    } else {
        qDebug() << json["key"];
    }
}
/* 當 Websocket 成功連線 */
void MainWindow::onConnected()
{
    qDebug("Connect success");
    errMsg->hide();
    this->connected = true;
    connect(webSocket, &QWebSocket::textMessageReceived,
                this, &MainWindow::onTextMessageReceived);
    if(isLogin())
    {
        stackedWidget->setCurrentIndex(3);
        page = 3;
    }
    else {
        this->stackedWidget->setCurrentIndex(2);
        page = 2;
    }
}
void MainWindow::onConnectError(QAbstractSocket::SocketError)
{
    qDebug("error");
    this->connected = false;
    errMsg->show();
    this->stackedWidget->setCurrentIndex(1);
}
void MainWindow::establishConnection()
{
    qDebug("connect");
    QString location;
    if(ws == 0)
    {
        location = "ws://"+ip->text()+":"+port->text();
    }
    else {
        location = "wss://"+ip->text()+":"+port->text();
    }
    webSocket->open(QUrl(location));
}
void MainWindow::showChatWindow()
{
    this->hide();
//    chatMainWindow->show();
}
void MainWindow::nextPage()
{
    this->stackedWidget->setCurrentIndex(++page);
}
void MainWindow::serverNextPage()
{
    if(connected)
    {
        page = 2;
        this->stackedWidget->setCurrentIndex(2);
    }
    else {
        establishConnection();
    }
}
void MainWindow::setConnectionType()
{
    QRadioButton *radio = qobject_cast<QRadioButton *>(sender());
    qDebug() << radio->text();
//    if(id == 0)
//    {
//        ws = 1;
//    }
//    else {
//        ws = 0;
//    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
