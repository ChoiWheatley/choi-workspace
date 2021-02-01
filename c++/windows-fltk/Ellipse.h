/*
 * <PPPUC++> Drawing Ellipse
 * using fl_arc(int x, int y, int w, int h, double a1, double a2)
 * x and y are center of Ellipse, w and h are each major and minor axis
 */
#ifndef ELLIPSE_H
#define ELLIPSE_H
#include <FL/fl_draw.H>
#include <FL/Fl_Widget.H>

class Ellipse : public Fl_Widget {
    int x_, y_, w_, h_;
    int ln_style_ = 0, ln_width_ = 0;
    int font_face_ = FL_HELVETICA, font_size_ = 0;
    const char * label_;
    Fl_Color * fill_color_ = nullptr;
    Fl_Color * line_color_ = new Fl_Color{FL_BLACK};
public:
    Ellipse(int x, int y, int w, int h, const char * label = 0) :
        Fl_Widget{x, y, w, h, label},
        x_{x}, y_{y}, w_{w}, h_{h}, label_{label} {
            if (x_ < 0) x_ *= (-1);
            if (y_ < 0) y_ *= (-1);
            if (w_ < 0) w_ *= (-1);
            if (h_ < 0) h_ *= (-1);
        }
    ~Ellipse() {delete label_; delete fill_color_; delete line_color_;}
    void fill_color(Fl_Color);
    void line_color(Fl_Color);
    void line_style(int style, int width);
    void font_style(int font_face, int font_size);
public:
    Fl_Color    fill_color() const {return *fill_color_;}
    Fl_Color    line_color() const {return *line_color_;}
    int         ln_style()   const {return ln_style_;}
    int         ln_width()   const {return ln_width_;}
    int         x()          const {return x_;}
    int         y()          const {return y_;}
    int         w()          const {return w_;}
    int         h()          const {return h_;}
    const char* label()      const {return label_;}
private:
    virtual void draw() override;
}; // class Ellipse


#endif
