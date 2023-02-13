#include "e_variables.h"

VALUE rb_mEVariables;

///
/// Instance Variables
/// ==================
///
/// You can "hide" instance variables from Ruby if you
/// define them without the "@" prefix.
///
/// 1. Setting instance variables
/// -----------------------------
///
/// ```c
/// VALUE rb_ivar_set(VALUE obj, ID id, VALUE val);
///
/// // Setting `@foo` in `my_obj` to `my_var`
/// ID iv_foo = rb_intern("@foo"); // Symbol :@foo
/// rb_ivar_set(my_obj, iv_foo, my_var);
///
/// // Set a "hidden" instance variable named `foo`
/// ID id_foo = rb_intern("foo"); // Symbol :foo
/// rb_ivar_set(my_obj, id_foo, my_var);
/// ```
///
/// 2. Getting instance variables
/// -----------------------------
///
/// ```c
/// VALUE rb_ivar_get(VALUE obj, ID id);
///
/// // Getting `@foo` in `my_obj`
/// ID iv_foo = rb_intern("@foo"); // Symbol :@foo
/// VALUE my_ivar = rb_ivar_get(my_obj, iv_foo);
/// ```
///
/// Class Variables
/// ===============
///
/// You can "hide" class variables from Ruby if you
/// define them without the "@@" prefix.
///
/// 1. Setting class variables
/// --------------------------
///
/// ```c
/// VALUE rb_cvar_set(VALUE klass, ID id, VALUE val);
///
/// // Setting `@@foo` in `my_klass` to `my_var`
/// ID cv_foo = rb_intern("@@foo"); // Symbol :@@foo
/// rb_cvar_set(my_klass, cv_foo, my_var);
/// ```
///
/// 2. Getting class variables
/// --------------------------
///
/// ```c
/// VALUE rb_cvar_get(VALUE klass, ID id);
///
/// // Getting `@@foo` in `my_klass`
/// ID cv_foo = rb_intern("@@foo"); // Symbol :@@foo
/// VALUE my_cvar = rb_ivar_get(my_klass, cv_foo);
/// ```
///
///
/// 3. Check if a class variable is defined
/// ---------------------------------------
///
/// ```c
/// // Will return `Qtrue` or `Qfalse`
/// VALUE rb_cvar_defined(VALUE klass, ID id);
///
/// // Checking `@@foo` in `my_klass`
/// ID cv_foo = rb_intern("@@foo"); // Symbol :@@foo
/// if (rb_ivar_defined(my_klass, cv_foo) == Qtrue) {
///   // @@foo exists in my_klass
/// } else {
///   // @@foo does not exist in my_klass
/// }
/// ```
///
///
/// Constants
/// =========
///
/// ```c
/// void rb_const_set(VALUE klass, ID id, VALUE val);
///
/// // Setting top-level constant ::MY_CONST to my_val
/// rb_const_set(rb_cObject, rb_intern("MY_CONST"), my_val);
/// ```
///
/// ```c
/// VALUE rb_const_get(VALUE klass, ID id);
///
/// // Getting top-level constant ::Foo
/// VALUE foo = rb_const_get(rb_cObject, rb_intern("Foo"));
///
/// // Getting constant Foo::Bar
/// VALUE bar = rb_const_get(foo, rb_intern("Bar"));
/// ```
///
///
/// Globals
/// =======
///
/// ```c
/// void rb_gv_set(const char *name, VALUE val);
///
/// // Setting global variable $foo to my_var
/// rb_gv_set("$foo", my_var);
/// ```
///
/// ```c
/// VALUE rb_gv_get(const char *name);
///
/// // Getting global variable $foo
/// VALUE my_var = rb_gv_get("$foo");
/// ```
///

void
Init_e_variables(void)
{
  rb_mEVariables = rb_define_module("EVariables");
}
