#ifndef SEND_READ_DATA_H
#define SEND_READ_DATA_H

#include <QString>
#include <QTcpSocket>
#include <QDataStream>

class send_read_data
{
public:
    send_read_data();
    void sendData(QString string, QTcpSocket *Socket);
    QString read_message(QTcpSocket *socket);

private :
    quint16 nextBlockSize;
};

#endif // SEND_READ_DATA_H
