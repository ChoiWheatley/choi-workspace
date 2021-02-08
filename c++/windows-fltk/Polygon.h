/*
Polygon class, 
    - Polygon class is a wrapper class for drawing an polygon
    - Initializer : {}
    - public member : 
    - private member : vertices, fill, linestyle, linecolor
*/
#ifndef POLYGON_H
#define POLYGON_H 1

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <vector>

class Polygon : public Fl_Widget{
public:
    Polygon() : Fl_Widget(0, 0, 0, 0, 0) {}
    ~Polygon() {}
    struct Vertex{ int x, int y };
// getters
    Fl_Color line_color() const {return line_color_;}
    Fl_Color fill_color() const {if(fill_color_ != nullptr) return *fill_color_; return 0;}
    int      line_stype() const {return line_style_;}
    int      cnt_vertices() const {return vertices_.size();}
// setters
    void line_style(Fl_Color color = FL_BLACK, int line_style = 0, int width = 0);
    void line_color(Fl_Color color);
    void fill_color(Fl_Color color);
    void fill_empty() {if(fill_color_ != nullptr) delete fill_color_;}
    void add_vertex(int x, int y);
private:
    int         line_style_ = 0;
    int         line_width_ = 0;
    Fl_Color    line_color_ = 0;
    Fl_Color*   fill_color_ = nullptr;
    vector<Vertex> vertices_;
// methods
    virtual void draw() override;
}; // class Polygon

#endif
