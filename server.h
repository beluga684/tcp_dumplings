#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <settings.h>

namespace Ui {
class server;
}

class server : public QWidget
{
    Q_OBJECT

public:
    explicit server(QWidget *parent = nullptr);
    ~server();

private slots:
    void on_pushButton_connect_clicked();

    void new_connection();

    void del_connection();

    void antiBan();

    void readData();

    void onlineList();

    void disconnected();

    void on_lineEdit_message_returnPressed();

    void on_pushButton_name_color_clicked();

    bool checkForSpam(QTcpSocket *clientSocket);

    void closeEvent(QCloseEvent *event);

private:
    Ui::server *ui;
    bool server_connected = false;
    bool client_disc = false;

    QTcpServer *TcpServer;
    QHostAddress adress;
    QColor color;
    QList <QTcpSocket*> Sockets;
    QStringList ban_list;

    QMap <QTcpSocket*, QString> nicks;
    QTcpSocket *server_id;

    QMap<QTcpSocket*, QTime> m_clients;
    QMap<QTcpSocket*, int> m_messagesPerSecond;
    Message *message = new Message;


    QMap<QTcpSocket *, QByteArray> socketBuffer;
    QMap<QTcpSocket *, QByteArray> socketBuffers;

    send_read_data *srd = new send_read_data;
};

#endif // SERVER_H
