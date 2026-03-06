/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKOpenGLNativeWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionopen_File;
    QAction *actionItem_Options;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *leftLayout;
    QTreeView *treeView;
    QHBoxLayout *buttonLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QVTKOpenGLNativeWidget *vtkWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuItem;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 800);
        actionopen_File = new QAction(MainWindow);
        actionopen_File->setObjectName("actionopen_File");
        actionItem_Options = new QAction(MainWindow);
        actionItem_Options->setObjectName("actionItem_Options");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        leftLayout = new QVBoxLayout();
        leftLayout->setObjectName("leftLayout");
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName("treeView");

        leftLayout->addWidget(treeView);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");

        buttonLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");

        buttonLayout->addWidget(pushButton);


        leftLayout->addLayout(buttonLayout);


        horizontalLayout->addLayout(leftLayout);

        vtkWidget = new QVTKOpenGLNativeWidget(centralwidget);
        vtkWidget->setObjectName("vtkWidget");

        horizontalLayout->addWidget(vtkWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuItem = new QMenu(menubar);
        menuItem->setObjectName("menuItem");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuItem->menuAction());
        menuFile->addAction(actionopen_File);
        menuItem->addAction(actionItem_Options);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionopen_File->setText(QCoreApplication::translate("MainWindow", "Open File", nullptr));
        actionItem_Options->setText(QCoreApplication::translate("MainWindow", "Item Options", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuItem->setTitle(QCoreApplication::translate("MainWindow", "Item", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
