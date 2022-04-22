#ifndef HEVAA_TRANSPORT_H
#define HEVAA_TRANSPORT_H

#include <QVariant>
#include <QVector>
#include <QSharedPointer>

namespace hevaa
{
    namespace transport
    {
        class TreeItem;

        using Node  = QSharedPointer<TreeItem>;
        using Row   = QVector<QVariant>;
    }
}

#endif // HEVAA_TRANSPORT_H
