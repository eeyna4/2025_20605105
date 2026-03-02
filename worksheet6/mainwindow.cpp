#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "ModelPartList.h"
#include "ModelPart.h"
#include "optionaldialog.h"

#include <QStatusBar>
#include <QTreeView>
#include <QFileDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, &MainWindow::statusUpdateMessage,
            ui->statusbar, &QStatusBar::showMessage);

    // Tree model
    this->partList = new ModelPartList("Parts List");
    ui->treeView->setModel(this->partList);

    // Exercise 10: context menu on tree
    ui->treeView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->treeView->addAction(ui->actionItem_Options);

    // Build demo tree
    ModelPart* rootItem = this->partList->getRootItem();

    for (int i = 0; i < 3; i++) {
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");

        ModelPart* childItem = new ModelPart({name, visible});
        rootItem->appendChild(childItem);

        for (int j = 0; j < 5; j++) {
            QString name = QString("Item %1,%2").arg(i).arg(j);
            QString visible("true");

            ModelPart* childChildItem = new ModelPart({name, visible});
            childItem->appendChild(childChildItem);
        }
    }

    // Exercise 5: show clicked item in status bar
    connect(ui->treeView, &QTreeView::clicked,
            this, &MainWindow::handleTreeClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleTreeClicked()
{
    QModelIndex index = ui->treeView->currentIndex();
    if (!index.isValid()) return;

    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
    QString text = selectedPart->data(0).toString();
    emit statusUpdateMessage(QString("The selected item is : ") + text, 0);
}

// Exercise 9: run dialog from Delete button (عشان يكون عندك طريق ثاني غير right-click)
void MainWindow::on_pushButton_released()
{
    on_actionItem_Options_triggered();
}

void MainWindow::on_pushButton_2_released()
{
    emit statusUpdateMessage("Add button was clicked", 0);
}

// Exercise 10: right click action -> dialog
void MainWindow::on_actionItem_Options_triggered()
{
    QModelIndex index = ui->treeView->currentIndex();
    if (!index.isValid()) {
        emit statusUpdateMessage("Select an item in the tree first", 3000);
        return;
    }

    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    OptionalDialog dialog(this);
    dialog.setFromModelPart(selectedPart);

    if (dialog.exec() == QDialog::Accepted) {
        dialog.applyToModelPart(selectedPart);

        // refresh both columns
        QModelIndex c0 = index.sibling(index.row(), 0);
        QModelIndex c1 = index.sibling(index.row(), 1);
        emit partList->dataChanged(c0, c1);

        emit statusUpdateMessage("Dialog accepted", 0);
    } else {
        emit statusUpdateMessage("Dialog rejected", 0);
    }
}

// Exercise 8: Open file dialog and update selected item name
void MainWindow::on_actionopen_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        "C:\\",
        tr("STL Files (*.stl);;Text Files (*.txt)")
        );

    if (fileName.isEmpty()) {
        emit statusUpdateMessage("No file selected", 2000);
        return;
    }

    emit statusUpdateMessage(QString("Selected file: ") + fileName, 0);

    QModelIndex index = ui->treeView->currentIndex();
    if (!index.isValid()) {
        emit statusUpdateMessage("Select an item in the tree first", 3000);
        return;
    }

    QString baseName = QFileInfo(fileName).fileName();

    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
    selectedPart->set(0, baseName);

    QModelIndex c0 = index.sibling(index.row(), 0);
    emit partList->dataChanged(c0, c0);
}
