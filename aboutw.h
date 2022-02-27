#ifndef ABOUTW_H
#define ABOUTW_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class AboutW;
}

class AboutW : public QWidget
{
    Q_OBJECT

public:
    explicit AboutW(QWidget *parent = nullptr);
    ~AboutW();

private:
    Ui::AboutW *ui;
    void paintEvent(QPaintEvent *e);
};

#endif // ABOUTW_H
