// mainwindow.cpp

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "ModelPartList.h"
#include "ModelPart.h"
#include "optionaldialog.h"

#include <QStatusBar>
#include <QTreeView>
#include <QFileDialog>
#include <QFileInfo>
#include <QDialog>
#include <QTimer>
#include <QDebug>

// VTK
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>

#include <vtkNew.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, &MainWindow::statusUpdateMessage,
            ui->statusbar, &QStatusBar::showMessage);

    // Helps visually confirm the widget is actually present in the layout.
    ui->vtkWidget->setStyleSheet("background: black;");
    ui->vtkWidget->setMinimumSize(200, 200);

    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    ui->vtkWidget->setRenderWindow(renderWindow);

    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(0.0, 0.0, 0.0);
    renderWindow->AddRenderer(renderer);

    vtkNew<vtkCylinderSource> cylinder;
    cylinder->SetResolution(8);

    vtkNew<vtkPolyDataMapper> cylinderMapper;
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    cylinderActor = vtkSmartPointer<vtkActor>::New();
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(1., 0., 0.35);

    cylinderActor->RotateX(30);
    cylinderActor->RotateY(-45);

    renderer->AddActor(cylinderActor);

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();

    this->partList = new ModelPartList("Parts List");
    ui->treeView->setModel(this->partList);

    ui->treeView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->treeView->addAction(ui->actionItem_Options);

    ModelPart* rootItem = this->partList->getRootItem();

    for (int i = 0; i < 3; i++) {
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");

        ModelPart* childItem = new ModelPart({name, visible});
        rootItem->appendChild(childItem);

        for (int j = 0; j < 5; j++) {
            QString childName = QString("Item %1,%2").arg(i).arg(j);
            ModelPart* childChildItem = new ModelPart({childName, visible});
            childItem->appendChild(childChildItem);
        }
    }

    connect(ui->treeView, &QTreeView::clicked,
            this, &MainWindow::handleTreeClicked);

    // IMPORTANT: delay first render until the widget has a valid size/context.
    QTimer::singleShot(0, this, [this]() {
        qDebug() << "vtkWidget size:" << ui->vtkWidget->size();
        updateRender();
    });
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
    if (!selectedPart) return;

    QString text = selectedPart->data(0).toString();
    emit statusUpdateMessage(QString("The selected item is : ") + text, 0);
}

void MainWindow::updateRender()
{
    if (!renderer || !renderWindow) {
        return;
    }

    renderer->RemoveAllViewProps();

    if (cylinderActor) {
        renderer->AddActor(cylinderActor);
    }

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();

    renderWindow->Render();
}

void MainWindow::updateRenderFromTree(const QModelIndex& index)
{
    Q_UNUSED(index);
}

void MainWindow::on_pushButton_released()
{
    on_actionItem_Options_triggered();
}

void MainWindow::on_pushButton_2_released()
{
    emit statusUpdateMessage("Add button was clicked", 0);
}

void MainWindow::on_actionItem_Options_triggered()
{
}

void MainWindow::on_actionopen_File_triggered()
{
}