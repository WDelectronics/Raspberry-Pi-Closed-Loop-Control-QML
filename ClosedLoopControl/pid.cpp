#include "pid.h"

Pid::Pid(QObject *parent) :
    QObject(parent)
{
    m_P = 0;
    m_I = 0;
    m_D = 0;
    pTerm = iTerm = dTerm = 0;
    setpoint = feedback = 0;
    doInit = true;
    output = 0;
    mode = AUTOMATIC;
    min = -255;
    max = 255;
}

void Pid::calculate()
{
    if (mode == MANUAL)
    {
        output = (setpoint / 350.0) * max;
    }
    else
    {
        if (doInit)
        {
            doInit = false;
            dError = feedback;
            iTerm = output;
            if (iTerm > max)
                iTerm = max;
            if (iTerm < min)
                iTerm = min;
        }

        int error = setpoint - feedback;
        pTerm = m_P * error;
        iTerm += m_I * error;

        if (iTerm > max)
            iTerm = max;
        if (iTerm < min)
            iTerm = min;

        dTerm = m_D *(feedback - dError);
        dError = feedback;

        output = pTerm + iTerm - dTerm;
    }

    if (output > max)
        output = max;
    if (output < min)
        output = min;

    if (output != lastOutput)
    {
        emit newOutput(output);
        output = lastOutput;
    }
}

void Pid::setOutputLimits(float min, float max)
{
    if (min > max)
    {
        return;
    }
    this->min = min;
    this->max = max;

    if (iTerm > max)
    {
        iTerm = max;
    }
    if (iTerm < min)
    {
        iTerm = min;
    }
}

void Pid::setActive(bool state)
{
    if (state == true)
    {
        if (mode == MANUAL)
        {
            doInit = true;
        }
        mode = AUTOMATIC;
    }
    else
    {
        mode = MANUAL;
    }
}

double Pid::P() const
{
    return m_P;
}

double Pid::I() const
{
    return m_I;
}

double Pid::D() const
{
    return m_D;
}

void Pid::newSetpoint(int setpoint)
{
    this->setpoint = setpoint;
}

void Pid::newFeedback(int feedback)
{
    this->feedback = feedback;
}

void Pid::setP(double P)
{
    m_P = P;
}

void Pid::setI(double I)
{
    m_I = I;
}

void Pid::setD(double D)
{
    m_D = D;
}
