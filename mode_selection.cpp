#include "mode_selection.h"
#include "ui_mode_selection.h"

mode_selection::mode_selection(QWidget *parent) // конструктор
    : QMainWindow(parent)
    , ui(new Ui::mode_selection)
{
    ui->setupUi(this);

    this->setWindowTitle("Выбор режима");
    this->setFixedSize(269,99);

    ui->comboBox->setEditable(true);
    ui->comboBox->lineEdit()->setReadOnly(true);
    ui->comboBox->lineEdit()->setAlignment(Qt::AlignCenter);

    for (int i = 0; i < ui->comboBox->count(); i++)
        ui->comboBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
}

mode_selection::~mode_selection() // деструктор
{
    delete ui;
}

void mode_selection::on_pushButton_clicked() // выбор режима и переход к окну
{
    if (ui->comboBox->currentIndex()==1)// клиент
    {
        client *Client = new client;
        Client -> show();
    }
    else if (ui->comboBox->currentIndex()==2)// сервер
    {
        server *Server = new server;
        Server -> show();
    }
    else
    {
        QMessageBox::warning(this,"Внимание","Выберите режим чата.");
        return;
    }
    this -> close();
}
