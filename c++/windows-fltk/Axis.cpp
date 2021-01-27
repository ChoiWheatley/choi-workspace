#include "Axis.h"

Axis::Axis(int x, int y, int length, int notches, orientation o, const char* label) :
	Fl_Widget{ x, y, length, length, label }, length_{ length }, notches_{ notches }, o_{ o }
{}

void Axis::setcolor(Fl_Color bg)
{
	color_ = bg;
	redraw();
}

void Axis::draw() {
	// first draw vertically, next rotate whether orientation is x
	int x = this->x();
	int y = this->y();
	fl_color(color_);
	switch (o_) {
	case orientation::x:
	{
		fl_line(x, y, x, y + width_);
		fl_line(x, y + width_, x + length_, y + width_);
		fl_line(x + length_, y + width_, x + length_, y);
		for (int i = 0; i < notches_; i++) {
			static int sum = 0; 
			static int len = length_;
			sum += static_cast<int>(len / (notches_ - i));
			len = length_ - sum;
			fl_line(x + sum, y + width_, x + sum, y);
		}
		fl_draw(label(), x + static_cast<int>(length_ / 2), y + width_ * 2);
		break;
	}
	case orientation::y:
	{
		fl_line(x, y, x + width_, y);
		fl_line(x, y, x, y + length_);
		fl_line(x, y + length_, x + width_, y + length_);
		for (int i = 0; i < notches_; i++) {
			static int sum = 0;
			static int len = length_;
			sum += static_cast<int>(len / (notches_ - i));
			len = length_ - sum;
			fl_line(x, y + sum, x + width_, y + sum);
		}
		fl_draw(label(), x - sizeof(label()), y - fl_height());
		break;
	}
	}
}
