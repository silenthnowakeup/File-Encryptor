#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_file_clicked();

    void password_operations();

    void on_lineEdit_password_textChanged(const QString &arg1);

    void check_password();

    void on_pushButton_clicked();

    void updateButtonText();
    void encryptFile();
    void decryptFile();

private:
    QString file_path;

    QString password;
    QString confirm_password;
    bool isPasswordVisible;
    Ui::MainWindow *ui;    
};
#endif // MAINWINDOW_H
