#include "Ellipse.h"

void Ellipse::fill_color(Fl_Color c){
    if (fill_color_ != nullptr) delete fill_color_;
    fill_color_ = new Fl_Color{c};
    this->redraw();
}
void Ellipse::line_color(Fl_Color c){
    if (line_color_ != nullptr) delete line_color_;
    line_color_ = new Fl_Color{c};
    this->redraw();
}
void Ellipse::line_style(int style, int width){
    ln_style_ = style;
    ln_width_ = width;
    this->redraw();
}
void Ellipse::font_style(int font_face, int font_size){
    font_face_ = font_face;
    font_size_ = font_size;
    this->redraw();
}
void Ellipse::draw(){
    fl_font(font_face_, font_size_);
    fl_line_style(ln_style_, ln_width_);
    int aligned_x = x_ - (int)(fl_width(label_, strlen(label_)) / 2);
    int aligned_y = y_ - fl_descent() + (int)(fl_height()/2);
    int center_x  = x_ - (int)(w_ / 2);
    int center_y  = y_ - (int)(h_ / 2);

// TODO : Text align method needed : text.align(LEFT | UPPER), 
// text.align(RIGHT | BOTTOM), text.align(CENTER_H | CENTER_V)
// using bitmask alright?
    // fill
    if (fill_color_) {
        fl_color(*fill_color_);
        fl_pie(center_x, center_y, w_-1, h_-1, 0, 360);
        fl_color(0);
    }
    // line
    fl_color(*line_color_);
    fl_arc(center_x, center_y, w_, h_, 0, 360);
    // text
    fl_draw(label_, aligned_x, aligned_y);
    // initialize color, style
    fl_font(1, 0);
    fl_line_style(0);
    fl_color(0);
}
