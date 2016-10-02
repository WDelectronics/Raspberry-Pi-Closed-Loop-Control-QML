#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double p READ p WRITE setP NOTIFY pChanged)
    Q_PROPERTY(double i READ i WRITE setI NOTIFY iChanged)
    Q_PROPERTY(double d READ d WRITE setD NOTIFY dChanged)
    Q_PROPERTY(bool connectionStatus READ connectionStatus WRITE setConnectionStatus NOTIFY connectionStatusChanged)
    Q_PROPERTY(int portIndex READ portIndex WRITE setPortIndex NOTIFY portIndexChanged)
    Q_PROPERTY(int baudIndex READ baudIndex WRITE setBaudIndex NOTIFY baudIndexChanged)
    Q_PROPERTY(bool autoConnect READ autoConnect WRITE setAutoConnect NOTIFY autoConnectChanged)
public:
    explicit Settings(QObject *parent = 0);
    Q_INVOKABLE void save();
    Q_INVOKABLE void load();
    Q_INVOKABLE QStringList getPortInfo();
    Q_INVOKABLE QStringList getBaudInfo();

    double p() const;
    double i() const;
    double d() const;
    bool connectionStatus() const;
    bool autoConnect() const;
    int portIndex() const;
    int baudIndex() const;

signals:
    void serialConnect(QString port, QString baud);
    void serialDisconnect();
    void pChanged(double p);
    void iChanged(double i);
    void dChanged(double d);
    void connectionStatusChanged(bool connectionStatus);
    void autoConnectChanged(bool autoConnect);
    void portIndexChanged(int portIndex);
    void baudIndexChanged(int baudIndex);

public slots:
    void setP(double p);
    void setI(double i);
    void setD(double d);
    void setConnectionStatus(bool connectionStatus);
    void setAutoConnect(bool autoConnect);
    void setPortIndex(int portIndex);
    void setBaudIndex(int baudIndex);

private:

    double m_p;
    double m_i;
    double m_d;
    bool m_connectionStatus;
    bool m_autoConnect;
    int m_portIndex;
    int m_baudIndex;
    QStringList baudList;
    QStringList portList;
};

#endif // SETTINGS_H
