#include "parser.h"

Parser::Parser(QObject *parent) :
    QObject(parent)
{
    serial = new QSerialPort(this);
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
}

void Parser::transmittData(int value)
{
    QString tx = QString::number(value) + '\n';
    if (serial->isOpen())
    {
        serial->write(tx.toUtf8());
    }
}

void Parser::connectToPort(QString port, QString baud)
{
    serial->setBaudRate(baud.toInt());
    serial->setPortName(port);
    bool status = serial->open(QIODevice::ReadWrite);
    emit connected(status);
}

void Parser::disconnectFromPort()
{
    if (serial->isOpen())
    {
        serial->close();
        emit connected(false);
    }
}

void Parser::readData()
{
    static QByteArray buffer;
    while (serial->bytesAvailable())
    {
        char data;
        serial->read(&data,1);
        if ((data == '\r') || (data == '\n'))
        {
            bool ok;
            int value = buffer.toInt(&ok);
            if (ok)
            {
                emit newData(value);
            }

            serial->peek(&data,1);
            if ((data == '\r') || (data == '\n'))
            {
                serial->read(&data,1);
            }
            buffer.clear();
        }
        else if (isprint(data))
        {
            buffer.append(data);
        }
    }
}
