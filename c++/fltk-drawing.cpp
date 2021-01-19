/*
 * << FLTK >> Drawing things in FLTK
 */

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Enumerations.H>

class NewDraw : public Fl_Widget {
    public:
        NewDraw(int x, int y, int w, int h, const char *label = (const char *)0);
        ~NewDraw();
        void draw() override;
};

int main(int argc, const char ** argv) {
    Fl_Window win(1000, 800, "Draw everything");
    NewDraw d{0, 0, 1000, 800};
    d.draw();
    win.show();
    return Fl::run();
}

NewDraw::NewDraw(int x, int y, int w, int h, const char *label) :
    Fl_Widget(x, y, w, h, label)
{}
NewDraw::~NewDraw() {  }
void NewDraw::draw() {
    // add clip
    // you can limit all your drawing to a rectangular region.
    // if you draw anything out of this region,,, Segmentation fault 
    // will occur. 왜만든거야
    //fl_push_clip(1, 1, 100, 200);
    // draw box
    fl_draw_box(Fl_Boxtype::FL_UP_BOX, 1, 1, 99, 99, FL_RED);
    // draw frame
    fl_frame("XXAA",1, 101, 99, 99);
    // pop clip back
    // so you can draw outside
    //fl_pop_clip();
    fl_draw_box(FL_UP_BOX, 1, 201, 99, 99, FL_BLUE);

    //colorpaletes 
    constexpr int startx = 101;
    constexpr int starty = 1;
    constexpr int side = 10;
    Fl_Color c = 0;
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 8; j++) {
            fl_draw_box(Fl_Boxtype::FL_THIN_UP_BOX,
                        startx + (j * side),
                        starty + (i * side), 
                        side,
                        side,
                        c++ 
            );
        }
    }
}