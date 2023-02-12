#include "c_calling_methods.h"

VALUE rb_mCCallingMethods;

void
Init_c_calling_methods(void)
{
  rb_mCCallingMethods = rb_define_module("CCallingMethods");
}
