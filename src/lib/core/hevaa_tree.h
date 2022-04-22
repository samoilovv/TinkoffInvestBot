#ifndef HEVAA_TREE_H
#define HEVAA_TREE_H

#include "hevaa_transport.h"

namespace hevaa
{
    namespace transport
    {

        class TreeItem
        {
        public:
            explicit TreeItem(const Row &data, Node parentItem = nullptr);
            ~TreeItem();

            void appendChild(Node child);

            Node child(int row);
            int childCount() const;
            int columnCount() const;
            QVariant data(int column) const;
    //        int row() const;
            Node parentItem();

        private:
            QVector<Node> m_childItems;
            Row m_itemData;
            Node m_parentItem;
        };
    }
}

#endif // HEVAA_TREE_H
