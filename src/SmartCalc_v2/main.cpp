#include <QApplication>

#include "scview.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::SCView w;
  w.show();
  return a.exec();
}
