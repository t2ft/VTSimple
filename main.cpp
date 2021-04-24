#include "mainwidget.h"

#include "t2ftapplication.h"

int main(int argc, char *argv[])
{
    T2FTApplication a(argc, argv, "VTSimple", "1.0.0");
    MainWidget w;
    w.show();
    return a.exec();
}
