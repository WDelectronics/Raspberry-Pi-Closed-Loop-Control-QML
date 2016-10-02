#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QtSerialPort>

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = 0);

signals:
    void newData(int value);
    void connected(bool value);

public slots:
    void transmittData(int value);
    void connectToPort(QString port, QString baud);
    void disconnectFromPort();

private slots:
    void readData();

private:
    QSerialPort *serial;
};

#endif // PARSER_H
