/*
 * <PPPUC++> 12.7.6. Rectangle 
 * - Rectangle class instantiates with 4 arguments, { int x, int y, int width, int height }
 * - Line style, Line color, Fill inside support
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H 1
#include <FL/Fl.H>
#include <FL/fl_draw.H>

class Rectangle : public Fl_Widget {
public:
    Rectangle(int x, int y, int w, int h) : Fl_Widget(x, y, w, h, 0){}
    ~Rectangle() { free(fill_color_); }
// getters
    Fl_Color line_color() const {return line_color_;}
    Fl_Color fill_color() const {return *fill_color_;}
    int      line_style() const {return line_style_;}
// setters
    void line_style(Fl_Color color = FL_WHITE, int line_style = 0, int width = 0);
    void fill_color(Fl_Color color);
    void fill_empty() { free(fill_color_); this->redraw(); }
private:
// members
    int       line_style_ = 0;
    int       line_width_ = 0;
    Fl_Color  line_color_ = 0;
    Fl_Color* fill_color_ = nullptr;
// methods
    virtual void draw() override;
}; // class Rectangle
// helper functions

#endif
