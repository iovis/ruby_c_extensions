#include "d_primitive_data_types.h"

VALUE rb_mDPrimitiveDataTypes;

///
/// Primitive Data Types
/// ====================
///
/// Heap allocated primitive types (managed by garbage collector):
/// - Array
/// - Bignum
/// - Class
/// - Complex
/// - File
/// - Float
/// - Hash
/// - MatchData
/// - Object
/// - Rational
/// - Regexp
/// - String
/// - Struct
/// - Symbol
///
/// Immediates (not allocated):
/// - Fixnum (small int)
/// - nil, true, false
///
///
/// Constants
/// =========
///
/// - rb_m: Ruby core modules (rb_mKernel)
/// - rb_c: classes (rb_cObject)
/// - rb_e: exceptions (rb_eRuntimeError)
///
/// * The list of builtin modules, classes and exceptions is here:
#include "ruby/internal/globals.h"

///
/// Special Constants
/// =================
///
/// - Qnil: Ruby `nil`
/// - Qtrue: Ruby `true`
/// - Qfalse: Ruby `false`
///
/// You can test them with the `RTEST` macro:
///
/// ```c
/// VALUE my_obj = ...;
/// if (RTEST(my_obj)) {
///     // my_obj is not Qfalse or Qnil
/// } else {
///     // my_obj is either Qfalse or Qnil
/// }
/// ```
///

///
/// Fixnum
/// ======
///
/// There used to be Fixnum and Bignum in Ruby, but nowadays
/// it's only Integer.
///
/// In the C api the two types still exist because they are
/// represented differently.
///
/// You can convert between C `long` and Ruby `Fixnum`:
///
/// ```c
/// // C long -> Ruby Fixnum
/// VALUE zero_ruby = LONG2FIX(0);
///
/// // Ruby Fixnum -> C long
/// long zero_c = FIX2LONG(zero_ruby);
/// ```
///

///
/// Arrays
/// ======
#include "ruby/internal/intern/array.h"
///
/// 1. Create Arrays
/// ----------------
///
/// - `rb_ary_new`: create a new, empty Ruby array
/// ```c
/// VALUE my_arr = rb_ary_new();
/// ```
///
/// - `rb_ary_new_capa`: create a new, empty Ruby array with capacity
/// ```c
/// VALUE my_arr = rb_ary_new_capa(100);
/// ```
///
/// 2. Adding to arrays
/// -------------------
///
/// - `rb_ary_push`: add one element and return array
/// ```c
/// VALUE my_arr = rb_ary_new();
/// rb_ary_push(my_array, LONG2FIX(42));
/// ```
///
/// - `rb_ary_cat`: add a C array to a Ruby array
/// ```c
/// VALUE my_arr = rb_ary_new_capa(100);
/// VALUE ruby_constants[3] = { Qtrue, Qfalse, Qnil };
/// rb_ary_cat(my_array, ruby_constants, 3);
/// ```
///
/// 3. Removing from arrays
/// -------------------
///
/// - `rb_ary_pop`
/// - `rb_ary_shift`
///
///
/// 4. Indexing arrays
/// ------------------
///
/// - `RARRAY_LEN`: get length of a Ruby array
/// - `RARRAY_PTR`: get backing C array pointer of a Ruby array
/// - `RARRAY_AREF`: get element at specific index of a Ruby array
///
/// ```c
/// // Get the length of my_array
/// long len = RARRAY_LEN(my_array);
///
/// // Get the backing C array of my_array
/// VALUE *elements = RARRAY_PTR(my_array);
///
/// // Read the first element of my_array
/// VALUE first_element = elements[0];
///
/// // Set the 42nd element to the fixnum 0
/// elements[41] = LONG2FIX(0);
///
/// // Another way to read the first element of my_array
/// VALUE first_element = RARRAY_AREF(my_array, 0);
/// ```
/// * SAFETY:
///   - Ruby may decide to reallocate or garbage collect, invalidating the
///     pointers
///   - RARRAY_AREF does not do bound checking
///

///
/// Hashes
/// ======
#include "ruby/internal/intern/hash.h"
///
/// 1. Create hashes
/// ----------------
///
/// - `rb_hash_new`: create a new, empty Ruby hash
/// ```c
/// VALUE my_hash = rb_hash_new();
/// ```
///
///
/// 2. Add to hash
/// ----------
/// - `rb_hash_aset`:
/// ```c
/// rb_hash_aset(my_hash, my_key, my_value);
/// ```
///
///
/// 3. Look up
/// ----------
/// - `rb_hash_aref`:
/// ```c
/// VALUE my_val = rb_hash_aref(my_hash, my_key);
/// ```
///
///
/// 4. Iterating
/// ------------
/// - `rb_hash_foreach`:
/// ```c
/// // Iterate over every key/value pair in my_hash
/// int my_hash_iter_func(VALUE key, VALUE value, VALUE arg) {
///     // Implementation goes here
///
///     // the `return` value has to be one of the following:
///     // - ST_CONTINUE => continue iteration
///     // - ST_STOP     => stop iteration
///     // - ST_DELETE   => delete the current entry
///     return ST_CONTINUE;
/// }
///
/// rb_hash_foreach(my_hash, my_hash_iter_func, 0);
/// ```
///

///
/// Strings
/// =======
#include "ruby/internal/intern/string.h"
///
/// 1. Create strings
/// -----------------
///
/// - `VALUE rb_str_new(const char *ptr, long len)`
/// ```c
/// char *c_str = malloc(13);
/// strcpy(c_str, "Hello world!");
/// VALUE my_string = rb_str_new(c_str, 12); // copies the string
/// free(c_str); // can be freed after
/// ```
///
/// - `VALUE rb_str_new_static(const char *ptr, long len)`
/// ```c
/// VALUE my_string = rb_str_new_static("Hello world!", 12);
/// // Uses a reference, doesn't allocate extra memory
/// // Don't free the pointer!
/// ```
///
/// - `VALUE rb_str_buf_new(long capacity)`
/// ```c
/// // Can grow if it exceeds capacity
/// VALUE my_string = rb_str_buf_new(12);
/// rb_str_cat_cstr(my_string, "Hello world!");
/// ```
///
/// 2. Appending to strings
/// -----------------------
///
/// - `VALUE rb_str_cat(VALUE str, const char *ptr, long len)`
/// ```c
/// // Appending "Hello world!" to a Ruby string my_string
/// size_t string_length = 12;
/// char *c_str = malloc(string_length);
///
/// // The C string c_str may or may not contain a null terminator
/// memcpy(c_str, "Hello world!", string_length);
/// rb_str_cat(my_string, c_string, string_length);
/// free(c_str);
/// ```
///
/// - `VALUE rb_str_cat_cstr(VALUE str, const char *ptr)`
/// ```c
/// // Appending "Hello world!" to a Ruby string my_string
/// // The CStr has to be null terminated
/// rb_str_cat_cstr(my_string, "Hello world!");
/// ```
///
/// 3. Reading and writing strings
/// ------------------------------
///
/// - `RSTRING_LEN`: get length of a Ruby string (like String#bytesize)
/// - `StringValuePtr`: get backing C pointer of a Ruby string
/// - `StringValueCStr`: get backing C character buffer
///
/// ```c
/// // Get the length of my_string
/// long length = RSTRING_LEN(my_string);
///
/// // Get the backing C character array
/// char *buff = StringValuePtr(my_string);
///
/// // Change the 11th character of my_string to 'a'
/// buff[10] = 'a';
/// ```
///

///
/// Symbols
/// =======
#include "ruby/internal/symbol.h"
///
/// 1. Creating Ruby symbols
/// ------------------------
///
/// ID is not a VALUE, so we can't pass it back to Ruby, we have
/// to convert it into a VALUE
///
/// ```c
/// ID hello = rb_intern("hello");
/// VALUE hello_symbol = rb_id2sym(hello);
/// ```
///

///
/// Checking Types
/// ==============
#include "ruby/internal/value_type.h"
///
/// - `bool RB_TYPE_P(VALUE obj, enum ruby_value_type type)`
/// ```c
/// if (RB_TYPE_P(my_obj, T_FIXNUM)) {
///   // my_obj is a Ruby Fixnum
/// } else {
///   // my_obj is not a Ruby Fixnum
/// }
/// ```
///
/// - `void Check_Type(VALUE obj, enum ruby_value_type type)`
/// ```c
/// // Will `raise TypeError` if it fails
/// Check_Type(my_obj, T_FIXNUM);
/// // my_obj is a Ruby Fixnum
/// ```
///

void
Init_d_primitive_data_types(void)
{
  rb_define_module("DPrimitiveDataTypes");
}
