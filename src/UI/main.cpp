#include "pch.h"
#include "mainwindow.h"
#include "mymodel.h"
#include "processesmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProcessesModel processesModel;
    MyModel logModel;

    MainWindow window(nullptr,&processesModel,&logModel);
    window.show();
    return a.exec();
}
