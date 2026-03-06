#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QSurfaceFormat>

// Available in your VTK install; provides the recommended defaultFormat.
#include <QVTKOpenGLNativeWidget.h>

int main(int argc, char *argv[])
{
    // Keep these (safe). If ANGLE/software env vars are set, Qt will still follow them.
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    // IMPORTANT: Set VTK-recommended format BEFORE QApplication is created.
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}