#include "CHOE/Window.h"

int main()
{
    using namespace Graph_lib;
    Point tl {100, 100};
	Window win{tl, 640, 480, "hello"};
	return Fl::run();
}
