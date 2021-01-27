#include "Function.h"

Function::Function(double (*funcptr)(double x),
	int range_min, int range_max,
	int pnt_x, int pnt_y,
	int accuracy,
	int scale_x, int scale_y) :
	Fl_Widget(pnt_x, pnt_y - scale_y, range_max* scale_x, scale_y * 2, 0),
	funcptr_{funcptr},
	range_min_{range_min}, range_max_{range_max},
	pnt_x_{pnt_x}, pnt_y_{pnt_y},
	accuracy_{accuracy},
	scale_x_{scale_x},
	scale_y_{scale_y}
{
}

void Function::draw() {
	// TODO
	// 1. draw just sine wave with the parameter "accuracy"
	// 2. offset sine wave
	// 3. scale sine wave
	fl_color(color_);
	fl_line_style(line_style_, line_width_);
	for (int i = 0; i < accuracy_; i++) {
		static double x = 0, y = ((*funcptr_)(0)), dx = 0, dy = ((*funcptr_)(0));
		dx = (x + ((double)range_max_ - (double)range_min_ + i) / (double)accuracy_);
		dy = ((*funcptr_)(dx));
		fl_line(offset(x, pnt_x_, scale_x_),
			offset(y, pnt_y_, scale_y_),
			offset(dx, pnt_x_, scale_x_),
			offset(dy, pnt_y_, scale_y_)
		);
		/*
		const int setwsize = std::to_string(accuracy_).size();
		std::cout << "(i)(x, y, dx, dy) = (" << std::setw(setwsize) << i << ") (" << 
			offset(x, pnt_x_, scale_x_) << ", " << 
			offset(y, pnt_y_, scale_y_) << ", " << 
			offset(dx, pnt_x_, scale_x_) << ", " << 
			offset(dy, pnt_y_, scale_y_) << ")\n";
		*/
		x = dx;
		y = dy;
	}
}
