#include "forms/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  //TODO: Loading of full-featured style sheet
  //from resource file
  a.setStyleSheet("* { font-size: 14px }");
  MainWindow w;
//  TableEditTestForm w;
  w.show();

  return a.exec();
}
