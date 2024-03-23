#include "godot_cpp/core/defs.hpp"
#include "godot_cpp/core/method_ptrcall.hpp"
#include "godot_cpp/variant/callable_custom.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include <cstdint>
#include <godot_cpp/variant/callable_method_pointer.hpp>
#include <utility>

namespace impl {

using namespace godot;

// Func traits
template <typename T>
struct function_traits : public function_traits<decltype(&T::operator())>
{};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const>
{
    using result_type = ReturnType;
    using arg_tuple = std::tuple<Args...>;
    static constexpr auto arity = sizeof...(Args);

	template<class L, std::size_t ... Is>
	_FORCE_INLINE_ static void call(L& l, const Variant **p_arguments, int p_argcount, Variant &r_return_value, GDExtensionCallError &r_call_error, IndexSequence<Is...>) {
#ifdef DEBUG_ENABLED
	if ((size_t)p_argcount > sizeof...(Args)) {
		r_call_error.error = GDEXTENSION_CALL_ERROR_TOO_MANY_ARGUMENTS;
		r_call_error.expected = (int32_t)sizeof...(Args);
		return;
	}

	if ((size_t)p_argcount < sizeof...(Args)) {
		r_call_error.error = GDEXTENSION_CALL_ERROR_TOO_FEW_ARGUMENTS;
		r_call_error.expected = (int32_t)sizeof...(Args);
		return;
	}
#endif

	r_call_error.error = GDEXTENSION_CALL_OK;

#ifdef DEBUG_METHODS_ENABLED
		l(VariantCasterAndValidate<Args>::cast(p_arguments, Is, r_call_error)...);
#else
		l(VariantCaster<Args>::cast(*p_args[Is])...);
#endif
		(void)(p_arguments); // Avoid warning.
	}
};

static void custom_callable_lambda_call(void *p_userdata, const GDExtensionConstVariantPtr *p_args, GDExtensionInt p_argument_count, GDExtensionVariantPtr r_return, GDExtensionCallError *r_error) {
	CallableCustom *callable_method_pointer = (CallableCustom *)p_userdata;
	callable_method_pointer->call((const Variant **)p_args, p_argument_count, *(Variant *)r_return, *r_error);
}

static GDExtensionBool custom_callable_lambda_is_valid(void *p_userdata) {
	CallableCustom *callable_method_pointer = (CallableCustom *)p_userdata;
	ObjectID object = callable_method_pointer->get_object();
	return object == ObjectID() || ObjectDB::get_instance(object);
}

static void custom_callable_lambda_free(void *p_userdata) {
	CallableCustom *callable_method_pointer = (CallableCustom *)p_userdata;
	memdelete(callable_method_pointer);
}

static uint32_t custom_callable_lambda_hash(void *p_userdata) {
	CallableCustom *callable_method_pointer = (CallableCustom *)p_userdata;
	return callable_method_pointer->hash();
}

// TODO: implement
static GDExtensionBool custom_callable_lambda_equal_func(void *p_a, void *p_b) {
	CallableCustom *a = (CallableCustom *)p_a;
	CallableCustom *b = (CallableCustom *)p_b;

	return a->hash() == b->hash();
}

// TODO: implement
static GDExtensionBool custom_callable_lambda_less_than_func(void *p_a, void *p_b) {
	CallableCustom *a = (CallableCustom *)p_a;
	CallableCustom *b = (CallableCustom *)p_b;
	return a->hash() < b->hash();
}

// CallableCustom
template<class Lambda>
class CallableCustomLambda : public CallableCustom {
	Lambda l;
	Object* instance;

public:
	CallableCustomLambda(Object* inst, Lambda&& new_l) : instance(inst), l(new_l) {};
	virtual ~CallableCustomLambda() = default;

	uint32_t hash() const override {
		return (intptr_t)this;
	}

	String get_as_text() const override {
		return "CallableCustomLambda";
	}

	virtual CompareEqualFunc get_compare_equal_func() const override {
		return [](const CallableCustom* a, const CallableCustom* b)
			{
				return a->hash() == b->hash();
			};
	}

	CompareLessFunc get_compare_less_func() const override {
		return [](const CallableCustom* a, const CallableCustom* b)
			{
				return a->hash() < b->hash();
			};
	}

	bool is_valid() const override {
		return instance != nullptr;
	}

	ObjectID get_object() const override {
		return ObjectID();
	}

	void call(const Variant **p_arguments, int p_argcount, Variant &r_return_value, GDExtensionCallError &r_call_error) const override {
		using traits = function_traits<Lambda>;
		traits::call(l, p_arguments, p_argcount, r_return_value, r_call_error, BuildIndexSequence<traits::arity>{});
	}
};
}

// Binding
template <class Lambda>
godot::Callable create_custom_callable_lambda(godot::Object* p_instance, Lambda&& l) {
	auto* ccl = memnew(impl::CallableCustomLambda(p_instance, std::forward<Lambda>(l)));

	GDExtensionCallableCustomInfo info = {};
	info.callable_userdata = ccl;
	info.token = godot::internal::token;
	info.object_id = ccl->get_object();
	info.call_func = &impl::custom_callable_lambda_call;
	info.is_valid_func = &impl::custom_callable_lambda_is_valid;
	info.free_func = &impl::custom_callable_lambda_free;
	info.hash_func = &impl::custom_callable_lambda_hash;
	info.equal_func = &impl::custom_callable_lambda_equal_func;
	info.less_than_func = &impl::custom_callable_lambda_less_than_func;

	godot::Callable callable;
	::godot::internal::gdextension_interface_callable_custom_create(callable._native_ptr(), &info);
	return callable;

}


