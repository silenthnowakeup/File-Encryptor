#include "file.h"
#include <QDebug>
#include <fstream>

File::File()
{

}

QByteArray File::readBytesFromFile(const QString &filePath)
{
    QByteArray data;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        data = file.readAll();
        file.close();
    }
    else
    {
        qDebug() << "Ошибка открытия файла для чтения:" << file.errorString();
    }

    return data;
}

// Метод для записи данных в файл
bool File::writeBytesToFile(const QString &filePath, const QByteArray &data)
{
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly))
    {
        qint64 bytesWritten = file.write(data);
        file.close();

        if (bytesWritten == data.size())
        {
            qDebug() << "Данные успешно записаны в файл:" << filePath;
            return true;
        }
        else
        {
            qDebug() << "Ошибка записи данных в файл:" << file.errorString();
                return false;
        }
    }
    else
    {
        qDebug() << "Ошибка открытия файла для записи:" << file.errorString();
        return false;
    }
}

qint64 File::size(QString filepath)
{
    QFile file(filepath);
    return file.size();
}
