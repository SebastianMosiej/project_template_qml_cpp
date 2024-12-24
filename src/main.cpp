#include "MainApp.h"
#include <QDebug>

int main(int argc, char* argv[])
{
    try
    {
        Q_INIT_RESOURCE(qml);
        return MainApp(argc, argv).exec();
    }
    catch (std::runtime_error& e)
    {
        qDebug() << "Runtime error: " << e.what();
        return -1;
    }
}


