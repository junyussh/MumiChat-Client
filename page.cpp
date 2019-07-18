#include "page.h"
#include <QDebug>

void Page::showEvent(QShowEvent *)
{
}
Page::Page(QWidget *parent) : QWidget(parent)
{
    child = new QWidget(this);
    box = new QVBoxLayout(child);

    box->setAlignment(Qt::AlignCenter);
    box->setSpacing(40);
    child->setMaximumSize(QSize(300, height()));

    layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    layout->addWidget(child, Qt::AlignCenter);
}
