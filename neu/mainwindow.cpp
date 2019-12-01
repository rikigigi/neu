#include "mainwindow.h"
#include "ui_mainwindow.h"

QRectF Punto::boundingRect() const {
    return QRectF(-2,-2,4,4);
}

void Punto::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawRect(QRectF(-2,-2,4,4));
}

void Grafico::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsItem *s=itemAt(mouseEvent->scenePos(),QTransform());
        if (s&& mouseEvent->button()==Qt::RightButton){
            removeItem(s);
            unsigned int idx=punti.indexOf(s);
            //punti.removeAt(idx);
            //rimuovo allo stesso modo in cui rimuovo il punto dagli input della rete per non scombinare gli indici
            punti.replace(idx,punti.last());
            punti.pop_back();
            // rimuovo il punto dagli input
            rete->remove_input(idx);
        }else if (mouseEvent->button()==Qt::LeftButton){
            Punto *p=new Punto;
            p->setPos(mouseEvent->scenePos());
            addItem(p);
            punti.append(p);
            tmp[0]=mouseEvent->scenePos().x();
            tmp[1]=mouseEvent->scenePos().y();
            rete->add_input(tmp);
        }
}

void Grafico::koho_run(unsigned int n, float e, float k){
    rete->run(n,e,k);

}

// legge la matrice dei pesi nelle linee disegnate sullo schermo
template<unsigned int n> class rete_lin {
public:
    static inline void A(QGraphicsLineItem *L,koh_2_100 *r){
        L[n-1].setLine(r->W(n,0),r->W(n,1),r->W(n-1,0),r->W(n-1,1));
        rete_lin<n-1>::A(L,r);
    }
};
template<> class rete_lin<1> {
public:
    static inline void A(QGraphicsLineItem *L,koh_2_100 *r){
        L[0].setLine(r->W(1,0),r->W(1,1),r->W(0,0),r->W(0,1));
    }
};

//aggiunge le linee
template<unsigned int n> class lin_agg {
public:
    static inline void A(QGraphicsLineItem *L,Grafico*g){
        g->addItem(&L[n]);
        lin_agg<n-1>::A(L,g);
    }
};
template<> class lin_agg<0> {
public:
    static inline void A(QGraphicsLineItem *L,Grafico*g){
        g->addItem(&L[0]);
    }
};

Grafico::Grafico(koh_2_100 *r, QObject *parent):QGraphicsScene(parent){
    rete=r;
    rete_lin<N_NEUR-1>::A(lin,rete);
    lin_agg<N_NEUR-2>::A(lin,this);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_cmwc4096();
    koh_2_100 *rete=new koh_2_100();
    grafico=new Grafico(rete);
    ui->graphicsView->setScene(grafico);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    float kf=ui->k_f->value(),ki=ui->k->value(),ef=ui->sigma_f->value(),ei=ui->sigma->value(),k,e,ak,bk,ae,be;
    bool klin=ui->klin->isChecked(),elin=ui->slin->isChecked();
    unsigned int cicli=ui->Niter->value();
    ui->startButton->setDisabled(true);
    if (!klin) {ak=expa(0.1,cicli,ki,kf);bk=expb(0.1,cicli,ki,kf);}
    if (!elin) {ae=expa(0.1,cicli,ei,ef);be=expb(0.1,cicli,ei,ef);}
    for (unsigned int i=0;i<cicli;i++){
            if (klin) {
                k=(kf-ki)*(float)i/(float)cicli + ki;
            } else {
                k=ak*exp(-bk*(float)i);
            }
            if (elin) {
                e=(ef-ei)*(float)i/(float)cicli + ei;
            } else {
                e=ae*exp(-be*(float)i);
            }
        ui->progressBar->setValue((float)i/ui->Niter->value()*100);
        grafico->koho_run(100,-e,k);
        rete_lin<N_NEUR-1>::A(grafico->lin,grafico->rete);
        QCoreApplication::processEvents();
    }
    ui->progressBar->setValue(100);
    ui->startButton->setDisabled(false);
}

