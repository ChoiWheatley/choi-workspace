#include "Circle.h"

void Circle::fill_color(Fl_Color col) {
    if (fill_color_) delete fill_color_;
    fill_color_ = new Fl_Color{col};
    this->redraw();
}
void Circle::line_color(Fl_Color col) {
    if (line_color_) delete line_color_;
    line_color_ = new Fl_Color{col};
    this->redraw();
}
void Circle::line_style(int style, int width) {
    ln_style_ = style;
    ln_width_ = width;
    // draw() method will handle this
    this->redraw();
}
void Circle::font_style(int font_face, int font_size) {
    font_face_ = font_face;
    font_size_ = font_size;
    // draw() method will handle this
    this->redraw();
}
void Circle::draw() {
    // font, line
    fl_font(font_face_, font_size_);
    fl_line_style(ln_style_, ln_width_);
    fl_color(*line_color_);

    int aligned_x = x_ - (int)(fl_width(label_, strlen(label_)) / 2);
    int aligned_y = y_ - fl_descent() + (int)(fl_height() / 2);
    fl_circle((double)x_, (double)y_, (double)rad_);

//debug
    fl_line(x_-rad_, y_, x_+rad_, y_);
    fl_line(x_, y_-rad_, x_, y_+rad_);
//debug
    // fill
    if (fill_color_) {
        fl_color(*fill_color_);
        fl_pie(x_-rad_+1, y_-rad_+1, rad_+rad_-1, rad_+rad_-1, 0, 360);
        fl_color(0);
    }
    fl_draw(label_, aligned_x, aligned_y);
    
    fl_font(1, 0);
    fl_line_style(0);
    fl_color(0);
}
