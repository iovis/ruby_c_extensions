# frozen_string_literal: true

RSpec.describe BDefiningMethods do
  describe "Object#my_fixed_args_method" do
    it { "a".my_fixed_args_method(1, "arg 2") }
  end

  describe "Object#my_var_args_c_array_method" do
    it { "a".my_var_args_c_array_method(1, "arg 2", :arg3) }
  end

  describe "Object#my_var_args_rb_array_method" do
    it { "a".my_var_args_rb_array_method(1, "arg 2", :arg3) }
  end

  describe "Object#my_method_with_required_block" do
    it do
      my_method_with_required_block do
        "my block"
      end
    end
  end
end
