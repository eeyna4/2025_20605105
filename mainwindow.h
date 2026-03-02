#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ModelPartList;
class ModelPart;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void statusUpdateMessage(const QString &message, int timeout);

private slots:
    void on_pushButton_2_released();
    void on_pushButton_released();
    void handleTreeClicked();
    void on_actionopen_File_triggered();
    void on_actionItem_Options_triggered();

private:
    Ui::MainWindow *ui;
    ModelPartList* partList;
};

#endif // MAINWINDOW_H
