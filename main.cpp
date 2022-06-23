#include <iostream>
#include <QApplication>
#include <mainwindow.h>

using namespace std;

int main(int argc, char** argv)
{
 QApplication q_app (argc, argv);
 MainWindow window;

 return q_app.exec();
}
