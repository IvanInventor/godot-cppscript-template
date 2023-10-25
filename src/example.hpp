#include <godot_cpp/classes/label.hpp>

#include <cppscript.h>

class Example : public godot::Label {

public:

	void do_something();

	GCLASS(Example, godot::Label);
};
