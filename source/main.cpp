#include <QApplication>
#include "WMain.h"
#include "Logger.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  Logger logger;
  WMain main;
  main.show();
  return app.exec();
}
