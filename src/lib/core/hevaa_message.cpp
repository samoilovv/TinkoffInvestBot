#include "hevaa_message.h"

namespace hevaa {

namespace transport {

    message::message()
    {

    }

    message::message(const message &other)
    {
        m_type = other.m_type;
        m_rootItem = other.m_rootItem;
    }

    message::~message()
    {

    }

    message::message(const MsgType &type, const Node &body)
    {
        m_type = type;
        m_rootItem = body;
    }

    Node message::body() const
    {
        return m_rootItem;
    }

    MsgType message::type() const
    {
        return m_type;
    }

}

}
