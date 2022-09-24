#include "pch.h"
#include "mainwindow.h"
#include "processesmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProcessesModel processesModel;

    MainWindow window(nullptr,&processesModel);
    window.show();
    return a.exec();
}
