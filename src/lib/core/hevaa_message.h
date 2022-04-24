#ifndef HEVAA_MESSAGE_H
#define HEVAA_MESSAGE_H

#include <QDebug>
#include <QMetaType>
#include "hevaa_tree.h"

namespace hevaa {

namespace transport {

    enum MsgType { HandshakeQuery, HandshakeAnswer, Info, Command };

    class message
    {
    public:
        message();
        message(const message &other);
        ~message();

        message(const MsgType &type, const Node &body = nullptr);
        Node body() const;
        MsgType type() const;

    private:
        QVector<QStringList> m_data;
        MsgType m_type;
        Node m_rootItem;
    };

}

}

Q_DECLARE_METATYPE(hevaa::transport::message);

#endif // HEVAA_MESSAGE_H
