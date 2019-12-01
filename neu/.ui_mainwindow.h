/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>
#elif QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtWidgets>
#endif

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QSpinBox *Niter;
    QDoubleSpinBox *sigma;
    QLabel *label;
    QDoubleSpinBox *sigma_f;
    QRadioButton *slin;
    QRadioButton *sexp;
    QProgressBar *progressBar;
    QDoubleSpinBox *k;
    QLabel *label_2;
    QDoubleSpinBox *k_f;
    QRadioButton *klin;
    QRadioButton *kexp;
    QPushButton *startButton;
    QGraphicsView *graphicsView;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(591, 365);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Niter = new QSpinBox(centralWidget);
        Niter->setObjectName(QString::fromUtf8("Niter"));
        Niter->setMinimum(1);
        Niter->setMaximum(9999);
        Niter->setValue(100);

        gridLayout->addWidget(Niter, 0, 0, 1, 1);

        sigma = new QDoubleSpinBox(centralWidget);
        sigma->setObjectName(QString::fromUtf8("sigma"));
        sigma->setDecimals(6);
        sigma->setMinimum(1e-06);
        sigma->setSingleStep(0.1);
        sigma->setValue(10);

        gridLayout->addWidget(sigma, 0, 1, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 2, 1, 1);

        sigma_f = new QDoubleSpinBox(centralWidget);
        sigma_f->setObjectName(QString::fromUtf8("sigma_f"));
        sigma_f->setDecimals(6);
        sigma_f->setMinimum(1e-06);
        sigma_f->setSingleStep(0.1);
        sigma_f->setValue(1);

        gridLayout->addWidget(sigma_f, 0, 3, 1, 1);

        slin = new QRadioButton(centralWidget);
        buttonGroup_2 = new QButtonGroup(MainWindow);
        buttonGroup_2->setObjectName(QString::fromUtf8("buttonGroup_2"));
        buttonGroup_2->addButton(slin);
        slin->setObjectName(QString::fromUtf8("slin"));
        slin->setChecked(false);
        slin->setAutoExclusive(true);
        slin->setAutoRepeatDelay(0);
        slin->setAutoRepeatInterval(0);

        gridLayout->addWidget(slin, 0, 4, 1, 1);

        sexp = new QRadioButton(centralWidget);
        buttonGroup_2->addButton(sexp);
        sexp->setObjectName(QString::fromUtf8("sexp"));
        sexp->setChecked(true);
        sexp->setAutoRepeat(false);
        sexp->setAutoExclusive(true);
        sexp->setAutoRepeatDelay(0);
        sexp->setAutoRepeatInterval(0);

        gridLayout->addWidget(sexp, 0, 5, 1, 1);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 1, 0, 1, 1);

        k = new QDoubleSpinBox(centralWidget);
        k->setObjectName(QString::fromUtf8("k"));
        k->setDecimals(6);
        k->setMinimum(1e-06);
        k->setSingleStep(0.01);
        k->setValue(1);

        gridLayout->addWidget(k, 1, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 2, 1, 1);

        k_f = new QDoubleSpinBox(centralWidget);
        k_f->setObjectName(QString::fromUtf8("k_f"));
        k_f->setDecimals(6);
        k_f->setMinimum(1e-06);
        k_f->setSingleStep(0.01);
        k_f->setValue(0.02);

        gridLayout->addWidget(k_f, 1, 3, 1, 1);

        klin = new QRadioButton(centralWidget);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(klin);
        klin->setObjectName(QString::fromUtf8("klin"));
        klin->setChecked(false);
        klin->setAutoExclusive(true);
        klin->setAutoRepeatDelay(0);
        klin->setAutoRepeatInterval(0);

        gridLayout->addWidget(klin, 1, 4, 1, 1);

        kexp = new QRadioButton(centralWidget);
        buttonGroup->addButton(kexp);
        kexp->setObjectName(QString::fromUtf8("kexp"));
        kexp->setChecked(true);
        kexp->setAutoExclusive(true);
        kexp->setAutoRepeatDelay(0);
        kexp->setAutoRepeatInterval(0);

        gridLayout->addWidget(kexp, 1, 5, 1, 1);

        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setEnabled(true);

        gridLayout->addWidget(startButton, 2, 1, 1, 3);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMouseTracking(false);
        graphicsView->setAcceptDrops(false);

        gridLayout_2->addWidget(graphicsView, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Reti neurali", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        Niter->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Numero di iterazioni</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        sigma->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>valore iniziale di sigma</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Il peso per il neurone <span style=\" color:#55aa00;\">i</span> quando vince il neurone <span style=\" color:#55aa00;\">i</span><span style=\" color:#55aa00; vertical-align:sub;\">0</span> \303\250 implementato nel programma con la formula:</p><p align=\"center\"><span style=\" font-size:11pt; color:#55aa00;\">k*exp(-(i-i</span><span style=\" font-size:11pt; color:#55aa00; vertical-align:sub;\">0</span><span style=\" font-size:11pt; color:#55aa00;\">)</span><span style=\" font-size:11pt; color:#55aa00; vertical-align:super;\">2</span><span style=\" font-size:11pt; color:#55aa00;\">/sigma)</span></p><p>dove <span style=\" color:#55aa00;\">k</span> e <span style=\" color:#55aa00;\">sigma</span> sono date dall'utente</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("MainWindow", "sigma", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sigma_f->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>valore finale di sigma</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        slin->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>andamento lineare</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        slin->setText(QApplication::translate("MainWindow", "lin", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sexp->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>andamento esponenziale</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        sexp->setText(QApplication::translate("MainWindow", "exp", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        k->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>valore iniziale di k </p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_2->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Il peso per il neurone <span style=\" color:#55aa00;\">i</span> quando vince il neurone <span style=\" color:#55aa00;\">i</span><span style=\" color:#55aa00; vertical-align:sub;\">0</span> \303\250 implementato nel programma con la formula:</p><p align=\"center\"><span style=\" font-size:11pt; color:#55aa00;\">k*exp(-(i-i</span><span style=\" font-size:11pt; color:#55aa00; vertical-align:sub;\">0</span><span style=\" font-size:11pt; color:#55aa00;\">)</span><span style=\" font-size:11pt; color:#55aa00; vertical-align:super;\">2</span><span style=\" font-size:11pt; color:#55aa00;\">/sigma)</span></p><p>dove <span style=\" color:#55aa00;\">k</span> e <span style=\" color:#55aa00;\">sigma</span> sono date dall'utente</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("MainWindow", "k", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        k_f->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>valore finale di k</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        klin->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>andamento lineare</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        klin->setText(QApplication::translate("MainWindow", "lin", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        kexp->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>andamento esponenziale</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        kexp->setText(QApplication::translate("MainWindow", "exp", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        startButton->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Inizia la simulazione</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        startButton->setText(QApplication::translate("MainWindow", "start", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
