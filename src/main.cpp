#include "View/MainWindow/MainWindow.hpp"
#include <QApplication>
#include <memory>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  auto w = std::make_unique<MainWindow>( );

  w->show( );

  return app.exec( );
}
