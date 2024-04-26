#include "send_read_data.h"

send_read_data::send_read_data()
{

}

void send_read_data::sendData(QString string, QTcpSocket *Socket)
{
    QByteArray Data = string.toUtf8();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    out << quint16(0) << string;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof (quint16));
    Socket->write(Data);
}

QString send_read_data::read_message(QTcpSocket *socket)
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_12);

    if(in.status() == QDataStream::Ok)
    {
        for(;;)
        {
            if (nextBlockSize == 0)
            {
                if (socket->bytesAvailable() < 2)
                    break;

                in >> nextBlockSize;
            }

            if (socket->bytesAvailable() < nextBlockSize)
                break;

            QString str;

            in >> str;
            nextBlockSize = 0;

            return str;
        }
    }
    return "-";
}
