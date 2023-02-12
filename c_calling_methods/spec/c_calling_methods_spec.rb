# frozen_string_literal: true

RSpec.describe CCallingMethods do
  describe "Array#puts_every_other" do
    # class Array
    #   def puts_every_other
    #     puts_curr = true
    #     each do |e|
    #       puts e if puts_curr
    #       puts_curr = !puts_curr
    #     end
    #   end
    # end

    it "puts every other value" do
      %w[one two three four five].puts_every_other
      %w[one two three four].puts_every_other
      [].puts_every_other
    end
  end
end
