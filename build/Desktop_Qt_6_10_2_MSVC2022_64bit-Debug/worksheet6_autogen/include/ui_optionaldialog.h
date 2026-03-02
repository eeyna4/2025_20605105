/********************************************************************************
** Form generated from reading UI file 'optionaldialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONALDIALOG_H
#define UI_OPTIONALDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OptionalDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *labelName;
    QLineEdit *lineEditName;
    QLabel *labelR;
    QSpinBox *spinBoxR;
    QLabel *labelG;
    QSpinBox *spinBoxG;
    QLabel *labelB;
    QSpinBox *spinBoxB;
    QLabel *labelVisible;
    QCheckBox *checkBoxVisible;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *OptionalDialog)
    {
        if (OptionalDialog->objectName().isEmpty())
            OptionalDialog->setObjectName("OptionalDialog");
        OptionalDialog->resize(420, 260);
        verticalLayout = new QVBoxLayout(OptionalDialog);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        labelName = new QLabel(OptionalDialog);
        labelName->setObjectName("labelName");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelName);

        lineEditName = new QLineEdit(OptionalDialog);
        lineEditName->setObjectName("lineEditName");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEditName);

        labelR = new QLabel(OptionalDialog);
        labelR->setObjectName("labelR");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelR);

        spinBoxR = new QSpinBox(OptionalDialog);
        spinBoxR->setObjectName("spinBoxR");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, spinBoxR);

        labelG = new QLabel(OptionalDialog);
        labelG->setObjectName("labelG");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, labelG);

        spinBoxG = new QSpinBox(OptionalDialog);
        spinBoxG->setObjectName("spinBoxG");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, spinBoxG);

        labelB = new QLabel(OptionalDialog);
        labelB->setObjectName("labelB");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, labelB);

        spinBoxB = new QSpinBox(OptionalDialog);
        spinBoxB->setObjectName("spinBoxB");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, spinBoxB);

        labelVisible = new QLabel(OptionalDialog);
        labelVisible->setObjectName("labelVisible");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, labelVisible);

        checkBoxVisible = new QCheckBox(OptionalDialog);
        checkBoxVisible->setObjectName("checkBoxVisible");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, checkBoxVisible);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(OptionalDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(OptionalDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, OptionalDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, OptionalDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(OptionalDialog);
    } // setupUi

    void retranslateUi(QDialog *OptionalDialog)
    {
        OptionalDialog->setWindowTitle(QCoreApplication::translate("OptionalDialog", "Item Options", nullptr));
        labelName->setText(QCoreApplication::translate("OptionalDialog", "Name", nullptr));
        labelR->setText(QCoreApplication::translate("OptionalDialog", "Colour R", nullptr));
        labelG->setText(QCoreApplication::translate("OptionalDialog", "Colour G", nullptr));
        labelB->setText(QCoreApplication::translate("OptionalDialog", "Colour B", nullptr));
        labelVisible->setText(QCoreApplication::translate("OptionalDialog", "isVisible", nullptr));
        checkBoxVisible->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class OptionalDialog: public Ui_OptionalDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONALDIALOG_H
