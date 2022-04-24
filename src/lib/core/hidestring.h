#ifndef HIDESTRING_H
#define HIDESTRING_H

#include <QString>

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
    std::string stdstr = qin.toStdString();
    const char * input = stdstr.c_str();
    int inputLength = qin.toStdString().length();
    const char* key;
    int keyLength;
    if (qkey.isEmpty())
    {
        Alpha str("");
        std::string myStr = str.c('g').c('F').c('H').c('z').c('}').c('m').c('H').c('>').c('d').c('j').c('w').c('r').c('Q').c('x').c('3').c('V').c('l').c('s').c('p').c('F').c('"').c('E').c('b').c('<').c('H').c('O').c('P').c('T').c('X').c('f');
        qkey = QString::fromStdString(myStr);
    }
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

namespace alphaConst {
    Alpha str("");
    std::string pass = str.c('P').c('A').c('S').c('S');
    const QString qPrefix(QString::fromStdString(pass));
}

#endif // HIDESTRING_H
