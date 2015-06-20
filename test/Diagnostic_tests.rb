#!/usr/bin/env ruby
require "minitest/autorun"
require "clangc"
require "fileutils"

class TestDiagnostic < MiniTest::Test
  def setup
    @cindex = Clangc::Index.new(false, false)
    # Good C test file
    @source_file = "#{File.expand_path(File.dirname(__FILE__))}/source1.c"
    # Good C test file with gnu-binary-literal option warning
    @source_file_option_warnings = "#{File.expand_path(File.dirname(__FILE__))}/source_option_warnings.c"
    # C source code with one error
    @source_file_one_error = "#{File.expand_path(File.dirname(__FILE__))}/source2.c"
    # C source code with two error
    @source_file_two_errors = "#{File.expand_path(File.dirname(__FILE__))}/source3.c"
    # Inexistant file
    @bad_file = "#{File.expand_path(File.dirname(__FILE__))}/qsdfqsdf.c"
    @ast_file = "#{File.expand_path(File.dirname(__FILE__))}/source1.ast"
    system *%W(clang -emit-ast -o #{@ast_file} #{@source_file})
    @clang_headers_path = Dir.glob("/usr/lib/clang/*/include").collect {|x| "-I#{x}"}
  end
  def teardown
    FileUtils.rm_f(@ast_file)
  end
  def test_get_diagnostics_array_no_error
    tu = @cindex.create_translation_unit_from_source_file(@source_file,@clang_headers_path)
    diagnostics = tu.diagnostics
    assert_instance_of Array, diagnostics
    assert_equal 0, diagnostics.size
  end
  def test_get_diagnostics_array_one_error
    tu = @cindex.create_translation_unit_from_source_file(@source_file_one_error,@clang_headers_path)
    diagnostics = tu.diagnostics
    assert_instance_of Array, diagnostics
    assert_equal 1, diagnostics.size
  end
  def test_get_diagnostics_array_two_errors
    tu = @cindex.create_translation_unit_from_source_file(@source_file_two_errors,@clang_headers_path)
    diagnostics = tu.diagnostics
    assert_instance_of Array, diagnostics
    assert_equal 2, diagnostics.size
  end
  def test_get_diagnostic_severity_one_error
    tu = @cindex.create_translation_unit_from_source_file(@source_file_one_error,@clang_headers_path)
    diagnostics = tu.diagnostics
    assert_instance_of Fixnum, diagnostics[0].severity
    assert_equal Clangc::DiagnosticSeverity::Error , diagnostics[0].severity
  end
  def test_get_diagnostic_severity_two_errors
    tu = @cindex.create_translation_unit_from_source_file(@source_file_two_errors,@clang_headers_path)
    diagnostics = tu.diagnostics
    assert_instance_of Fixnum, diagnostics[1].severity
    assert_equal Clangc::DiagnosticSeverity::Warning , diagnostics[1].severity
  end
  def test_get_diagnostic_spelling_one_error
    tu = @cindex.create_translation_unit_from_source_file(@source_file_one_error,@clang_headers_path)
    diagnostics = tu.diagnostics
    assert_equal "expected \';\' after top level declarator" , diagnostics[0].spelling
  end
  def test_get_diagnostic_spelling_two_errors
    tu = @cindex.create_translation_unit_from_source_file(@source_file_two_errors,@clang_headers_path)
    diagnostics = tu.diagnostics
    assert_equal "type specifier missing, defaults to \'int\'" , diagnostics[1].spelling
  end
  def test_get_diagnostic_category_one_error
    tu = @cindex.create_translation_unit_from_source_file(@source_file_one_error,@clang_headers_path)
    diagnostics = tu.diagnostics
    assert_equal 4 , diagnostics[0].category
  end
  def test_get_diagnostic_category_two_errors
    tu = @cindex.create_translation_unit_from_source_file(@source_file_two_errors,@clang_headers_path)
    diagnostics = tu.diagnostics
    assert_equal 2 , diagnostics[1].category
  end
  def test_get_diagnostic_category_name_one_error
    tu = @cindex.create_translation_unit_from_source_file(@source_file_one_error,@clang_headers_path)
    diagnostics = tu.diagnostics
    assert_equal "Parse Issue" , diagnostics[0].category_name
  end
  def test_get_diagnostic_category_name_two_errors
    tu = @cindex.create_translation_unit_from_source_file(@source_file_two_errors,@clang_headers_path)
    diagnostics = tu.diagnostics
    assert_equal "Semantic Issue" , diagnostics[1].category_name
  end
  def test_get_diagnostic_category_text_one_error
    tu = @cindex.create_translation_unit_from_source_file(@source_file_one_error,@clang_headers_path)
    diagnostics = tu.diagnostics
    assert_equal "Parse Issue" , diagnostics[0].category_text
  end
  def test_get_diagnostic_category_text_two_errors
    tu = @cindex.create_translation_unit_from_source_file(@source_file_two_errors,@clang_headers_path)
    diagnostics = tu.diagnostics
    assert_equal "Semantic Issue" , diagnostics[1].category_text
  end
  def test_get_diagnostic_num_ranges_one_error
    tu = @cindex.create_translation_unit_from_source_file(@source_file_one_error,@clang_headers_path)
    diagnostics = tu.diagnostics
    assert_equal 0, diagnostics[0].num_ranges
  end
  def test_get_diagnostic_num_ranges_two_errors
    tu = @cindex.create_translation_unit_from_source_file(@source_file_two_errors,@clang_headers_path)
    diagnostics = tu.diagnostics
    assert_equal 1, diagnostics[1].num_ranges
  end
  def test_get_diagnostic_num_fixits_one_error
    tu = @cindex.create_translation_unit_from_source_file(@source_file_one_error,@clang_headers_path)
    diagnostics = tu.diagnostics
    assert_equal 1, diagnostics[0].num_fixits
  end
  def test_get_diagnostic_num_fixits_two_errors
    tu = @cindex.create_translation_unit_from_source_file(@source_file_two_errors,@clang_headers_path)
    diagnostics = tu.diagnostics
    assert_equal 0, diagnostics[1].num_fixits
  end
  def test_format_diagnostic_one_error
    tu = @cindex.create_translation_unit_from_source_file(@source_file_one_error,@clang_headers_path)
    diagnostics = tu.diagnostics
    format = diagnostics[0].format(Clangc.default_diagnostic_display_options)
    assert_instance_of String, format 
#    format = diagnostics[0].format(Clangc::DiagnosticDisplayOptions::Displaysourcelocation)
    format = diagnostics[0].format(0)
    reference = "error: expected \';\' after top level declarator [Parse Issue]"
    assert_equal reference, diagnostics[0].format(Clangc::DiagnosticDisplayOptions::Displaycategoryname)
  end
  def test_get_diagnostic_options
    tu = @cindex.create_translation_unit_from_source_file(@source_file_option_warnings,@clang_headers_path + %w(-Wall -pedantic))
    assert_equal 20, tu.diagnostics.size
    assert_equal "-Wgnu-binary-literal", tu.diagnostics[15].option[0]
    assert_equal "-Wno-gnu-binary-literal", tu.diagnostics[15].option[1]
  end
  def test_get_diagnostic_range
    tu = @cindex.create_translation_unit_from_source_file(@source_file_two_errors,@clang_headers_path)
    diagnostics = tu.diagnostics
    range_number = tu.diagnostics[1].num_ranges
    assert_instance_of Clangc::SourceRange , diagnostics[1].source_range(range_number - 1)
  end
  def test_get_diagnostic_ranges
    tu = @cindex.create_translation_unit_from_source_file(@source_file_two_errors,@clang_headers_path)
    diagnostics = tu.diagnostics
    range_number = tu.diagnostics[1].num_ranges
    source_ranges = diagnostics[1].source_ranges
    assert_equal range_number, source_ranges.size
    assert_instance_of Clangc::SourceRange, source_ranges[range_number - 1]
  end
end
