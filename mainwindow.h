#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QSizePolicy>
#include <QStackedWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QtWebSockets/QWebSocket>
#include <QLineEdit>
#include <QLabel>
#include <QtSql>
#include "chatmainwindow.h"
#include "chatmessage.h"
#include "simplechat.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool isLogin = false;

private slots:
    void showChatWindow();
    void nextPage();
    void serverNextPage();
    void setConnectionType();
    void establishConnection();
    void onConnected();
    void onConnectError(QAbstractSocket::SocketError);
    void onTextMessageReceived(QString);
    void userLogin();
    void showRegisterPage();
    void nextRegisterPage();
    void userRegister();
private:
    Ui::MainWindow *ui;
    int page = 0;
    bool ws = 0;
    bool connected = 0;
    void isUserExist();
    void sendMessage(QString);
    void updateErrorStatus(int);
    void updateSuccessStatus(int);
    void writeDatabase(QJsonObject);
    void initDatabase();
    QSqlDatabase db;
    QWebSocket *webSocket;
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QPushButton *loginButton;
    QPushButton *showRegisterPageButton;
    QPushButton *registerButton;
    QPushButton *serverNextButton;
    QPushButton *startMessaging;
    /* error msg */
    QLabel *errMsg;
    QLabel *loginError;
    QLabel *reg_err1;
    QLabel *reg_err2;
    /* success msg */
    QLabel *regSuccess;
    /* input box */
    QLineEdit *email;
    QLineEdit *password;
    QLineEdit *ip;
    QLineEdit *port;
    QLineEdit *reg_email, *reg_password, *reg_con_password, *firstName, *lastName;
    /* chat window */
    CHATMainWindow *chatMainWindow;
    SimpleChat *simpleChat;
};

#endif // MAINWINDOW_H
