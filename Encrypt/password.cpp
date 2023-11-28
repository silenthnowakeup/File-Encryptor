#include "password.h"
#include <cstdlib>   // Для функции rand()
#include <ctime>     // Для функции time()
#include <QString>
#include <QApplication>
#include <QClipboard>
#include <algorithm>

Password::Password()
{

}

static const char numbers[] = "0123456789";
static const char symbols[] = "!@#$%^&*";
static const char lowercase[] = "abcdefghijklmnopqrstuvwxyz";
static const char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static const char alphanum[] =
    "0123456789"
    "!@#$%^&*"
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

QString Password::createPassword(int length, bool isUpper, bool isLower, bool isNumbers, bool isSymbols, bool isCopy)
{
    QString password;
    srand(static_cast<unsigned int>(time(0)));

    std::string selectedSet;

    if (isUpper)
    {
        selectedSet += uppercase;
    }
    if (isLower)
    {
        selectedSet += lowercase;
    }
    if (isNumbers)
    {
        selectedSet += numbers;
    }
    if (isSymbols)
    {
        selectedSet += symbols;
    }

    if (selectedSet.empty())
    {
        selectedSet = alphanum;
    }

    for (int i = 0; i < length; i++)
    {
        char selectedChar = selectedSet[rand() % selectedSet.size()];
        password += selectedChar;
    }

    if (isCopy)
        QApplication::clipboard()->setText(password);

    return password;
}

