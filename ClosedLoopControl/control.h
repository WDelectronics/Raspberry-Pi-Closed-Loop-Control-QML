#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>

class Control : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int rpm READ rpm WRITE setRpm NOTIFY RpmChanged)
    Q_PROPERTY(int load READ load WRITE setLoad NOTIFY loadChanged)

public:
    explicit Control(QObject *parent = 0);

    int rpm() const;
    int load() const;

signals:
    void newSliderSetpoint(int setpoint);
    void RpmChanged(int rpm);
    void loadChanged(int load);
    void closedLoopSwitch(bool state);

public slots:
    void setRpm(int rpm);
    void setLoad(int load);

private:
    int m_rpm;
    int m_load;
};

#endif // CONTROL_H
