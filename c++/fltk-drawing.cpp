/*
 * << FLTK >> Drawing things in FLTK
 */

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/fl_show_colormap.H>
#include <iostream>

uchar rr = 0xff;
uchar gg = 0xff;
uchar bb = 0xff;
void colorCB(Fl_Widget *w, void *v);

class NewDraw : public Fl_Widget {
    public:
        NewDraw(int x, int y, int w, int h, const char *label = (const char *)0);
        ~NewDraw();
        void draw() override;
};

int main(int argc, const char ** argv) {
    Fl_Window win(1000, 800, "Draw everything");
    Fl_Button col_btn(301, 1, 100, 100, "Choose Color!");
    col_btn.callback(colorCB, &win);
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

void colorCB(Fl_Widget *w, void *v) {
    // DEBUG
    std::cout << "DBG : colorCB entered!\n";
    std::cout << "DBG : rr = " << std::hex << (int)rr << '\n';
    std::cout << "DBG : gg = " << std::hex << (int)gg << '\n';
    std::cout << "DBG : bb = " << std::hex << (int)bb << '\n';
    Fl_Window * e = (Fl_Window *) v;
    fl_color_chooser("Select a color!", rr, gg, bb, 2);
    w->color(fl_rgb_color(rr, gg, bb));
    e->color(fl_rgb_color(rr, gg, bb));
    e->redraw();
}