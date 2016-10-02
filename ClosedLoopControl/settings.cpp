#include "settings.h"
#include <QSettings>
#include <QtSerialPort/QSerialPortInfo>

Settings::Settings(QObject *parent) : QObject(parent)
{
   baudList << "9600" << "57600" << "115200";
   m_connectionStatus = false;
   m_autoConnect = false;
   m_portIndex = 0;
   m_baudIndex = 0;
   setP(0);
   setI(0);
   setD(0);
}

void Settings::save()
{
   QSettings settings("WD Electronics", "WheelControl");
   settings.beginGroup("PID");
   settings.setValue("Pterm", QVariant::fromValue(m_p));
   settings.setValue("Iterm", QVariant::fromValue(m_i));
   settings.setValue("Dterm", QVariant::fromValue(m_d));
   settings.endGroup();
   settings.beginGroup("Serial");
   if (!portList.isEmpty())
   {
      QString currentPort = portList.at(m_portIndex);
      QString currentBaud = baudList.at(m_baudIndex);
      settings.setValue("Port", QVariant::fromValue(currentPort));
      settings.setValue("Baud", QVariant::fromValue(currentBaud));
   }
   settings.setValue("AutoConnect", QVariant::fromValue(m_autoConnect));
   settings.endGroup();
}

void Settings::load()
{
   QSettings settings("WD Electronics", "WheelControl");
   settings.beginGroup("PID");
   double p = settings.value("Pterm").toDouble();
   double i = settings.value("Iterm").toDouble();
   double d = settings.value("Dterm").toDouble();
   settings.endGroup();
   settings.beginGroup("Serial");
   QString port = settings.value("Port").toString();
   QString baud = settings.value("Baud").toString();
   bool autoconnect = settings.value("AutoConnect").toBool();
   settings.endGroup();

   if (p < 0 || i < 0 || d < 0)
   {
      p = 0.5;
      i = 0.05;
      d = 0.5;
   }

   setP(p);
   setI(i);
   setD(d);

   if (!port.isEmpty())
   {
      QStringList portlist = getPortInfo();
      if (portlist.contains(port, Qt::CaseInsensitive))
      {
         setPortIndex(portlist.indexOf(port));
      }
   }
   if (!baud.isEmpty())
   {
      if (baudList.contains(baud, Qt::CaseInsensitive))
      {
         setBaudIndex(baudList.indexOf(baud));
      }
   }
   if (autoconnect)
   {
      setAutoConnect(autoconnect);
      serialConnect(port, baud);
   }
}

QStringList Settings::getPortInfo()
{
   foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
      portList << info.portName();
   }
   return portList;
}

QStringList Settings::getBaudInfo()
{
   return baudList;
}

double Settings::p() const
{
   return m_p;
}

double Settings::i() const
{
   return m_i;
}

double Settings::d() const
{
   return m_d;
}

bool Settings::connectionStatus() const
{
   return m_connectionStatus;
}

bool Settings::autoConnect() const
{
   return m_autoConnect;
}

int Settings::portIndex() const
{
   return m_portIndex;
}

int Settings::baudIndex() const
{
   return m_baudIndex;
}

void Settings::setP(double p)
{
   if (m_p == p)
      return;

   m_p = p;
   emit pChanged(p);
}

void Settings::setI(double i)
{
   if (m_i == i)
      return;

   m_i = i;
   emit iChanged(i);
}

void Settings::setD(double d)
{
   if (m_d == d)
      return;

   m_d = d;
   emit dChanged(d);
}

void Settings::setConnectionStatus(bool connectionStatus)
{
   if (m_connectionStatus == connectionStatus)
      return;

   m_connectionStatus = connectionStatus;
   emit connectionStatusChanged(connectionStatus);
}

void Settings::setAutoConnect(bool autoConnect)
{
   if (m_autoConnect == autoConnect)
      return;

   m_autoConnect = autoConnect;
   emit autoConnectChanged(autoConnect);
}

void Settings::setPortIndex(int portIndex)
{
   if (m_portIndex == portIndex)
      return;

   m_portIndex = portIndex;
   emit portIndexChanged(portIndex);
}

void Settings::setBaudIndex(int baudIndex)
{
   if (m_baudIndex == baudIndex)
      return;

   m_baudIndex = baudIndex;
   emit baudIndexChanged(baudIndex);
}
