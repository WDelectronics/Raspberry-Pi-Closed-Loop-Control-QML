#include "control.h"

Control::Control(QObject *parent) :
   QObject(parent)
{
}

int Control::rpm() const
{
   return m_rpm;
}

int Control::load() const
{
   return m_load;
}

void Control::setRpm(int rpm)
{
   if (m_rpm == rpm)
      return;

   m_rpm = rpm;
   emit RpmChanged(rpm);
}

void Control::setLoad(int load)
{
   if (m_load == load)
      return;

   m_load = load;
   emit loadChanged(load);
}
