#ifndef MAINAPP_H
#define MAINAPP_H
#include <QGuiApplication>

class QQmlApplicationEngine;

class MainApp : public QGuiApplication
{
public:
    MainApp(int argc, char* argv[]);
    virtual ~MainApp();
private:
    void parseArgs();
    void setupQML();
    void registerTypes();

    std::unique_ptr<QQmlApplicationEngine>  m_engine;
};

#endif // MAINAPP_H
