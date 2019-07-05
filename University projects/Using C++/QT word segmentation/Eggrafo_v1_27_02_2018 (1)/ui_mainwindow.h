/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionInv;
    QAction *actionLine_Split;
    QAction *actionLine_Split_Detailed;
    QAction *actionWord_Split;
    QAction *actionWord_Split_Detailed;
    QAction *actionLines_Batch;
    QAction *actionWords_Batch;
    QAction *actionHorizontal_Rlsa;
    QAction *actionBatch_Process;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QGraphicsView *graphicsView_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuProc;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(691, 390);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionInv = new QAction(MainWindow);
        actionInv->setObjectName(QStringLiteral("actionInv"));
        actionLine_Split = new QAction(MainWindow);
        actionLine_Split->setObjectName(QStringLiteral("actionLine_Split"));
        actionLine_Split_Detailed = new QAction(MainWindow);
        actionLine_Split_Detailed->setObjectName(QStringLiteral("actionLine_Split_Detailed"));
        actionWord_Split = new QAction(MainWindow);
        actionWord_Split->setObjectName(QStringLiteral("actionWord_Split"));
        actionWord_Split_Detailed = new QAction(MainWindow);
        actionWord_Split_Detailed->setObjectName(QStringLiteral("actionWord_Split_Detailed"));
        actionLines_Batch = new QAction(MainWindow);
        actionLines_Batch->setObjectName(QStringLiteral("actionLines_Batch"));
        actionWords_Batch = new QAction(MainWindow);
        actionWords_Batch->setObjectName(QStringLiteral("actionWords_Batch"));
        actionHorizontal_Rlsa = new QAction(MainWindow);
        actionHorizontal_Rlsa->setObjectName(QStringLiteral("actionHorizontal_Rlsa"));
        actionBatch_Process = new QAction(MainWindow);
        actionBatch_Process->setObjectName(QStringLiteral("actionBatch_Process"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 2);

        graphicsView_2 = new QGraphicsView(centralWidget);
        graphicsView_2->setObjectName(QStringLiteral("graphicsView_2"));

        gridLayout->addWidget(graphicsView_2, 0, 2, 1, 2);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 1, 1, 1, 1);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 1, 2, 1, 1);

        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 1, 3, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 0, 1, 4);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 691, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuProc = new QMenu(menuBar);
        menuProc->setObjectName(QStringLiteral("menuProc"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuProc->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuProc->addAction(actionInv);
        menuProc->addAction(actionLine_Split);
        menuProc->addAction(actionWord_Split);
        menuProc->addAction(actionHorizontal_Rlsa);
        menuProc->addAction(actionBatch_Process);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        actionInv->setText(QApplication::translate("MainWindow", "Inv", Q_NULLPTR));
        actionLine_Split->setText(QApplication::translate("MainWindow", "Line Split", Q_NULLPTR));
        actionLine_Split_Detailed->setText(QApplication::translate("MainWindow", "Line Split Detailed", Q_NULLPTR));
        actionWord_Split->setText(QApplication::translate("MainWindow", "Word Split", Q_NULLPTR));
        actionWord_Split_Detailed->setText(QApplication::translate("MainWindow", "Word Split Detailed", Q_NULLPTR));
        actionLines_Batch->setText(QApplication::translate("MainWindow", "Lines Batch", Q_NULLPTR));
        actionWords_Batch->setText(QApplication::translate("MainWindow", "Words  Batch", Q_NULLPTR));
        actionHorizontal_Rlsa->setText(QApplication::translate("MainWindow", "Horizontal Rlsa", Q_NULLPTR));
        actionBatch_Process->setText(QApplication::translate("MainWindow", "Batch Process", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "-", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "+", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "1:1", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "FitToPage", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuProc->setTitle(QApplication::translate("MainWindow", "Proc", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
