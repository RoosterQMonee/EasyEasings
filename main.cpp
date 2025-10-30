#include "EasyEasings.h"
#include <iostream>

int main() {
	float t = 0.25f;
	float y1 = easing::in_quad<float>(t);          // use direct function
	double y2 = easing::evaluate<double>(easing::Ease::OutElastic, 0.6);
	std::cout << y1 << " " << y2 << "\n";
}
