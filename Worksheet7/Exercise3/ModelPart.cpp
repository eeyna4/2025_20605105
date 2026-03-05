/**     @file ModelPart.cpp
  *
  *     EEEE2076 - Software Engineering & VR Project
  *
  *     Template for model parts that will be added as treeview items
  *
  *     P Evans 2022
  */

#include "ModelPart.h"

// VTK
#include <vtkProperty.h>

ModelPart::ModelPart(const QList<QVariant>& data, ModelPart* parent)
    : m_itemData(data), m_parentItem(parent)
{
    // Default values
    isVisible = true;

    // IMPORTANT: default colour must not be black (or you won't see it on black background)
    colourR = 255;
    colourG = 255;
    colourB = 255;

    // Create empty actor/mapper so getActor() is always valid
    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    actor  = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    actor->GetProperty()->SetColor(1.0, 1.0, 1.0);
    actor->SetVisibility(1);
}

ModelPart::~ModelPart()
{
    qDeleteAll(m_childItems);
}

void ModelPart::appendChild(ModelPart* item)
{
    item->m_parentItem = this;
    m_childItems.append(item);
}

ModelPart* ModelPart::child(int row)
{
    if (row < 0 || row >= m_childItems.size())
        return nullptr;
    return m_childItems.at(row);
}

int ModelPart::childCount() const
{
    return m_childItems.count();
}

int ModelPart::columnCount() const
{
    return m_itemData.count();
}

QVariant ModelPart::data(int column) const
{
    if (column < 0 || column >= m_itemData.size())
        return QVariant();
    return m_itemData.at(column);
}

void ModelPart::set(int column, const QVariant &value)
{
    if (column < 0 || column >= m_itemData.size())
        return;

    m_itemData.replace(column, value);
}

ModelPart* ModelPart::parentItem()
{
    return m_parentItem;
}

int ModelPart::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<ModelPart*>(this));
    return 0;
}

/* ---------- Colour handling ---------- */
void ModelPart::setColour(const unsigned char R, const unsigned char G, const unsigned char B)
{
    colourR = R;
    colourG = G;
    colourB = B;

    if (actor) {
        actor->GetProperty()->SetColor(
            static_cast<double>(colourR) / 255.0,
            static_cast<double>(colourG) / 255.0,
            static_cast<double>(colourB) / 255.0
        );
    }
}

unsigned char ModelPart::getColourR() { return colourR; }
unsigned char ModelPart::getColourG() { return colourG; }
unsigned char ModelPart::getColourB() { return colourB; }

/* ---------- Visibility handling ---------- */
void ModelPart::setVisible(bool isVisible)
{
    this->isVisible = isVisible;

    if (actor) {
        actor->SetVisibility(isVisible ? 1 : 0);
    }
}

bool ModelPart::visible()
{
    return this->isVisible;
}

/* ---------- STL loading (Worksheet7 Exercise4) ---------- */
void ModelPart::loadSTL(QString fileName)
{
    file = vtkSmartPointer<vtkSTLReader>::New();
    file->SetFileName(fileName.toStdString().c_str());
    file->Update();

    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(file->GetOutputPort());

    actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // Apply current colour + visibility
    actor->GetProperty()->SetColor(
        static_cast<double>(colourR) / 255.0,
        static_cast<double>(colourG) / 255.0,
        static_cast<double>(colourB) / 255.0
    );
    actor->SetVisibility(isVisible ? 1 : 0);
}

vtkSmartPointer<vtkActor> ModelPart::getActor()
{
    return actor;
}

vtkActor* ModelPart::getNewActor()
{
    vtkActor* newActor = vtkActor::New();
    if (mapper) {
        newActor->SetMapper(mapper);
    }

    newActor->GetProperty()->SetColor(
        static_cast<double>(colourR) / 255.0,
        static_cast<double>(colourG) / 255.0,
        static_cast<double>(colourB) / 255.0
    );
    newActor->SetVisibility(isVisible ? 1 : 0);

    return newActor; // caller must Delete()
}