#include "MainApp.h"
#include <QQmlApplicationEngine>
#include <QObject>

MainApp::MainApp(int argc, char* argv[]) : QGuiApplication (argc, argv)
{
    parseArgs();
    registerTypes();

    setupQML();
}

MainApp::~MainApp()
{ }

void MainApp::parseArgs()
{
    const QStringList argumentsList = arguments();
}

void MainApp::setupQML()
{
    m_engine.reset(new QQmlApplicationEngine);

    m_engine->addImportPath("qrc:/");

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(m_engine.get(), &QQmlApplicationEngine::objectCreated,
        this,[url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);
    m_engine->load(url);
}

void MainApp::registerTypes()
{
    // qmlRegisterSingletonInstance("Settings", 1, 0, "AppSettings", &m_appSettings);
}
