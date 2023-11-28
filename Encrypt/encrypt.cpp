//#include "encrypt.h"
//#include <QFile>
//#include <QByteArray>
//#include <QCryptographicHash>
//#include <QDebug>
//#include <openssl/aes.h>
//#include <openssl/rand.h>

//Encrypt::Encrypt()
//{

//}

//const int AES_KEY_SIZE = 256;
//const int AES_BLOCK_SIZE_ = 128;

//void AESEncrypt(QString inputFilePath, QString outputFilePath, QString password)
//{
//    QFile inputFile(inputFilePath);
//    if (!inputFile.open(QIODevice::ReadOnly)) {
//        qDebug() << "Error opening input file.";
//        return;
//    }

//    QByteArray inputData = inputFile.readAll();

//    // Генерация случайной соли
//    QByteArray salt = generateRandomSalt();

//    // Генерация ключа из пароля и соли
//    QByteArray key = hashPassword(password.toUtf8(), salt);

//    // Шифрование данных
//    QByteArray encryptedData;
//    encryptedData.resize((inputData.size() + AES_BLOCK_SIZE_ - 1) / AES_BLOCK_SIZE_ * AES_BLOCK_SIZE_);

//    AES_KEY aesKey;
//    AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(key.constData()), AES_KEY_SIZE, &aesKey);
//    AES_encrypt(reinterpret_cast<const unsigned char*>(inputData.constData()), reinterpret_cast<unsigned char*>(encryptedData.data()), &aesKey);

//    // Запись зашифрованных данных в файл
//    QFile outputFile(outputFilePath);
//    if (!outputFile.open(QIODevice::WriteOnly)) {
//        qDebug() << "Error opening output file.";
//        return;
//    }

//    // Сохранение соли в начале файла
//    outputFile.write(salt);
//    outputFile.write(encryptedData);
//    qDebug() << "File encrypted successfully.";
//}
