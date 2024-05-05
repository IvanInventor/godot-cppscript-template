#include "cppscript_defs.h"
#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/classes/texture.hpp"
#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/variant/typed_array.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/compressed_texture2d.hpp>

#include <godot_cpp/classes/resource_loader.hpp>

#include <godot_cpp/classes/file_access.hpp>


#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>

#include <godot_cpp/classes/gd_script.hpp>

#include <godot_cpp/classes/material.hpp>

#include <godot_cpp/templates/hash_map.hpp>

#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/scene_tree_timer.hpp>

#include <cppscript.h>

#include <godot_cpp/core/error_macros.hpp>

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/engine.hpp>

#include <godot_cpp/classes/image.hpp>

#include <godot_cpp/classes/tree.hpp>

#include "callable_lambda.hpp"
#include <godot_cpp/variant/utility_functions.hpp>

class MyRes : public godot::Resource {
	GCLASS(MyRes, godot::Resource);
};

class Example : public godot::Node {
public:
	enum enum_example {
		a = 1,
		b = 2,
		c = 3,
	};

	GPROPERTY(set_barr, get_barr);
	godot::PackedByteArray barr;

	GPROPERTY(test_var, get_var);
	godot::Variant var;

	void test_var(godot::Variant var) {
		ERR_FAIL_COND_MSG(var.get_type() == godot::Variant::NIL, "ERROR TYPE");
	}

	GVARARG();
	void varargs_func_void(const godot::Variant **args, GDExtensionInt arg_count, GDExtensionCallError &error) {};
	GVARARG(String str);
	void varargs_func_void2(const godot::Variant **args, GDExtensionInt arg_count, GDExtensionCallError &error) {};
	GVARARG(str, String newstr);
	void varargs_func_void3(const godot::Variant **args, GDExtensionInt arg_count, GDExtensionCallError &error) {};

	void get_ref(const godot::Array& arr) {
		godot::Array n = arr;
		n.append(123);
	};
	GPROPERTY(set_material, get_material);
	godot::Ref<godot::Material> material;

	GPROPERTY(set_p, get_p);
	godot::Ref<godot::Texture> p;

	GPROPERTY(set_t, get_t,
			none, "");
	godot::Ref<godot::GDScript> t;

	GPROPERTY(set_str, get_str,
			none, "", PROPERTY_USAGE_NO_EDITOR, "");
	godot::String str = "124525";

	GPROPERTY(set_arr, get_arr,
			array_type, "MyRes", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_ARRAY);
	godot::TypedArray<MyRes> arr;


		GSTATIC_MEMBER(godot::String, static_str, "123456");

	GSTATIC_MEMBER(Node*, nodeptr, nullptr);
	GSTATIC_MEMBER(godot::Ref<godot::CompressedTexture2D>, preload, godot::ResourceLoader::get_singleton()->load("res://icon.png"));

	void exposed_method() {};
	godot::Ref<godot::CompressedTexture2D> get_preload() {
		return  preload;
	}

	void _ready() override {
		godot::Callable c = create_custom_callable_lambda(this, 
			[](const godot::Ref<godot::InputEvent>& i)
				{
				godot::UtilityFunctions::print(i);
				}
		);
		connect("renamed", c);
		disconnect("renamed", c);
	}

	void _input(const godot::Ref<godot::InputEvent>& ev) override {
		std::vector<uint8_t> data(10, 3);
		godot::PackedByteArray packet;
		packet.resize(data.size());
		std::memcpy(packet.ptrw(), data.data(), data.size());
		godot::UtilityFunctions::print(packet);

		int i = 42;
		if(godot::Input::get_singleton()->is_action_just_pressed(SNAME("act"))) {
			auto timer = get_tree()->create_timer(1);
			timer->connect(
				"timeout",
				create_custom_callable_lambda(this, [=](int arg)
					{
						WARN_PRINT("STRINGGGGGGGGG");
						godot::UtilityFunctions::print("Warning\n""\x20\x20\x20""at: ggg (secec.main.cpp)");
						godot::UtilityFunctions::print_rich("[color=yellow]* Warning");
						/*
						godot::UtilityFunctions::print("Called before process, i = ", i, ", arg = ", arg);
						godot::Array list = timer->get_signal_connection_list("timeout");
						godot::UtilityFunctions::print(godot::Callable(godot::Dictionary(list[0])["callable"]));
						Node* child = find_child("Label2");
						ERR_FAIL_NULL(child);
						child->print_tree();
						*/

					})
				.bind(100),
				ConnectFlags::CONNECT_ONE_SHOT);

				get_viewport()->set_input_as_handled();
		}
	}

	GIGNORE();
	void do_thing(int i) {};
	GIGNORE();
	void do_thing(godot::Vector2i i){};

	GCLASS(Example, godot::Node);
};

class GInput : public godot::Tree {
public:
	void _gui_input(const godot::Ref<godot::InputEvent>& event) override {
		godot::UtilityFunctions::print(event);
		if(event->is_pressed()) {};
	}

	GCLASS(GInput, godot::Tree);
};


class Plug : public godot::EditorPlugin {
	GEDITOR_PLUGIN();

public:
	Plug() {
		godot::UtilityFunctions::print("Plugin Enabled");
	}

	godot::String _get_plugin_name() const override {
		return "PluginName";
	}
	void _enable_plugin() override {
		godot::UtilityFunctions::print("Plugin Enabled");
	}

	GCLASS(Plug, godot::EditorPlugin);
};

class CT : public godot::Node {
	GCLASS(CT, godot::Node);

	CT() {
		if(godot::Engine::get_singleton()->is_editor_hint())
			return;
		godot::UtilityFunctions::print("Constructed");
	}
};

