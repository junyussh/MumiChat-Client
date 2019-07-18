#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
#include <QVBoxLayout>

class Page : public QWidget
{
    Q_OBJECT
public:
    explicit Page(QWidget *parent = nullptr);
    QVBoxLayout *box;

signals:

public slots:

private:
    void showEvent(QShowEvent *);
    QBoxLayout *layout;
    QWidget *child;
};

#endif // PAGE_H
