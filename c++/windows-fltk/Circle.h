/*
 * <PPPUC++> Drawing Circle, arc
 */
 #ifndef CIRCLE_H
 #define CIRCLE_H
 #include <FL/fl_draw.H>
 #include <FL/Fl_Widget.H>

 class Circle : public Fl_Widget{
    int x_, y_, rad_;
    int ln_style_ = 0, ln_width_ = 0;
    int font_face_ = FL_HELVETICA, font_size_ = 0;
    const char * label_;
    Fl_Color * fill_color_ = nullptr;
    Fl_Color * line_color_ = new Fl_Color{FL_BLACK};
public:
    Circle(int x, int y, int rad, const char * label = 0) :
        Fl_Widget{x-rad, y-rad, rad+rad, rad+rad, label},
        x_{x}, y_{y}, rad_{rad}, label_{label} {}
    ~Circle() { delete fill_color_; delete label_; delete line_color_; }
    void fill_color(Fl_Color);
    void line_color(Fl_Color);
    void line_style(int style, int width); 
    void font_style(int font_face, int font_size);
public:
    Fl_Color fill_color() const {return *fill_color_;}
    Fl_Color line_color() const {return *line_color_;}
    int ln_style() const {return ln_style_;}
    int ln_width() const {return ln_width_;}
    int x() const {return x_;}
    int y() const {return y_;}
    int rad() const {return rad_;}
    const char* label() const {return label_;}
private:
    virtual void draw() override;
 }; // class Circle

 #endif
