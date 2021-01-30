/*
 * <PPPUC++> Drawing Circle, arc
 */
 #ifndef CIRCLE_H
 #define CIRCLE_H
 #include <FL_fl_draw.H>

 typedef Func_Type void (*)();

 class Circle : public Fl_Widget {
    int x_, y_, rad_, start_, end_;
    enum class Filltype = Filltype::line;
 public:
    Circle(int x, int y, int w, int h, int start = 0, int end = 360, const char* label = 0);
    Circle(int x, int y, int rad, int start = 0, int end = 360, const char* label = 0);
 private:
    virtual void draw() override;
    // begin might be three types
    // 1. fl_begin_points()
    // 2. fl_begin_line()
    // 3. fl_begin_arc()
    Func_Type begin;
    // end might be three types
    // 1. fl_end_points()
    // 2. fl_end_line()
    // 3. fl_begin_arc()
    Func_Type end;
 }; // class Circle

 enum class Circle::Filltype{
    point = 0 ,
    line = 1 ,
    arc = 2 
 };

 /* Circle Reference
 // Draw an arc of points
     fl_begin_points();
     fl_arc(100.0, 100.0, 50.0, 0.0, 180.0);
     fl_end_points();
 // Draw arc with a line
     fl_begin_line();
     fl_arc(200.0, 100.0, 50.0, 0.0, 180.0);
     fl_end_line();
 // Draw filled arc
     fl_begin_polygon();
     fl_arc(300.0, 100.0, 50.0, 0.0, 180.0);
     fl_end_polygon();

 */
 #endif
