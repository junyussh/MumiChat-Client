#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QSizePolicy>
#include "loginui.h"
#include "register.h"
#include "chatmainwindow2.h"
#include <QStackedWidget>
#include <QPushButton>
#include <QSpinBox>
#include<QtWebSockets/QWebSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    ChatMainWindow *chatMainWindow;
    bool isLogin();
    Ui::MainWindow *ui;
    int page = 0;
    bool ws = 0;
    bool connected = 0;
    void isUserExist();
    void sendMessage(QString);
    void updateErrorStatus(int);
    void updateSuccessStatus(int);
    QWebSocket *webSocket;
    QWidget *centralWidget;
    LoginUI *loginUI;
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
};

#endif // MAINWINDOW_H
