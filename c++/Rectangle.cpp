#include "Rectangle.h"

void Rectangle::line_style(Fl_Color color, int line_style, int width) {
    line_color_ = color;
	line_style_ = line_style;
	line_width_ = width;
    this->redraw();
}

void Rectangle::fill_color(Fl_Color color) {
	if(fill_color_) free(fill_color_);
    fill_color_ = new Fl_Color{color};
    this->redraw();
}

// first draw filled rectangle if fill_color is instantiated
// second draw line rectangle with given line style
void Rectangle::draw() {
    int x = this->x();
    int y = this->y();
    int w = this->w();
    int h = this->h();
    if (fill_color_) fl_rectf(x, y, w, h, *fill_color_);
    fl_color(line_color_);
    fl_line_style(line_style_, line_width_);
    fl_rect(x, y, w, h);
    fl_color(0);
    fl_line_style(0);
}

