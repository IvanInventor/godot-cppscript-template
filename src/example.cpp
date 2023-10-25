#include <godot_cpp/variant/utility_functions.hpp>

#include "example.hpp"

using namespace godot;

void Example::do_something() {
	set_text("Check console");
	UtilityFunctions::print("GDExtension working!");
}
