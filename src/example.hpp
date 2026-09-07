#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <cppscript.h>

class Example : public godot::Label {
	GCLASS(Example, godot::Label);
public:

	GPROPERTY(set_button, get_button);
	bool button;
	void set_button(bool){
		godot::UtilityFunctions::print("Pressed!");
	};

	void do_something();
};
