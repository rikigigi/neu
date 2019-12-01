#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define N_NEUR 30

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QList>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QTransform>
#include <QPainterPath>
#include <QGraphicsPathItem>
#include <neur.h>


typedef kohonen<2,N_NEUR,1> koh_2_100;

namespace Ui {
class MainWindow;
}

/*class kohonen : public QObject : public koh_2_100{
    Q_OBJECT
private:
};*/

class Grafico : public QGraphicsScene {
    Q_OBJECT
public:
    Grafico(koh_2_100 *r, QObject *parent = 0);
    void koho_run(unsigned int,float,float);
    koh_2_100 * rete;
    QGraphicsLineItem lin[N_NEUR-1];
private:
//    QList<QGraphicsItem*> idx;
    float tmp[2];
    QList<QGraphicsItem*> punti;
    void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
};

class Punto : public QGraphicsItem {
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startButton_clicked();


private:
    Ui::MainWindow *ui;
    Grafico *grafico;
};



#endif // MAINWINDOW_H
