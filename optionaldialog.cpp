#include "optionaldialog.h"
#include "ui_optionaldialog.h"

#include "ModelPart.h"

OptionalDialog::OptionalDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionalDialog)
{
    ui->setupUi(this);

    ui->spinBoxR->setRange(0, 255);
    ui->spinBoxG->setRange(0, 255);
    ui->spinBoxB->setRange(0, 255);
}

OptionalDialog::~OptionalDialog()
{
    delete ui;
}

void OptionalDialog::setFromModelPart(ModelPart* part)
{
    if (!part) return;

    ui->lineEditName->setText(part->data(0).toString());

    ui->spinBoxR->setValue(part->getColourR());
    ui->spinBoxG->setValue(part->getColourG());
    ui->spinBoxB->setValue(part->getColourB());

    ui->checkBoxVisible->setChecked(part->visible());
}

void OptionalDialog::applyToModelPart(ModelPart* part)
{
    if (!part) return;

    // Name (column 0)
    part->set(0, ui->lineEditName->text());

    // isVisible + column 1 string
    bool vis = ui->checkBoxVisible->isChecked();
    part->setVisible(vis);
    part->set(1, vis ? "true" : "false");

    // Colour
    part->setColour(
        static_cast<unsigned char>(ui->spinBoxR->value()),
        static_cast<unsigned char>(ui->spinBoxG->value()),
        static_cast<unsigned char>(ui->spinBoxB->value())
        );
}
