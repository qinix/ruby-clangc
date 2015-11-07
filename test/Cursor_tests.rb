#!/usr/bin/env ruby
require "minitest/autorun"
require "clangc"
require "fileutils"
require "#{File.expand_path(File.dirname(__FILE__))}/clangc_utils.rb"

class TestCursorUsage < MiniTest::Test
    include ClangcUtils
  def setup
    @cindex = Clangc::Index.new(false, false)
    system *%W(clang -emit-ast -o #{AST_FILE} #{SOURCE_FILE})
  end
  def teardown
    FileUtils.rm_f(AST_FILE)
  end
  def test_TU_get_cursor
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    assert_instance_of Clangc::Cursor, tu.cursor
  end
  def test_Cursor_is_null
    cursor = Clangc.null_cursor
    assert_equal true, cursor.is_null
  end
  def test_Cursor_is_not_null
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    assert_equal false, tu.cursor.is_null
  end
  def test_Cursor_is_equal
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    cursor = tu.cursor
    cursor1 = tu.cursor
    assert_equal false, cursor.is_equal(Clangc.null_cursor)
    assert_equal true, cursor.is_equal(cursor1)
  end
  def test_Cursor_hash
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    cursor = tu.cursor
    hash = tu.hash
    assert_instance_of Fixnum, hash
  end
  def test_Cursor_get_kind
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      parent_kind_found = false
      cursor_kind_found = false
      Clangc::CursorKind.constants.each do |c|
        if parent.kind == Clangc::CursorKind.const_get(c)
          parent_kind_found = true
        end
        if cursor.kind == Clangc::CursorKind.const_get(c)
          cursor_kind_found = true
        end
      end
      assert_equal true, cursor_kind_found
      assert_equal true, parent_kind_found
    end
  end
  def test_Cursor_get_linkage
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      parent_linkage_found = false
      cursor_linkage_found = false
      Clangc::LinkageKind.constants.each do |l|
        if parent.linkage == Clangc::LinkageKind.const_get(l)
          parent_linkage_found = true
        end
        if cursor.linkage == Clangc::LinkageKind.const_get(l)
          cursor_linkage_found = true
        end
      end
      assert_equal true, cursor_linkage_found
      assert_equal true, parent_linkage_found
    end
  end
  def test_Cursor_get_availability
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      parent_availability_found = false
      cursor_availability_found = false
      Clangc::AvailabilityKind.constants.each do |l|
        if parent.availability == Clangc::AvailabilityKind.const_get(l)
          parent_availability_found = true
        end
        if cursor.availability == Clangc::AvailabilityKind.const_get(l)
          cursor_availability_found = true
        end
      end
      assert_equal true, cursor_availability_found
      assert_equal true, parent_availability_found
    end
  end
  def test_Cursor_get_language
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      parent_language_found = false
      cursor_language_found = false
      Clangc::LanguageKind.constants.each do |l|
        if parent.language == Clangc::LanguageKind.const_get(l)
          parent_language_found = true
        end
        if cursor.language == Clangc::LanguageKind.const_get(l)
          cursor_language_found = true
        end
      end
      assert_equal true, cursor_language_found
      assert_equal true, parent_language_found
    end
  end
  def test_Cursor_get_type
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      assert_instance_of Clangc::Type, cursor.type
      assert_instance_of Clangc::Type, parent.type
    end
  end
  def test_Cursor_get_semantic_parent
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      assert_instance_of Clangc::Cursor, cursor.semantic_parent
      assert_instance_of Clangc::Cursor, parent.semantic_parent
    end
  end
  def test_Cursor_get_lexical_parent
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      assert_instance_of Clangc::Cursor, cursor.lexical_parent
      assert_instance_of Clangc::Cursor, parent.lexical_parent
    end
  end
  def test_Cursor_get_location
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      assert_instance_of Clangc::SourceLocation, cursor.location
      assert_instance_of Clangc::SourceLocation, parent.location
    end
  end
  def test_Cursor_get_extent
  tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      assert_instance_of Clangc::SourceRange, cursor.extent
      assert_instance_of Clangc::SourceRange, parent.extent
    end
  end
  def test_Cursor_get_spelling
  tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      assert_instance_of String, cursor.spelling
      assert_instance_of String, parent.spelling
    end
  end
  def test_Cursor_get_typedef_decl_underlying_type
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      if cursor.kind == Clangc::CursorKind::TYPEDEF_DECL
        assert_instance_of Clangc::Type, cursor.typedef_decl_underlying_type
      end
    end
  end
  def test_Cursor_get_included_file
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      if cursor.kind == Clangc::CursorKind::INCLUSION_DIRECTIVE
        assert_instance_of Clangc::File, cursor.included_file
        assert_equal SOURCE_FILE, cursor.included_file.name
      end
    end
  end
  def test_Cursor_is_declaration
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      if cursor.location.spelling[0].name == SOURCE_FILE && cursor.spelling == "data"
        assert_equal true, cursor.is_declaration, cursor.spelling
      end
      Clangc::ChildVisitResult::RECURSE
    end
  end
  def test_Cursor_is_reference
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      if cursor.location.spelling[0].name == SOURCE_FILE && cursor.spelling == "struct data"
        assert_equal true, cursor.is_reference, cursor.spelling
      end
      Clangc::ChildVisitResult::RECURSE
    end
  end
  def test_Cursor_is_expression
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      if cursor.location.spelling[0].name == SOURCE_FILE && cursor.spelling == "printf"
        assert_equal true, cursor.is_expression, cursor.spelling
      end
      Clangc::ChildVisitResult::RECURSE
    end
  end
  def test_Cursor_is_statement
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      if cursor.location.spelling[0].name == SOURCE_FILE && 
        cursor.location.spelling[1] == 9 && cursor.location.spelling[2] == 28 
        assert_equal true, cursor.is_statement, cursor.location.spelling
      end
      Clangc::ChildVisitResult::RECURSE
    end
  end
  def test_Cursor_is_attribute
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      if cursor.location.spelling[0].name == SOURCE_FILE && 
        cursor.location.spelling[1] == 17 && cursor.location.spelling[2] == 25 
        assert_equal true, cursor.is_attribute, cursor.location.spelling
      end
      Clangc::ChildVisitResult::RECURSE
    end
  end
  def test_Cursor_is_invalid
    assert_equal true, Clangc.null_cursor.is_invalid, "Not null"
  end
  def test_Cursor_is_translation_unit
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    assert_equal true, tu.cursor.is_translation_unit
  end
  def test_Cursor_is_preprocessing
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE_MACRO, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
        assert_equal true, cursor.is_preprocessing, cursor.location.spelling
      Clangc::ChildVisitResult::RECURSE
    end
  end
  def test_Cursor_get_enum_decl_integer_type
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE_ENUM, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      if cursor.kind == Clangc::CursorKind::ENUM_DECL
        assert_instance_of Clangc::Type, cursor.enum_decl_integer_type
        assert_equal Clangc::TypeKind::U_INT, cursor.enum_decl_integer_type.kind, cursor.enum_decl_integer_type.spelling
      end
    end
  end
  def test_Cursor_get_enum_const_decl_value
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE_ENUM, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      if cursor.kind == Clangc::CursorKind::ENUM_CONSTANT_DECL
        case cursor.spelling
        when "RANDOM"
          assert_equal 0, cursor.enum_const_decl_value, cursor.spelling
        when "IMMEDIATE"
          assert_equal 1, cursor.enum_const_decl_value, cursor.spelling
        when "SEARCH"
          assert_equal 2, cursor.enum_const_decl_value, cursor.spelling
        when "HOP"
          assert_equal -1, cursor.enum_const_decl_value, cursor.spelling
        when "TOTO"
          assert_equal -2, cursor.enum_const_decl_value, cursor.spelling
        end
      end
      Clangc::ChildVisitResult::RECURSE
    end
  end
  def test_Cursor_get_enum_const_decl_unsigned_value
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE_ENUM, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      if cursor.kind == Clangc::CursorKind::ENUM_CONSTANT_DECL
        case cursor.spelling
        when "RANDOM"
          assert_equal 0, cursor.enum_const_decl_unsigned_value, cursor.spelling
        when "IMMEDIATE"
          assert_equal 1, cursor.enum_const_decl_unsigned_value, cursor.spelling
        end
      end
      Clangc::ChildVisitResult::RECURSE
    end
  end
  def test_Cursor_get_field_decl_bit_width
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE_STRUCT_BITFIELD, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      if cursor.kind == Clangc::CursorKind::FIELD_DECL
        case cursor.spelling
        when "opaque"
          assert_equal 1, cursor.field_decl_bit_width, cursor.spelling
        when "fill_color"
          assert_equal 3, cursor.field_decl_bit_width, cursor.spelling
        end
      end
      Clangc::ChildVisitResult::RECURSE
    end
  end
  def test_Cursor_get_num_arguments
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent|
      if cursor.kind == Clangc::CursorKind::FUNCTION_DECL 
        case cursor.spelling
        when "stupid_function"
          assert_equal 1, cursor.num_arguments, cursor.spelling
        when "main"
          assert_equal 2, cursor.num_arguments, cursor.spelling
        end
      end
      Clangc::ChildVisitResult::RECURSE
    end
  end
  def test_Cursor_get_argument
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent|
      if cursor.kind == Clangc::CursorKind::FUNCTION_DECL 
        case cursor.spelling
        when "stupid_function"
          arg = cursor.argument(0)
          assert_equal Clangc::TypeKind::DOUBLE, arg.type.kind, arg.type.spelling
        when "main"
          arg = cursor.argument(0)
          assert_equal Clangc::TypeKind::INT, arg.type.kind, arg.type.spelling
        end
      end
      Clangc::ChildVisitResult::RECURSE
    end
  end
  def test_Cursor_get_arguments
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent|
      if cursor.kind == Clangc::CursorKind::FUNCTION_DECL 
        case cursor.spelling
        when "stupid_function"
          args = cursor.arguments
          assert_instance_of Array, args
          assert_equal 1, args.size, args.inspect
          assert_equal Clangc::TypeKind::DOUBLE, args[0].type.kind, args[0].type.spelling
        when "main"
          args = cursor.arguments
          assert_instance_of Array, args
          assert_equal 2, args.size, args.inspect
          assert_equal Clangc::TypeKind::INT, args[0].type.kind, args[0].type.spelling
        end
      end
      Clangc::ChildVisitResult::RECURSE
    end
  end
  def test_Cursor_get_num_template_arguments
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE_FUNCTION_TEMPLATE, ['-x', 'c++'] + CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent|
      if cursor.kind == Clangc::CursorKind::FUNCTION_DECL
        assert_equal 3, cursor.num_template_arguments, cursor.spelling
      end
      Clangc::ChildVisitResult::RECURSE
    end
  end
  def test_Cursor_get_decl_ObjectC_type_encoding
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE_OBJECTC, ['-x', 'objective-c'] + CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent|
      if cursor.location.spelling[0].is_equal(tu.file(SOURCE_FILE_OBJECTC)) &&
         cursor.spelling == "tata"
        assert_equal "i", cursor.decl_objectC_type_encoding, cursor.spelling
      end
      Clangc::ChildVisitResult::RECURSE
    end
  end
  def test_Cursor_get_result_type
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      if cursor.kind == Clangc::CursorKind::FUNCTION_DECL
        if cursor.spelling == "stupid_function"
          assert_instance_of Clangc::Type, cursor.result_type
          assert_equal "int", cursor.result_type.spelling
        end
      end
      Clangc::ChildVisitResult::RECURSE
    end
  end
  def test_Cursor_get_offset_of_field
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent| 
      if cursor.kind == Clangc::CursorKind::FIELD_DECL
        if cursor.spelling == "index"
          assert_equal 0, cursor.offset_of_field
        end
      else
        assert_equal -1, cursor.offset_of_field
      end
      Clangc::ChildVisitResult::RECURSE
    end
  end
  def test_Cursor_is_anonymous
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE_ANON_DECLS, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent|
      if cursor.kind == Clangc::CursorKind::UNION_DECL
        assert_equal false, cursor.is_anonymous, cursor.spelling
      end
      Clangc::ChildVisitResult::RECURSE
    end
  end
  def test_Cursor_is_bit_field
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE_STRUCT_BITFIELD, CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent|
      if cursor.kind == Clangc::CursorKind::FIELD_DECL
        assert_equal true, cursor.is_bit_field, cursor.spelling
      end
      Clangc::ChildVisitResult::RECURSE
    end
  end
  def test_Cursor_is_virtual_base
    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE_VIRT_BASE_CLASS, ['-x', 'c++'] + CLANG_HEADERS_PATH)
    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent|
      if cursor.kind == Clangc::CursorKind::CXX_BASE_SPECIFIER
        if cursor.spelling == "class Animal"
          assert_equal true, cursor.is_virtual_base, cursor.spelling
        else  
          assert_equal false, cursor.is_virtual_base, cursor.spelling
        end
      end
      Clangc::ChildVisitResult::RECURSE
    end
  end
#  def test_Cursor_get_cxx_access_specifier
#    tu = @cindex.create_translation_unit_from_source_file(SOURCE_FILE_VIRT_BASE_CLASS, ['-x', 'c++'] + CLANG_HEADERS_PATH)
#    Clangc.visit_children(cursor: tu.cursor) do |cursor, parent|
#      if cursor.kind == Clangc::CursorKind::CXX_BASE_SPECIFIER
#        if cursor.spelling == "class Animal"
#          assert_equal Clangc::AccessSpecifier::, cursor.is_virtual_base, cursor.spelling
#        else  
#          assert_equal false, cursor.is_virtual_base, cursor.spelling
#        end
#      end
#      Clangc::ChildVisitResult::RECURSE
#    end
#  end
end
