#ifndef HIDESTRING_H
#define HIDESTRING_H

#include <QString>

/*!
    \brief Строковый тип данных

    Класс, позволяющий спрятать строковые данные внутри бинарных файов программы
*/
class Alpha : public std::string
{
public:
    Alpha(std::string str)
    {
        std::string phrase(str.c_str(), str.length());
        this->assign(phrase);
    }
    Alpha c(char c) {
        std::string phrase(this->c_str(), this->length());
        phrase += c;
        this->assign(phrase);
        return *this;
    }
};

QString codeDecode(QString qin, QString qkey = "")
{
    if (qkey.isEmpty())
    {
        return qin;
    } else {
        std::string stdstr = qin.toStdString();
        const char * input = stdstr.c_str();
        int inputLength = qin.toStdString().length();
        const char* key;
        int keyLength;
        std::string strkey = qkey.toStdString().c_str();
        key = strkey.c_str();
        keyLength = qkey.toStdString().length();
        char output[inputLength];
        for (int i = 0; i < inputLength; ++i)
        {
            output[i] = input[i] ^ key[i % keyLength];
        }
        return QString::fromLatin1(output, inputLength);
    }
}

namespace alphaConst {
    Alpha str("");
    std::string pass = str.c('P').c('A').c('S').c('S');
    const QString qPrefix(QString::fromStdString(pass));
}

#endif // HIDESTRING_H
