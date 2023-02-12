# frozen_string_literal: true

RSpec.describe DPrimitiveDataTypes do
  describe ".create_array_of_strings" do
    subject { create_array_of_strings }

    it do
      is_expected.to eq %w[
        one
        two
        three
      ]
    end
  end

  describe ".reversed_string" do
    subject { reversed_string(string) }

    let(:string) { "Hello, World!" }

    it { is_expected.to eq "!dlroW ,olleH" }
  end
end
