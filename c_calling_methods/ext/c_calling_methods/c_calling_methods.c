#include "c_calling_methods.h"
#include "ruby/internal/eval.h"
#include "ruby/internal/iterator.h"
#include "ruby/internal/value.h"

VALUE rb_mCCallingMethods;

/// Calling methods
/// ===============
///
/// `rb_funcall` => Like Object#send(:method, args), but you need to know the
/// number of arguments ahead of time
///
/// Example:
/// ```c
/// // Calling Kernel#puts with three arguments a, b, and c
/// rb_funcall(rb_mKernel, rb_intern("puts"), 3, a, b, c);
/// ```
///
/// Calling methods with variable arguments
/// =======================================
///
/// `rb_funcallv` => call with C arrays
/// - recv: receiver object
/// - mid: method name as an ID symbol
/// - argc: number of arguments
/// - argv: pointer to the arguments
///
/// Example:
/// ```c
/// // Kernel#puts with 3 args in a C array allocated on the stack
/// VALUE argv[3] = { a, b, c };
/// rb_funcallv(rb_mKernel, rb_intern("puts"), 3, argv);
/// ```
///
/// `rb_apply` => call with Ruby arrays
/// - recv: receiver object
/// - mid: method name as an ID symbol
/// - args: the Ruby array of arguments
///
/// Example:
/// ```c
/// // Kernel#puts with `my_array` splatted
/// VALUE my_array = ...; // Ruby array
/// rb_apply(rb_mKernel, rb_intern("puts"), my_array);
/// ```
///
/// `rb_funcallv_kw` => call with Ruby arrays
/// * first 3 args same as `rb_funcallv`
/// - kw_splat: whether to use the last argument of `argv` as keyword arguments
///     - RB_PASS_KEYWORDS => yes
///     - RB_NO_KEYWORDS => no (same as rb_funcallv)
///
/// Example:
/// ```c
/// // Kernel#puts with two positional arguments and keyword arguments
/// VALUE my_hash = ...; // Ruby hash
/// VALUE argv[3] = { a, b, my_hash };
/// rb_funcallv_kw(rb_mKernel, rb_intern("puts"), 3, argv, RB_PASS_KEYWORDS);
/// ```
///
///
/// Calling methods with a block
/// ============================
///
/// `rb_block_call` => call a method with a block
/// * first 4 args same as `rb_funcallv`
/// - bl_proc: the C function that implements the block
///     - VALUE block_callback(VALUE yielded_arg, VALUE callback_arg, int argc,
///                            const VALUE *argv, VALUE blockarg)
///     - yielded_arg: first arg that is yielded to the block
///     - callback_arg: value that is passed into `data2` during the
///     `rb_block_call`
///     - argc: number of arguments yielded into the block (including
///     `yielded_arg`)
///     - argv: The C array of arguments yielded to the block (including
///     `yielded_arg`)
///     - blockarg: the block that is passed into this block
/// - data2: any data that you want to pass into the block

static VALUE
puts_every_other_block(VALUE yielded_arg, VALUE data, int argc, const VALUE *argv, VALUE blockarg)
{
  // Cast the data back to a pointer
  int *puts_curr_ptr = (int *)data;
  int puts_curr = *puts_curr_ptr;

  if (puts_curr) {
    rb_funcall(rb_mKernel, rb_intern("puts"), 1, yielded_arg);
  }

  *puts_curr_ptr = !puts_curr;

  return Qnil;
}

static VALUE
puts_every_other(VALUE self)
{
  int puts_curr = 1;

  // Call Array#each with block
  // NOTE: `VALUE` is an `unsigned long`, so you can just pass a pointer to something
  rb_block_call(self, rb_intern("each"), 0, NULL, puts_every_other_block, (VALUE)&puts_curr);

  return Qnil;
}

void
Init_c_calling_methods(void)
{
  // rb_mCCallingMethods = rb_define_module("CCallingMethods");

  rb_define_method(rb_cArray, "puts_every_other", puts_every_other, 0);
}
