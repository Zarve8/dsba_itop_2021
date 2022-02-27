#include "aboutw.h"
#include "ui_aboutw.h"

#include<QPainterPath>

AboutW::AboutW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutW)
{
    ui->setupUi(this);
    setWindowTitle("");
    setFixedSize(400, 400);
}

AboutW::~AboutW()
{
    delete ui;
}

void AboutW::paintEvent(QPaintEvent *e){
    int scale  = 15;
    int cx = 120;
    int cy = 200;
    int rad = 7;
    int xspace = 26;
    int yspace = 26;
    QPainter painter(this);

    QPolygon poly1;
    poly1 << QPoint(cx, cy);
    poly1 << QPoint(cx + scale*7, cy);
    poly1 << QPoint(cx + scale*7, cy + scale*7);
    poly1 << QPoint(cx, cy + scale*7);

    QPolygon poly2;
    poly2 << QPoint(cx, cy);
    poly2 << QPoint(cx + scale*4, cy + scale*(-3));
    poly2 << QPoint(cx + scale*11, cy + scale*(-3));
    poly2 << QPoint(cx + scale*7, cy);

    QPolygon poly3;
    poly3 << QPoint(cx + scale*11, cy + scale*(-3));
    poly3 << QPoint(cx + scale*7, cy);
    poly3 << QPoint(cx + scale*7, cy + scale*7);
    poly3 << QPoint(cx + scale*11, cy + scale*4);


    QBrush fillbrush;
    fillbrush.setColor(Qt::green);
    fillbrush.setStyle(Qt::SolidPattern);

    QPainterPath path;
    path.addPolygon(poly1);
    path.addPolygon(poly2);
    path.addPolygon(poly3);

    painter.fillPath(path, fillbrush);

    painter.drawLine(cx, cy, cx + scale*7, cy);
    painter.drawLine(cx, cy, cx, cy + scale*7);
    painter.drawLine(cx + scale*7, cy, cx + scale*7, cy + scale*7);
    painter.drawLine(cx, cy + scale*7, cx + scale*7, cy + scale*7);

    painter.drawLine(cx, cy, cx + scale*4, cy + scale*(-3));
    painter.drawLine(cx + scale*4, cy + scale*(-3), cx + scale*11, cy + scale*(-3));
    painter.drawLine(cx + scale*11, cy + scale*(-3), cx + scale*7, cy);
    painter.drawLine(cx + scale*11, cy + scale*(-3), cx + scale*11, cy + scale*4);
    painter.drawLine(cx + scale*7, cy + scale*7, cx + scale*11, cy + scale*4);

    painter.setPen(Qt::white);
    QPoint p0(cx + scale*3.5, cy + scale*3.5);
    QPoint p1(cx + scale*3.5 - xspace, cy + scale*3.5);
    QPoint p2(cx + scale*3.5 - xspace, cy + scale*3.5 + yspace);
    QPoint p3(cx + scale*3.5 - xspace, cy + scale*3.5 - yspace);
    QPoint p4(cx + scale*3.5 + xspace, cy + scale*3.5);
    QPoint p5(cx + scale*3.5 + xspace, cy + scale*3.5 + yspace);
    QPoint p6(cx + scale*3.5 + xspace, cy + scale*3.5 - yspace);
    painter.drawEllipse(p1, rad, rad);
    painter.drawEllipse(p2, rad, rad);
    painter.drawEllipse(p3, rad, rad);
    painter.drawEllipse(p4, rad, rad);
    painter.drawEllipse(p5, rad, rad);
    painter.drawEllipse(p6, rad, rad);

    QPoint p11(cx + scale*9.25, cy + scale*2);
    painter.drawEllipse(p11, 6, rad);


    QPoint p31(cx + scale*5.5, cy + scale*(-1.5));
    QPoint p32(cx + scale*5.5 + xspace*1.75, cy + scale*(-1.5) - yspace*0.35);
    QPoint p33(cx + scale*5.5 - xspace*1.75, cy + scale*(-1.5) + yspace*0.35);
    painter.drawEllipse(p31, rad, 6);
    painter.drawEllipse(p32, rad, 6);
    painter.drawEllipse(p33, rad, 6);

    QWidget::paintEvent(e);

}
