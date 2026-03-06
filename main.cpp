// main.cpp

#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLNativeWidget.h>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // REQUIRED: ensures the widget gets the correct OpenGL format
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}