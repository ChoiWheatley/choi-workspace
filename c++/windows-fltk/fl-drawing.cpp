/*
 * <FLTK> Drawing Things in FLTK
 *
 * < Author > ChoiWheatley
 * < Doc Link > https://www.fltk.org/doc-1.3/drawing.html
 *
 * < ToDo >
 * <> Mac Visual Studio 설치하여 해당 리포지토리 끌어와서 fltk 빌드 가능한지 확인하기
 *
 *
 * < History >
 * 2021. 01. 21.
 *	-- 윈도우에서 fltk 재도전 하기. Visual Studio에서 제대로 돌아간다.
 *	-- 목표 : [ Drawing Fast Shapes ] & [ Drawing Complex Shapes ] & [ Drawing Text ] & [ Fonts ]
 * 
 * < Compile Options via Visual Studio >
 * reference from : https://alf-p-steinbach.github.io/Install-FLTK-for-use-with-Visual-C-/
 * 
 */

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Window.H>

class MyWindow : public Fl_Window {
public:
	MyWindow(int w, int h, const char* label = 0) : Fl_Window{ w, h, label } {}
	~MyWindow() {}
	virtual void draw() override;
private:
};

int main(int argc, char** argv)
{
	MyWindow* win = new MyWindow(640, 480, "My Window");
	// ToDo : Write down your own code below
	win->show();
	return Fl::run();
}

void MyWindow::draw()
{
	Fl_Window::draw();
	fl_draw_box(Fl_Boxtype::FL_UP_BOX, 1, 1, 99, 99, FL_BLUE);
	fl_frame("AAXX", 1, 101, 99, 99);
	fl_line_style(FL_CAP_FLAT | FL_DASHDOTDOT, 10);

	fl_rectf(1, 201, 99, 99, FL_RED);
	fl_line_style(0);
}




