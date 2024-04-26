#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <settings.h>

namespace Ui{
class client;
}

class client : public QWidget
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = nullptr);
    ~client();

private slots:

    void readData();

    void disconnected();

    void on_pushButton_connect_clicked();

    void on_lineEdit_message_returnPressed();

    void on_pushButton_local_clicked();

    void on_pushButton_name_color_clicked();

    void closeEvent(QCloseEvent *event);

private:
    Ui::client *ui;

    QColor color;
    bool already_connected = false;
    bool self_disc;

    QTcpSocket *TcpSocket;

    Message *message = new Message;

    QMap<QTcpSocket *, QByteArray> socketBuffer;
    QMap<QTcpSocket *, QByteArray> socketBuffers;

    send_read_data *srd = new send_read_data;
};

#endif // CLIENT_H
