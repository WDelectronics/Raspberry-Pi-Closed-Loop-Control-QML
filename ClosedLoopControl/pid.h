#ifndef PID_H
#define PID_H

#include <QObject>

#define MANUAL 0
#define AUTOMATIC 1

class Pid : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double P READ P WRITE setP)
    Q_PROPERTY(double I READ I WRITE setI)
    Q_PROPERTY(double D READ D WRITE setD)
public:
    explicit Pid(QObject *parent = 0);

    void setOutputLimits(float min, float max);
    double P() const;
    double I() const;
    double D() const;

signals:
    void newOutput(int out);
public slots:
    void setActive(bool state);
    void newSetpoint(int setpoint);
    void newFeedback(int feedback);
    void calculate(void);
    void setP(double P);
    void setI(double I);
    void setD(double D);

private:
    double pTerm;
    double iTerm;
    double dTerm;
    int dError;
    double min;
    double max;
    int mode;
    bool doInit;
    int setpoint;
    int feedback;
    int output;
    int lastOutput;
    double m_P;
    double m_I;
    double m_D;
};

#endif // PID_H
