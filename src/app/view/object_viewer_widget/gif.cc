#include "../../utils/gif.h"

#include <qcontainerfwd.h>
#include <qdatetime.h>
#include <qimage.h>
#include <qlist.h>
#include <qlogging.h>
#include <qmath.h>
#include <qnamespace.h>

#include <cstdint>
#include <glm/common.hpp>
#include <string>

#include "obj_v_wid.h"

namespace s21 {

void ObjectViewerWidget::MakeGIF() {
  if (gif_status) {
    return;
  }
  gif_status = true;

  gif_timer_->start(100);
}

void ObjectViewerWidget::MakeImage() {
  if (img_status) {
    return;
  }
  img_status = true;

  QPixmap pixmap = grab();
  QImage image = pixmap.toImage();

  Str def_path{"build/bin/"};

  Str time_stamp = GetTimeStamp();

  Str jpeg = def_path + time_stamp + ".jpeg";
  Str bmp = def_path + time_stamp + ".bmp";

  QString time_stamp_jpeg{jpeg.data()};
  QString time_stamp_bmp{bmp.data()};

  image.save(time_stamp_jpeg);
  image.save(time_stamp_bmp);

  img_status = false;
}

void ObjectViewerWidget::MGIF() {
  static uint8_t frames_cnt = 0;

  QPixmap pixmap = grab();
  QImage image = pixmap.toImage();
  image = image.convertToFormat(QImage::Format_RGBA8888);
  image = image.scaled(gif_w_, gif_h_);

  ++frames_cnt;
  images_.push_back(image);

  if (frames_cnt == 50) {
    gif_timer_->stop();

    if (images_.empty()) return;

    Str def_path{"build/bin/"};
    Str time_stamp = GetTimeStamp();
    Str gif = def_path + time_stamp + ".gif";
    QString time_stamp_gif{gif.data()};

    GifWriter writer;
    GifBegin(&writer, time_stamp_gif.toUtf8().constData(), gif_w_, gif_h_,
             delay_);

    for (const QImage& frame : images_) {
      GifWriteFrame(&writer, frame.bits(), gif_w_, gif_h_, delay_);
    }
    GifEnd(&writer);

    gif_status = false;
    frames_cnt = 0;
    images_.clear();
  }
}

Str ObjectViewerWidget::GetTimeStamp() {
  auto datetime = QDateTime::currentDateTime();
  auto date = datetime.date();
  auto time = datetime.time();

  auto tos = [](int arg) { return std::to_string(arg); };

  Str time_stamp{};
  time_stamp += tos(date.year());
  time_stamp += tos(date.day());
  time_stamp += tos(date.month());

  time_stamp += tos(time.hour());
  time_stamp += tos(time.minute());
  time_stamp += tos(time.second());
  time_stamp += tos(time.msec());

  return time_stamp;
}

}  // namespace s21
