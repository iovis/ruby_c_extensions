#include "d_primitive_data_types.h"

VALUE rb_mDPrimitiveDataTypes;

void
Init_d_primitive_data_types(void)
{
  rb_mDPrimitiveDataTypes = rb_define_module("DPrimitiveDataTypes");
}
