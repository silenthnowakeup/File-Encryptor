#ifndef FILE_H
#define FILE_H
#include <QString>
#include <QFile>
#include <fstream>

class File
{
public:
    File();
    QByteArray readBytesFromFile(const QString &filePath);
    bool writeBytesToFile(const QString &filePath, const QByteArray &data);
    qint64 size(QString);
};

#endif // FILE_H
