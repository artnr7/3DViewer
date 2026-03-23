#include <QApplication>
#include <QSurfaceFormat>

#include "controller.h"
#include "logger.h"
#include "model.h"
// #include "utils/gif.h"
#include "view.h"

std::unique_ptr<s21::Lg> s21::Lg::inst_ = nullptr;

int main(int argc, char* argv[]) {
  // #include <QImage>
  // #include <vector>
  //
  // #include "gif.h"
  //
  //   void createGif(const QString& filename, const QList<QImage>& frames) {
  //     if (frames.isEmpty()) return;
  //
  //     int width = frames[0].width();
  //     int height = frames[0].height();
  //     GifWriter writer;
  //     GifBegin(&writer, filename.toUtf8().constData(), width, height,
  //              10);  // 10ms delay
  //
  //     for (const QImage& frame : frames) {
  //       // Ensure format is compatible
  //       QImage formattedFrame =
  //       frame.convertToFormat(QImage::Format_RGBA8888);
  //
  //       // gif.h expects raw RGBA data
  //       GifWriteFrame(&writer, formattedFrame.bits(), width, height, 10);
  //     }
  //     GifEnd(&writer);
  //   }
  s21::Lg::Log()->Info(std::string(__func__));
  // s21::Lg::Log()->SetLogLevel(s21::Lg::LogLevel::TRACE);
  //
  // int width = 1200;
  // int height = 900;
  // std::vector<uint8_t> black(width * height * 4, 0);
  // std::vector<uint8_t> white(width * height * 4, 255);
  //
  // auto fileName = "bwgif.gif";
  //
  // int delay = 100;
  // GifWriter g;
  // GifBegin(&g, fileName, width, height, delay);
  // GifWriteFrame(&g, black.data(), width, height, delay);
  // GifWriteFrame(&g, white.data(), width, height, delay);

  QApplication app(argc, argv);

  s21::Model model;
  s21::Controller controller(&model);
  s21::View view(&controller);

  s21::Lg::Log()->Info("View show");
  view.show();
  auto aaa = app.exec();

  // GifEnd(&g);
  return aaa;
}
