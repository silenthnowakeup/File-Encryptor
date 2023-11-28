#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "password.h"
#include "create_password.h"
#include <QClipboard>
#include <stdio.h>
#include "file.h"
#include <QMessageBox>
#include "encrypt.h"
#include <stdio.h>
#include <vector>
#include "aes.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileSystemModel>
#include <QDebug>
#include <string>
#include "sha256.h"
#define BUFFER_SIZE 1024*1024

void MainWindow::updateButtonText() {

    // Обновить имя файла из поля выбора файла
    if (this->file_path.endsWith(".pcv", Qt::CaseInsensitive)) {
        ui->pushButton->setText("Decrypt file");
    } else {
        ui->pushButton->setText("Encrypt file");
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateButtonText();

    connect(ui->pushButton_create, SIGNAL(clicked()), this, SLOT(password_operations()));
    connect(ui->pushButton_copy, SIGNAL(clicked()), this, SLOT(password_operations()));
    connect(ui->pushButton_paste, SIGNAL(clicked()), this, SLOT(password_operations()));
    connect(ui->pushButton_show, SIGNAL(clicked()), this, SLOT(password_operations()));
    connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(password_operations()));
    connect(ui->lineEdit_password, SIGNAL(textChanged(QString)), this, SLOT(on_lineEdit_password_textChanged(QString)));
    connect(ui->lineEdit_confirm_password, SIGNAL(textChanged(QString)), this, SLOT(on_lineEdit_password_textChanged(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_file_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Все файлы (*.*)");
    if(!filePath.isEmpty())
    {
        ui->statusbar->showMessage("Open the folder:" + filePath);
    }
    this->file_path = filePath;
    QString type = file_path.right(4);
    QString dec_out = file_path;
    dec_out.chop(4);

    if(type == ".pcv")
    {
        ui->pushButton->setText("Decrypt file");
        ui->lineEdit_out->setText(dec_out);
        ui->lineEdit_confirm_password->setText("");
        ui->lineEdit_confirm_password->setEnabled(false);
        ui->pushButton_create->setEnabled(false);
    }
    else{
        ui->pushButton->setText("Encrypt file");
        ui->lineEdit_out->setText(file_path + ".pcv");
        ui->lineEdit_confirm_password->setEnabled(true);
        ui->pushButton_create->setEnabled(true);
    }
}


void MainWindow::password_operations()
{
    QPushButton *button = (QPushButton *)sender();

    if (button->text() == "Create")
    {
        create_password window;
        window.setModal(true);
        window.exec();
        Password generator;

        this->password = generator.createPassword(window.length, window.isUpper, window.isLower, window.isNumber, window.isSymbol, window.isCopy);
        ui->statusbar->showMessage("Password is create!");
        ui->lineEdit_password->setText(this->password);
        ui->lineEdit_confirm_password->setText(this->password);
        this->isPasswordVisible = false;
    }
    if (button->text() == "Clear")
    {
        ui->lineEdit_password->setText("");
        ui->lineEdit_confirm_password->setText("");
    }
    if (button->text() == "Copy")
    {
        QApplication::clipboard()->setText(this->password);
        ui->statusbar->showMessage("Copy to buffer complete!");
    }
    if (button->text() == "Paste")
    {
        QString clipboardText = QApplication::clipboard()->text();
        ui->lineEdit_password->setText(clipboardText);
        if (ui->pushButton->text() != "Decrypt file")
            ui->lineEdit_confirm_password->setText(clipboardText);
    }
    if (button->text() == "Show")
    {
        if (ui->lineEdit_password->text().isEmpty()) {
            return; // Если поле пароля пустое, нет смысла переключаться
        }

        // Переключение видимости пароля
        if (ui->lineEdit_password->echoMode() == QLineEdit::Password) {
            ui->lineEdit_password->setEchoMode(QLineEdit::Normal); // Показать пароль
            ui->lineEdit_confirm_password->setEchoMode(QLineEdit::Normal);
        } else {
            ui->lineEdit_password->setEchoMode(QLineEdit::Password);
            ui->lineEdit_confirm_password->setEchoMode(QLineEdit::Password);

    }
}
}



void MainWindow::on_lineEdit_password_textChanged(const QString &text)
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(sender());

    if (lineEdit->objectName() == "lineEdit_password")
    {
        this->password = text;
    }
    else if (lineEdit->objectName() == "lineEdit_confirm_password")
    {
        this->confirm_password = text;
    }

    check_password();

    // Устанавливаем отображение в виде звездочек
    lineEdit->setEchoMode(QLineEdit::Password);
}



void MainWindow::check_password()
{
    // Проверяем, совпадают ли пароли
    bool passwordsMatch = (this->password == this->confirm_password);

    // Окрашиваем QLineEdit в зависимости от результата проверки
    if(ui->pushButton->text() == "Encrypt file")
    {
        QPalette palette;
        palette.setColor(QPalette::Text, passwordsMatch ? Qt::green : Qt::red);
        ui->lineEdit_password->setPalette(palette);
        ui->lineEdit_confirm_password->setPalette(palette);
    }
}

void MainWindow::encryptFile()
{
    QFile file(this->file_path);

    // Если открыть файл для шифрования (.pcv)
    file.open(QIODevice::ReadOnly);
    QString file_path = this->file_path;
    QString out_file_path = ui->lineEdit_out->text();
    qint64 len;

    if (!file_path.isEmpty()) {
        QByteArray data = file.readAll();
        len = file.size();
        QMessageBox::about(this, "Данные", "Файл " + file_path + " успешно прочитан");

        AES Encrypt;
        // Преобразование QString в QByteArray с использованием UTF-8
        QByteArray passwordBytes = this->password.toUtf8();
        SHA256 hash;
        std::string hashedKey = hash.hash(passwordBytes.constData());

        // Конвертирование хешированного пароля в const unsigned char*
        const unsigned char* key = reinterpret_cast<const unsigned char*>(hashedKey.c_str());

        // Выравнивание длины данных до кратного 16
        // Проверяем, нужно ли добавлять padding
        if ((len) % 16 != 0) {
            // Выравнивание длины данных до кратного 16
            int padding = 16 - ((len) % 16);

            // Добавляем нули для выравнивания
            data.append(QByteArray(padding-1, 0));
            data.append(static_cast<char>(padding));


            // Обновляем длину
            len += padding;
        }

        const unsigned char* dataPtr = reinterpret_cast<const unsigned char*>(data.constData());

        const unsigned char* encryptedDataPtr = Encrypt.EncryptECB(dataPtr, len, key);

        // Создание QByteArray с использованием конструктора, принимающего указатель и размер
        QByteArray encryptedData(reinterpret_cast<const char*>(encryptedDataPtr), len);

        QFile out_file(out_file_path);

        // Открытие файла в режиме записи
        if (out_file.open(QIODevice::WriteOnly)) {
            // Запись зашифрованных данных в файл
            out_file.write(encryptedData);

            // Закрытие файла после записи
            out_file.close();

            QMessageBox::about(this, "Успех", "Файл успешно зашифрован и записан в " + out_file_path);
        } else {
            qDebug() << "Не удалось открыть файл для записи.";
        }

        // Освобождение памяти, выделенной в EncryptECB
        delete[] encryptedDataPtr;
    } else {
        ui->statusbar->showMessage("Выбор файла отменен");
    }
}

void copyFile(const QString &sourceFilePath, const QString &destFilePath)
{
    QFile sourceFile(sourceFilePath);
    QFile destFile(destFilePath);

    if (!sourceFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Не удалось открыть исходный файл для чтения.";
        return;
    }
    if (!destFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Не удалось открыть целевой файл для записи.";
        return;
    }
    destFile.write(sourceFile.readAll());
    sourceFile.close();
    destFile.close();
}

void deleteFile(const QString &filePath)
{
    QFile file(filePath);
    file.remove();
}

void MainWindow::decryptFile()
{
    // Действия с файлами
    QString file_path = this->file_path;
    file_path.chop(4);
    QString type = file_path.right(4);
    file_path.chop(4);
    QString temp_path = file_path + "temp" + type;
    copyFile(this->file_path, temp_path);
    QString file_path_out = ui->lineEdit_out->text();
    QFile out_file(file_path_out);
    QFile file(temp_path);
    file.open(QIODevice::ReadOnly);

    AES decrypt;
    qint64 len;

    QByteArray data = file.readAll();
    const unsigned char* dataPtr = reinterpret_cast<const unsigned char*>(data.constData());
    len = file.size();

    deleteFile(temp_path);

    // Преобразование QString в QByteArray с использованием UTF-8
    QByteArray passwordBytes = ui->lineEdit_password->text().toUtf8();

    SHA256 hash;
    std::string hashedKey = hash.hash(passwordBytes.constData());

    // Конвертирование хешированного ключа const unsigned char*
    const unsigned char* key = reinterpret_cast<const unsigned char*>(hashedKey.c_str());

    const unsigned char* decryptedDataPtr = decrypt.DecryptECB(dataPtr, len , key);
    QByteArray decryptedData(reinterpret_cast<const char*>(decryptedDataPtr), len);
    int paddingSize = decryptedData.at(decryptedData.length() - 1);
    decryptedData.chop(paddingSize);

    // Открытие файла в режиме записи
    if (out_file.open(QIODevice::WriteOnly)) {
        // Запись зашифрованных данных в файл
        out_file.write(decryptedData);

        // Закрытие файла после записи
        out_file.close();

        QMessageBox::about(this, "Успех", "Файл успешно расшифрован и записан в " + file_path_out);
    } else {
        qDebug() << "Не удалось открыть файл для записи.";
    }
}


void MainWindow::on_pushButton_clicked() {    
    if(ui->pushButton->text() == "Encrypt file")
    {
        encryptFile();
    }
    if (ui->pushButton->text() == "Decrypt file")
    {
        decryptFile();
    }
}
