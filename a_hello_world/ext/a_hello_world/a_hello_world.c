#include "a_hello_world.h"

VALUE rb_mAHelloWorld;

// Init_<name of file> => entry point
void
Init_a_hello_world(void)
{
  // ID => represents a ruby symbol
  // rb_intern(Cstr) => converts a C string into a ruby symbol
  ID id_puts = rb_intern("puts");

  // VALUE => represents a ruby object
  // rb_str_new_cstr => create a ruby string
  VALUE hello_world_str = rb_str_new_cstr("Hello world!");

  // rb_funcall => like `Object.send`
  //               - 1: object instance (Kernel)
  //                    - `rb_mKernel` => module Kernel
  //                    - `rb_cInteger` => class Integer
  //               - 2: symbol (:puts)
  //               - 3: number of arguments (1)
  //               - *: arguments ("Hello world!")
  rb_funcall(rb_mKernel, id_puts, 1, hello_world_str);
}
