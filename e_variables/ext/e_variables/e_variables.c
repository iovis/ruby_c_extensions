#include "e_variables.h"

VALUE rb_mEVariables;

void
Init_e_variables(void)
{
  rb_mEVariables = rb_define_module("EVariables");
}
