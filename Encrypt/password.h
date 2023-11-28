#ifndef PASSWORD_H
#define PASSWORD_H
#include <QMainWindow>

class Password
{
public:
    Password();
    QString createPassword(int length, bool isUpper, bool isLower, bool isNumbers, bool isSymbols, bool isCopy);
};

#endif // PASSWORD_H
