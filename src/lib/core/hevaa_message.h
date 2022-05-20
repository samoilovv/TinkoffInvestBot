#ifndef HEVAA_MESSAGE_H
#define HEVAA_MESSAGE_H

#include <QDebug>
#include <QMetaType>
#include "hevaa_tree.h"

namespace hevaa {

namespace transport {

    /*!
        \brief Тип сообщения

        HandshakeQuery - запрос на подключение к модулю или роботу;
        HandshakeAnswer - ответ на попытку подключения;
        Info - информационное сообщение для модуля или робота;
        Command - команда модулю или роботу.

    */
    enum MsgType { HandshakeQuery, HandshakeAnswer, Info, Command };

    /*!
        \brief Сообщения, пересылаемые между модулями программы

        Структура сообщения, используемого для коммуникации модулей и роботов,
        внутри себя содержит деревовидную структуру данных, что позволяет передавать
        сложные вложенные сообщения и команды, например структуру меню телеграм бота
        или набор команд робота.
    */
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
