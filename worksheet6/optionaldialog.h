#ifndef OPTIONALDIALOG_H
#define OPTIONALDIALOG_H

#include <QDialog>

class ModelPart;

namespace Ui {
class OptionalDialog;
}

class OptionalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionalDialog(QWidget *parent = nullptr);
    ~OptionalDialog();

    void setFromModelPart(ModelPart* part);
    void applyToModelPart(ModelPart* part);

private:
    Ui::OptionalDialog *ui;
};

#endif // OPTIONALDIALOG_H
