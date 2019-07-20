#include "itemdelegate.h"

#include <QPainter>
#include <QStyledItemDelegate>
#include <QStyle>
#include <QEvent>
#include <QDebug>
#include "itemdef.h"

ItemDelegate::ItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

ItemDelegate::~ItemDelegate()
{

}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.isValid())
    {
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //消锯齿
        ItemStatus status = (ItemStatus)(index.data(Qt::UserRole).toInt());

        QVariant variant = index.data(Qt::UserRole+1);
        User data = variant.value<User>();

        QStyleOptionViewItem viewOption(option);//用来在视图中画一个item

        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth( option.rect.width()-1);
        rect.setHeight(option.rect.height()-1);

        //QPainterPath画圆角矩形
        const qreal radius = 0;

        QRect area = QRect(option.rect);
        /*
        QPainterPath path;
        path.moveTo(rect.topRight() - QPointF(radius, 0));
        path.lineTo(rect.topLeft() + QPointF(radius, 0));
        path.quadTo(rect.topLeft(), rect.topLeft() + QPointF(0, radius));
        path.lineTo(rect.bottomLeft() + QPointF(0, -radius));
        path.quadTo(rect.bottomLeft(), rect.bottomLeft() + QPointF(radius, 0));
        path.lineTo(rect.bottomRight() - QPointF(radius, 0));
        path.quadTo(rect.bottomRight(), rect.bottomRight() + QPointF(0, -radius));
        path.lineTo(rect.topRight() + QPointF(0, radius));
        path.quadTo(rect.topRight(), rect.topRight() + QPointF(-radius, -0));
        */

        QColor SelectBGD = QColor(102, 184, 255);
        bool isSelect = false;
        bool isMouseOver = false;
        bool isNoAction = false;

        if(option.state.testFlag(QStyle::State_Selected))
        {
            painter->setPen(QPen(SelectBGD));
            painter->setBrush(SelectBGD);
            painter->drawRoundedRect(area, radius, radius);
            isSelect = true;
            isMouseOver = false;
            isNoAction = false;

        }
        else if(option.state.testFlag(QStyle::State_MouseOver))
        {
            painter->setPen(QPen(QColor(236, 236, 236)));
            painter->setBrush(QColor(236, 236, 236));
            painter->drawRoundedRect(area, radius, radius);
            isSelect = false;
            isMouseOver = true;
            isNoAction = false;
        }
        else{
            painter->setPen(QPen(Qt::white));
            painter->setBrush(Qt::white);
            painter->drawRoundedRect(area, radius, radius);
            isSelect = false;
            isMouseOver = false;
            isNoAction = true;
        }

        //绘制数据位置
        QRect avatarRect = QRect(rect.left() +10, rect.top()+5, rect.height() - 10, rect.height() - 10);
        QRect NameRect = QRect(avatarRect.right() +10, rect.top()+10, rect.width()-30, 20);
        //QRect circle = QRect(NameRect.right() - avatarRect.right(), rect.top()+10, 10, 10);
        QRect telRect = QRect(avatarRect.right() +10, rect.bottom()-25, rect.width()-10, 20);


        painter->drawPixmap(avatarRect, QPixmap(":/images/icon/user.png"));
        /*
        switch (status) {
        case S_RED:
            painter->setBrush(Qt::red);
            painter->setPen(QPen(Qt::red));
            break;
        case S_BLUE:
            painter->setBrush(Qt::blue);
            painter->setPen(QPen(Qt::blue));
            break;
        case S_YELLOW:
            painter->setBrush(Qt::yellow);
            painter->setPen(QPen(Qt::yellow));
            break;
        }

        painter->drawEllipse(circle);     //画圆圈
        */
        if(isSelect == true)
        {
            painter->setPen(QPen(Qt::white));
            painter->setFont(QFont("Microsoft JhengHei", 12, QFont::Bold));
            painter->drawText(NameRect,Qt::AlignLeft,data.firstName+" "+data.lastName); //绘制名字

            painter->setPen(QPen(Qt::white));
            painter->setFont(QFont("Microsoft JhengHei", 10));
            painter->drawText(telRect,Qt::AlignLeft,data.Email); //绘制最新訊息
            getUSERnameFromItem = data.Email;
            getEMAILFromItem = data.ID;
            //getAVATARFromItem = data.avatar;
        }
        if(isMouseOver == true || isNoAction == true)
        {
            painter->setPen(QPen(Qt::black));
            painter->setFont(QFont("Microsoft JhengHei", 12, QFont::Bold));
            painter->drawText(NameRect,Qt::AlignLeft,data.firstName+" "+data.lastName); //绘制名字

            painter->setPen(QPen(Qt::gray));
            painter->setFont(QFont("Microsoft JhengHei", 10));
            painter->drawText(telRect,Qt::AlignLeft,data.Email); //绘制最新訊息
        }


        painter->restore();
    }
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(160, 70);
}

QString ItemDelegate::getGetName()
{
    return getUSERnameFromItem;
}
QString ItemDelegate::getEMAIL()
{
    return getEMAILFromItem;
}
/*
QPixmap ItemDelegate::getAVATAR()
{
    return getAVATAR();
}
*/
