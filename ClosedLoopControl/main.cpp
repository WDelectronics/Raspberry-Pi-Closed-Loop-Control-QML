#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QTimer>
#include "settings.h"
#include "control.h"
#include "pid.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QQuickStyle::setStyle("Material");
    QGuiApplication a(argc, argv);
    QQmlApplicationEngine engine;

    Settings settings;
    Control control;
    Pid pid;
    Parser parser;
    QTimer timer;
    timer.setInterval(50);

    QObject::connect(&settings, SIGNAL(pChanged(double)), &pid, SLOT(setP(double)));
    QObject::connect(&settings, SIGNAL(iChanged(double)), &pid, SLOT(setI(double)));
    QObject::connect(&settings, SIGNAL(dChanged(double)), &pid, SLOT(setD(double)));
    QObject::connect(&settings, SIGNAL(serialConnect(QString,QString)), &parser, SLOT(connectToPort(QString,QString)));
    QObject::connect(&settings, SIGNAL(serialDisconnect()), &parser, SLOT(disconnectFromPort()));
    QObject::connect(&parser, SIGNAL(connected(bool)), &settings, SLOT(setConnectionStatus(bool)));

    QObject::connect(&timer, SIGNAL(timeout()), &pid, SLOT(calculate()));
    QObject::connect(&parser, SIGNAL(newData(int)), &pid, SLOT(newFeedback(int)));
    QObject::connect(&parser, SIGNAL(newData(int)), &control, SLOT(setRpm(int)));
    QObject::connect(&control, SIGNAL(newSliderSetpoint(int)), &pid, SLOT(newSetpoint(int)));
    QObject::connect(&pid, SIGNAL(newOutput(int)), &parser, SLOT(transmittData(int)));
    QObject::connect(&pid, SIGNAL(newOutput(int)), &control, SLOT(setLoad(int)));
    QObject::connect(&control, SIGNAL(closedLoopSwitch(bool)), &pid, SLOT(setActive(bool)));

    engine.rootContext()->setContextProperty("settingsDialog", &settings);
    engine.rootContext()->setContextProperty("controlDialog", &control);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    timer.start();

    return a.exec();
}
