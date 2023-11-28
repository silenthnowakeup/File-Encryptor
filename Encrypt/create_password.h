#ifndef CREATE_PASSWORD_H
#define CREATE_PASSWORD_H

#include <QDialog>

namespace Ui {
class create_password;
}

class create_password : public QDialog
{
    Q_OBJECT

public:
    explicit create_password(QWidget *parent = nullptr);
    ~create_password();
    bool isLower = false;
    bool isUpper = false;
    bool isNumber = false;
    bool isSymbol = false;
    bool isCopy = false;
    int length;

private slots:
    void on_horizontalSlider_actionTriggered(int action);

    void on_pushButton_ok_clicked();

private:
    Ui::create_password *ui;
};

#endif // CREATE_PASSWORD_H
