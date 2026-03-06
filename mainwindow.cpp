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
#include <QMenuBar>
#include <QAction>
#include <QSplitter>
#include <QLabel>
#include <QTimer>

#include <QOpenGLContext>
#include <QSurfaceFormat>

#include <QVTKRenderWidget.h>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

#include <QFile>
#include <QTextStream>
#include <QDateTime>

static void mwlog(const char* msg)
{
    QFile f("C:/Users/LLR User/2025_20605105/Worksheet7/Exercise4/build/mwlog.txt");
    if (!f.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) return;
    QTextStream ts(&f);
    ts << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz") << " " << msg << "\n";
    ts.flush();
}

static QTreeView* runtimeTree(MainWindow* self)
{
    return self->findChild<QTreeView*>("treeView_runtime");
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) // keep, do not call setupUi()
{
    mwlog("STEP 1: constructor entered");

    setStatusBar(new QStatusBar(this));
    connect(this, &MainWindow::statusUpdateMessage,
            statusBar(), &QStatusBar::showMessage);
    mwlog("STEP 2: statusbar ready");

    auto *loading = new QLabel("Starting...", this);
    loading->setWordWrap(true);
    setCentralWidget(loading);
    mwlog("STEP 3: setCentralWidget(loading)");

    auto *fileMenu = menuBar()->addMenu(tr("&File"));
    auto *openAction = new QAction(tr("&Open File"), this);
    fileMenu->addAction(openAction);
    connect(openAction, &QAction::triggered,
            this, &MainWindow::on_actionopen_File_triggered);
    mwlog("STEP 4: menu open wired");

    partList = new ModelPartList("Parts List");
    mwlog("STEP 5: partList created");

    QTimer::singleShot(0, this, [this] {
        mwlog("STEP 6: singleShot entered");

        auto *splitter = new QSplitter(this);
        mwlog("STEP 7: splitter created");

        auto *treeView = new QTreeView(splitter);
        treeView->setObjectName("treeView_runtime");
        mwlog("STEP 8: treeView created");

        // HARD CHECK: prove OpenGL context can be created BEFORE any QVTK widget.
        mwlog("STEP 8.1: creating QOpenGLContext...");
        QOpenGLContext ctx;
        ctx.setFormat(QSurfaceFormat::defaultFormat());
        if (!ctx.create()) {
            mwlog("STEP 8.2: QOpenGLContext create FAILED");

            auto *err = new QLabel(
                "OpenGL context creation failed.\n"
                "This machine/driver cannot create the OpenGL context required for the VTK widget.\n\n"
                "Try updating GPU drivers, or run with:\n"
                "  set QT_OPENGL=angle\n"
                "  set QT_ANGLE_PLATFORM=d3d11\n"
                "or install a VTK build that provides QVTKOpenGLWidget.\n",
                this
            );
            err->setWordWrap(true);
            setCentralWidget(err);
            return;
        }
        mwlog("STEP 8.2: QOpenGLContext create OK");

        mwlog("STEP 8.5: BEFORE creating QVTKRenderWidget");

        // If the process dies here, it is 100% inside the widget ctor.
        auto *vtkWidget = new QVTKRenderWidget(splitter);
        vtkWidget->setObjectName("vtkWidget_runtime");
        mwlog("STEP 9: QVTKRenderWidget created");

        splitter->addWidget(treeView);
        splitter->addWidget(vtkWidget);
        splitter->setStretchFactor(0, 0);
        splitter->setStretchFactor(1, 1);
        mwlog("STEP 10: splitter populated");

        setCentralWidget(splitter);
        mwlog("STEP 11: setCentralWidget(splitter)");

        treeView->setModel(partList);
        mwlog("STEP 12: treeView model set");

        connect(treeView, &QTreeView::clicked, this, [this, treeView] {
            QModelIndex index = treeView->currentIndex();
            if (!index.isValid()) return;
            ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
            emit statusUpdateMessage(QString("The selected item is : ") + selectedPart->data(0).toString(), 0);
        });
        mwlog("STEP 13: tree click wired");

        renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
        vtkWidget->setRenderWindow(renderWindow);
        mwlog("STEP 14: renderWindow set");

        renderer = vtkSmartPointer<vtkRenderer>::New();
        renderer->SetBackground(0.2, 0.2, 0.2);
        renderWindow->AddRenderer(renderer);
        mwlog("STEP 15: renderer added");

        renderWindow->Render();
        mwlog("STEP 16: initial render done");
    });
}

MainWindow::~MainWindow()
{
    mwlog("STEP X: destructor");
    delete ui;
}

void MainWindow::handleTreeClicked()
{
    // setupUi disabled; ignore
}

void MainWindow::updateRender()
{
    if (!renderer || !renderWindow || !partList) return;

    renderer->RemoveAllViewProps();

    int topRows = partList->rowCount(QModelIndex());
    for (int i = 0; i < topRows; i++) {
        updateRenderFromTree(partList->index(i, 0, QModelIndex()));
    }

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();

    renderWindow->Render();
}

void MainWindow::updateRenderFromTree(const QModelIndex& index)
{
    if (index.isValid()) {
        ModelPart* part = static_cast<ModelPart*>(index.internalPointer());
        if (part && part->visible()) {
            auto a = part->getActor();
            if (a && a->GetMapper()) {
                renderer->AddActor(a);
            }
        }
    }

    if (!partList->hasChildren(index) || (index.flags() & Qt::ItemNeverHasChildren)) return;

    int rows = partList->rowCount(index);
    for (int i = 0; i < rows; i++) {
        updateRenderFromTree(partList->index(i, 0, index));
    }
}

void MainWindow::on_pushButton_released()
{
    emit statusUpdateMessage("Buttons unavailable (setupUi disabled)", 2000);
}

void MainWindow::on_pushButton_2_released()
{
    emit statusUpdateMessage("Buttons unavailable (setupUi disabled)", 2000);
}

void MainWindow::on_actionItem_Options_triggered()
{
    emit statusUpdateMessage("Item options unavailable (setupUi disabled)", 2000);
}

void MainWindow::on_actionopen_File_triggered()
{
    mwlog("Open File triggered");

    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        "C:\\",
        tr("STL Files (*.stl);;Text Files (*.txt)")
    );

    if (fileName.isEmpty()) {
        emit statusUpdateMessage("No file selected", 2000);
        mwlog("Open File: canceled");
        return;
    }

    emit statusUpdateMessage(QString("Selected file: ") + fileName, 0);

    QString baseName = QFileInfo(fileName).fileName();
    QString visible("true");

    ModelPart* newPart = new ModelPart({baseName, visible});
    newPart->loadSTL(fileName);

    QTreeView* tv = runtimeTree(this);
    QModelIndex index = tv ? tv->currentIndex() : QModelIndex();

    if (index.isValid()) {
        ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
        selectedPart->appendChild(newPart);
        if (tv) tv->expand(index);
        emit partList->dataChanged(index, index);
    } else {
        ModelPart* rootItem = partList->getRootItem();
        rootItem->appendChild(newPart);
        emit partList->layoutChanged();
    }

    updateRender();
    mwlog("Open File: loaded + rendered");
}