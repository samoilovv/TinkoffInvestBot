#include "hevaa_tree.h"

namespace hevaa {

namespace transport {

TreeItem::TreeItem(const Row &data, Node parent)
    : m_itemData(data), m_parentItem(parent)
{}

TreeItem::~TreeItem()
{
}

void TreeItem::appendChild(Node item)
{
    m_childItems.append(item);
}

Node TreeItem::child(int row)
{
    if (row < 0 || row >= m_childItems.size())
        return nullptr;
    return m_childItems.at(row);
}

int TreeItem::childCount() const
{
    return m_childItems.count();
}

int TreeItem::columnCount() const
{
    return m_itemData.count();
}

QVariant TreeItem::data(int column) const
{
    if (column < 0 || column >= m_itemData.size())
        return QVariant();
    return m_itemData.at(column);
}

//int TreeItem::row() const
//{
//    if (m_parentItem)
//        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));
//    return 0;
//}

Node TreeItem::parentItem()
{
    return m_parentItem;
}

}

}
