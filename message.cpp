#include "message.h"
#include "ui_message.h"

Message::Message(QWidget *parent) : // конструктор
    QDialog(parent),
    ui(new Ui::Message)
{
    ui->setupUi(this);
    ui->label->setText("");
    this->setWindowTitle("Уведомление");
}

Message::~Message() // деструктор
{
    delete ui;
}

void Message::set_warn(QString str) // получение текста
{
    ui->label->setText(str);
}

void Message::on_pushButton_clicked() // закрытие ошибки
{
    this->close();
}

