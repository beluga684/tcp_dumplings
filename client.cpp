#include "client.h"
#include "ui_client.h"

client::client(QWidget *parent) : //конструктор
    QWidget(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);

    this->setWindowTitle("Режим клиента");
    this->setFixedSize(779,399);

    ui->lineEdit_name->setPlaceholderText("Ваше имя здесь");

    color = Qt::blue;
    ui->label_color->setStyleSheet(QString("background-color: %1").arg(color.name()));

    TcpSocket = nullptr;

    ui->frame->setEnabled(0);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

client::~client() //деструктор
{
    if (TcpSocket!=nullptr)
        TcpSocket->deleteLater();
    delete ui;
}

void client::readData() //чтение сообщений
{
    QString str = srd->read_message(TcpSocket);
    QStringList str_list=str.split("⊘", Qt::KeepEmptyParts);

    if (str_list[0] == "✉")
    {
        message->close();
        message->set_warn(str_list[1]);
        message->show();
        return;
    }

    else if(str_list[0]=="∑")
    {
        str_list.removeAt(0);

        ui->tableWidget->setRowCount(str_list.size());

        for(int i = 0; i < str_list.size(); i++)
        {
            if(ui->tableWidget->item(i,0)==nullptr)
            {
                QTableWidgetItem *item;
                item = new QTableWidgetItem;
                ui->tableWidget->setItem(i, 0,item);
            }
            ui->tableWidget->item(i,0)->setText(str_list[i]);
        }
    }

    else if(str_list[0]=="£")
        ui->chatEdit->appendHtml("<span style=\"color:" + str_list[2] + "\">" + "<b>" + str_list[1] + "</b>"\
                + "<span style=\"color:" + str_list[2] + "\">" + " : " + str_list[3] + "</span>");
}

void client::disconnected() //отключение
{
    ui->frame_2->setEnabled(1);
    ui->frame->setEnabled(0);
    ui->chatEdit->clear();
    already_connected = false;
    ui->pushButton_connect->setText("Присоединиться к чату");
    ui->tableWidget->setRowCount(0);
}

void client::on_pushButton_connect_clicked() //подключение
{
    if(!already_connected)
    {
        if(ui->lineEdit_name->text().count("  ")>0 or ui->lineEdit_name->text().size()<=0)
        {
            message->close();
            message->set_warn("Проверьте имя");
            message->show();
            return;
        }

        int port=ui->spinBox_port->value();

        QHostAddress *adress;
        adress = new QHostAddress;
        adress->setAddress(ui->lineEdit_ip->text());

        if(!adress->isNull())
        {
            TcpSocket=nullptr;

            TcpSocket = new QTcpSocket(this);
            connect(TcpSocket, &QTcpSocket::readyRead, this, &client::readData);
            connect(TcpSocket, &QTcpSocket::disconnected, this, &client::disconnected);

            TcpSocket->connectToHost(*adress, quint16(port));

            if(TcpSocket->waitForConnected(1000))
            {
                QString str = "✉⊘" + (ui->lineEdit_name->text());
                srd->sendData(str, TcpSocket);

                ui->frame->setEnabled(1);
                ui->frame_2->setEnabled(0);

                ui->pushButton_connect->setText("Отключиться от чата");
                already_connected = true;
                self_disc = false;
            }
            else
            {
                message->close();
                message->set_warn("Не удалось подключится");
                message->show();
                return;
            }
        }
        else
        {
            message->close();
            message->set_warn("Не тот адресс");
            message->show();
            return;
        }
    }
    else
    {
        already_connected = false;
        self_disc = true;
        TcpSocket->disconnectFromHost();

        if(TcpSocket!=nullptr)
            TcpSocket->deleteLater();
        TcpSocket=nullptr;

        ui->frame_2->setEnabled(1);
        ui->frame->setEnabled(0);

        ui->chatEdit->clear();

        ui->tableWidget->setRowCount(0);

        ui->pushButton_connect->setText("Присоедениться к чату");
    }
}

void client::on_lineEdit_message_returnPressed() // отправка сообщения
{
    if(already_connected and ui->lineEdit_message->text().size()>0)
    {
        QString name = ui->lineEdit_name->text();

        QString color_str = color.name(QColor::HexArgb);

        QString text = ui->lineEdit_message->text().toHtmlEscaped();

        QString str = (name+"⊘"+color_str+"⊘"+ui->lineEdit_message->text()).toUtf8();

        srd->sendData(str, TcpSocket);

        ui->chatEdit->appendHtml("<span style=\"color:" + color_str + "\">" + "<b>" + name + "</b>" \
                                 + "<span style=\"color:" + color_str + "\">" + " : " + text + "</span>");

        ui->lineEdit_message->clear();
    }
}

void client::on_pushButton_local_clicked() // тестовые данные
{
    ui->lineEdit_ip->setText("127.0.0.1");
    ui->lineEdit_name->setText("standart_user");
}

void client::on_pushButton_name_color_clicked() // функция смены цвета
{
    color = QColorDialog::getColor(color,this);
    ui->label_color->setStyleSheet(QString("background-color: %1").arg(color.name()));
}

void client::closeEvent(QCloseEvent *event) // событие при закрытии окна
{
    message->close();
    event->accept();
}
