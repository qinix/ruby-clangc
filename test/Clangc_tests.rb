#!/usr/bin/env ruby
require "minitest/autorun"
require "clangc"

class TestClangcMethods < MiniTest::Test
  def test_clangc_version
    assert_instance_of String, Clangc.version
  end
  def test_clangc_default_diagnostic_display_options
    assert_instance_of Fixnum, Clangc.default_diagnostic_display_options
    default_display_options = Clangc::DiagnosticDisplayOptions::Displaysourcelocation|
                              Clangc::DiagnosticDisplayOptions::Displaycolumn|
                              Clangc::DiagnosticDisplayOptions::Displayoption
    assert_equal default_display_options, Clangc.default_diagnostic_display_options
  end
  def test_clangc_default_editing_translation_unit_options
    assert_instance_of Fixnum, Clangc.default_editing_translation_unit_options
  end
  def test_clangc_default_code_complete_options
    assert_instance_of Fixnum, Clangc.default_code_complete_options
  end
  def test_clangc_null_range
    assert_instance_of Clangc::SourceRange, Clangc.null_source_range
  end
  def test_clangc_null_location
    assert_instance_of Clangc::SourceLocation, Clangc.null_source_location
  end
  def test_clangc_null_cursor
    assert_instance_of Clangc::Cursor, Clangc.null_cursor
  end
end
