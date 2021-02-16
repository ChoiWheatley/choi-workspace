#ifndef GRAPH_H
#define GRAPH_H 1

#include "fltk.h"
#include "Point.h"
#include "std_lib_facilities.h"


namespace Graph_lib 
{

typedef double Fct(double);

struct Color {
    enum Transparency { invisible = 0, visible = 255 };

    Color(Fl_Color cc) : v{visible}, c{cc} {}
    Color(Fl_Color cc, Transparency vv) : v{vv}, c{cc} {}
    Color(Transparency vv) : v{vv}, c{Fl_Color()} {}

    int as_int() const { return c; }
    Transparency visibility() const { return v; }
    void visibility(Transparency vv) { v=vv; }
private:
    Transparency v;        // visibility 0 or 1
    Fl_Color c;
};// struct Color

struct Line_style {
private:
    int s;
    int w;
public:
    Line_style(int ss) : s{ss}, w{0} { }
    Line_style(int ss, int ww) : s{ss}, w{ww} { }

    int width() const { return w; }
    int style() const { return s; }
};// struct Line_style

class Shape 
{
    vector<Point> points;
    Color lcolor {fl_color()};
    Line_style ls {0};
    Color fcolor {Color::invisible};

protected:
    Shape() { }
    Shape(initializer_list<Point> lst) : points{lst} {}  // add() the Points to this Shape
    void add(Point p) { points.push_back(p); }
    void set_point(int i, Point p) { points[i] = p; }

public:
    void draw() const;              // deal with color and draw_lines
protected:
    virtual void draw_lines() const;// simply draw lines
public:
    virtual void move(int dx, int dy);


    void set_color(Color col) {lcolor = col;}
    Color color() const { return lcolor; }

    void set_style(Line_style sty) { ls = sty; }
    Line_style style() const { return ls; }

    void set_fill_color(Color col) { fcolor = col; }
    Color fill_color() const { return fcolor; }

    Point point(int i) const { return points[i]; }
    Point& operator[](int i) { return points[i]; }
    int number_of_points() const { return int(points.size()); }

    virtual ~Shape() {}
};// class Shape


struct Function : Shape {
    Function(Fct f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);
};// struct Function

struct Line : Shape {
    Line(Point p1, Point p2) { add(p1); add(p2); }
};// struct Line

struct Rectangle : Shape {
    Rectangle(Point xy, int ww, int hh) : w{ww}, h{ww} {
        if (h <= 0 || w <= 0) error ("Bad rectangle: none positive side");
        add(xy);
    }
    Rectangle(Point a, Point b) : w{ b.x - a.x }, h{ b.y - a.y } {
        if (w < 0) {
            a = Point{b.x, a.y};
            b = Point{a.x, b.y};
            w *= (-1);
        } 
        if (h < 0) {
            a = Point{a.x, b.y};
            b = Point{b.x, a.y};
            h *= (-1);
        }
        add(a);
    }
    void draw_lines() const;

    int height() const { return h; }
    int width() const { return w; }
private:
    int w;
    int h;
};// struct Rectangle


}// namespace Graph_lib
#endif
