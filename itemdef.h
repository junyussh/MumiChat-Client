#ifndef ITEMDEF_H
#define ITEMDEF_H

#include <QMetaType>
#include <QString>
#include <QPixmap>
typedef enum{
    S_RED,
    S_BLUE,
    S_YELLOW,
} ItemStatus;

struct User {
    QString firstName;
    QString lastName;
    QString Email;
    QString ID;
    bool isLogin;
};

Q_DECLARE_METATYPE(User)

#endif // ITEMDEF_H
