/**     @file ModelPart.cpp
  *
  *     EEEE2076 - Software Engineering & VR Project
  *
  *     Template for model parts that will be added as treeview items
  *
  *     P Evans 2022
  */

#include "ModelPart.h"


/* Commented out for now, will be uncommented later when you have
 * installed the VTK library
 */
//#include <vtkSmartPointer.h>
//#include <vtkDataSetMapper.h>


ModelPart::ModelPart(const QList<QVariant>& data, ModelPart* parent )
    : m_itemData(data), m_parentItem(parent)
{
    /* Default values */
    isVisible = true;
    colourR = 0;
    colourG = 0;
    colourB = 0;
}

ModelPart::~ModelPart()
{
    qDeleteAll(m_childItems);
}

void ModelPart::appendChild(ModelPart* item)
{
    /* Add another model part as a child of this part
     * (it will appear as a sub-branch in the treeview)
     */
    item->m_parentItem = this;
    m_childItems.append(item);
}

ModelPart* ModelPart::child(int row)
{
    /* Return pointer to child item in row below this item.
     */
    if (row < 0 || row >= m_childItems.size())
        return nullptr;
    return m_childItems.at(row);
}

int ModelPart::childCount() const
{
    /* Count number of child items
     */
    return m_childItems.count();
}

int ModelPart::columnCount() const
{
    /* Count number of columns (properties) that this item has.
     */
    return m_itemData.count();
}

QVariant ModelPart::data(int column) const
{
    /* Return the data associated with a column of this item
     * QVariant is a generic placeholder type
     */
    if (column < 0 || column >= m_itemData.size())
        return QVariant();
    return m_itemData.at(column);
}

void ModelPart::set(int column, const QVariant &value)
{
    /* Set the data associated with a column of this item
     */
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
    /* Return the row index of this item, relative to its parent.
     */
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<ModelPart*>(this));
    return 0;
}

/* ---------- Colour handling (FIXED) ---------- */
void ModelPart::setColour(const unsigned char R, const unsigned char G, const unsigned char B)
{
    colourR = R;
    colourG = G;
    colourB = B;
}

unsigned char ModelPart::getColourR()
{
    return colourR;
}

unsigned char ModelPart::getColourG()
{
    return colourG;
}

unsigned char ModelPart::getColourB()
{
    return colourB;
}

/* ---------- Visibility handling (FIXED) ---------- */
void ModelPart::setVisible(bool isVisible)
{
    this->isVisible = isVisible;
}

bool ModelPart::visible()
{
    return this->isVisible;
}

void ModelPart::loadSTL(QString fileName)
{
    Q_UNUSED(fileName);
    /* Placeholder for later VTK work */
}

//vtkSmartPointer<vtkActor> ModelPart::getActor() {
//}

//vtkActor* ModelPart::getNewActor() {
//}
