/*
 * ruby-clangc ruby bindings for the C interface of Clang
 * Copyright (C) 2015  cedlemo <cedlemo@gmx.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*Cursor ruby class*/
#include "class_Cursor.h"
#include "class_Type.h"
#include "class_SourceLocation.h"
#include "class_SourceRange.h"
#include "class_File.h"
#include "macros.h"

static void
c_Cursor_struct_free(Cursor_t *s)
{
  if(s)
  {
    ruby_xfree(s);
  }
}  

static void
c_Cursor_mark(void *s)
{
  if(s)
  {
    Cursor_t *t =(Cursor_t *)s;
    rb_gc_mark(t->parent);
  }
}

VALUE
c_Cursor_struct_alloc( VALUE klass)
{
  
  Cursor_t * ptr;
  ptr = (Cursor_t *) ruby_xmalloc(sizeof(Cursor_t)); 
  ptr->parent = Qnil;

  return Data_Wrap_Struct(klass, NULL, c_Cursor_struct_free, (void *) ptr);
}

/**
* call-seq:
*   Clangc::Cursor#is_null => true /false
*
*   return true is the cursor is a null Cursor or false otherwise
*/
VALUE
c_Cursor_is_null(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  if(clang_Cursor_isNull(c->data) != 0)
    return Qtrue;
  else
    return Qfalse;
}

/**
* call-seq:
*   Clangc::Cursor#is_equal(cursor1) => true/false
*
* Determine whether two cursors are equivalent.
*/
VALUE
c_Cursor_is_equal(VALUE self, VALUE cursor1)
{
  Cursor_t *c;
  Cursor_t *c1;

  Data_Get_Struct(self, Cursor_t, c);
  Data_Get_Struct(cursor1, Cursor_t, c1);

  if(clang_equalCursors(c->data, c1->data) != 0)
    return Qtrue;
  else
    return Qfalse;
}

/**
* call-seq:
*   Clangc::Cursor#hash => Fixnum
*
* Compute a hash value for the given cursor.
*/
VALUE
c_Cursor_get_hash(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return CUINT_2_NUM(clang_hashCursor(c->data)); 
}

/**
* call-seq:
*   Clangc::Cursor#kind => Fixnum
*
* Retrieve the kind of the given cursor.
* The value should refer to the constants in
* Clangc::CursorKind
*/
VALUE
c_Cursor_get_kind(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return CUINT_2_NUM(clang_getCursorKind(c->data)); 
}

/**
* call-seq:
*   Clangc::Cursor#linkage => Fixnum
*
* Determine the linkage of the entity referred to by a given cursor.
* The value should refer to the constants in
* Clangc::LinkageKind
*/
VALUE
c_Cursor_get_linkage(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return CUINT_2_NUM(clang_getCursorLinkage(c->data)); 
}

/**
* call-seq:
*   Clangc::Cursor#availability => Fixnum
*
* Determine the availability of the entity that this cursor refers to,
* taking the current target platform into account.
*
* The availability of the cursor.
* The value should refer to the constants in
* Clangc::AvailabilityKind
*/
VALUE
c_Cursor_get_availability(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return CUINT_2_NUM(clang_getCursorAvailability(c->data)); 
}

/**
* call-seq:
*   Clangc::Cursor#language => Fixnum
*
* Determine the "language" of the entity referred to by a given cursor.
* The value should refer to the constants in
* Clangc::LanguageKind
*/
VALUE
c_Cursor_get_language(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return CUINT_2_NUM(clang_getCursorLanguage(c->data));
}

/**
* call-seq:
*   Clangc::Cursor#type => Clangc::Type
*
* Retrieve the type of a CXCursor (if any).
*/
VALUE
c_Cursor_get_type(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  Type_t *t;
  VALUE type;
  R_GET_CLASS_DATA("Clangc", "Type", type, Type_t, t);
  t->data = clang_getCursorType(c->data);
  t->parent = self;
  return type;
}

/**
* call-seq:
*   Clangc::Cursor#semantic_parent => Clangc::Cursor
*
* Determine the semantic parent of the given cursor.
*
* The semantic parent of a cursor is the cursor that semantically contains
* the given cursor. For many declarations, the lexical and semantic parents
* are equivalent (the lexical parent is returned by 
* Clang::Cursor#lexical_parent). They diverge when declarations or
* definitions are provided out-of-line. For example:
*
*     class C {
*      void f();
*     };
*    
*     void C::f() { }
*
* In the out-of-line definition of "C::f", the semantic parent is
* the class "C", of which this function is a member. The lexical parent is
* the place where the declaration actually occurs in the source code; in this
* case, the definition occurs in the translation unit. In general, the
* lexical parent for a given entity can change without affecting the semantics
* of the program, and the lexical parent of different declarations of the
* same entity may be different. Changing the semantic parent of a declaration,
* on the other hand, can have a major impact on semantics, and redeclarations
* of a particular entity should all have the same semantic context.
*
* In the example above, both declarations of "C::f" have "C" as their
* semantic context, while the lexical context of the first "C::f" is "C"
* and the lexical context of the second "C::f" is the translation unit.
*
* For global declarations, the semantic parent is the translation unit.
*/
VALUE
c_Cursor_get_semantic_parent(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  Cursor_t *s;
  VALUE sem_par;
  R_GET_CLASS_DATA("Clangc", "Cursor", sem_par, Cursor_t, s);
  s->data = clang_getCursorSemanticParent(c->data);
  s->parent = c->parent;
  return sem_par;
}

/**
* call-seq:
*   Clangc::Cursor#lexical_parent => Clangc::Cursor
*
* Determine the lexical parent of the given cursor.
*
* The lexical parent of a cursor is the cursor in which the given cursor
* was actually written. For many declarations, the lexical and semantic parents
* are equivalent (the semantic parent is returned by 
* Clangc::Cursor#semantic_parent). They diverge when declarations or
* definitions are provided out-of-line. For example:
*
*     class C {
*      void f();
*     };
*    
*     void C::f() { }
*
* In the out-of-line definition of "C::f", the semantic parent is
* the class "C", of which this function is a member. The lexical parent is
* the place where the declaration actually occurs in the source code; in this
* case, the definition occurs in the translation unit. In general, the
* lexical parent for a given entity can change without affecting the semantics
* of the program, and the lexical parent of different declarations of the
* same entity may be different. Changing the semantic parent of a declaration,
* on the other hand, can have a major impact on semantics, and redeclarations
* of a particular entity should all have the same semantic context.
*
* In the example above, both declarations of "C::f" have "C" as their
* semantic context, while the lexical context of the first "C::f" is "C"
* and the lexical context of the second "C::f" is the translation unit.
*
* For declarations written in the global scope, the lexical parent is
* the translation unit.
*/
VALUE
c_Cursor_get_lexical_parent(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  Cursor_t *l;
  VALUE lex_par;
  R_GET_CLASS_DATA("Clangc", "Cursor", lex_par, Cursor_t, l);
  l->data = clang_getCursorLexicalParent(c->data);
  l->parent = c->parent;
  return lex_par;
}

/**
* call-seq:
*   Clangc::Cursor#location => Clangc::SourceLocation
*
* Retrieve the physical location of the source constructor referenced
* by the given cursor.
*
* The location of a declaration is typically the location of the name of that
* declaration, where the name of that declaration would occur if it is
* unnamed, or some keyword that introduces that particular declaration.
* The location of a reference is where that reference occurs within the
* source code.
*/
VALUE
c_Cursor_get_source_location(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  SourceLocation_t *s;
  VALUE src_loc;
  R_GET_CLASS_DATA("Clangc", "SourceLocation", src_loc, SourceLocation_t, s);
  s->data = clang_getCursorLocation(c->data);
  s->parent = self;
  return src_loc;
}

/**
* call-seq:
*   Clangc::Cursor#extent => Clangc::SourceRange
*
* Retrieve the physical extent of the source construct referenced by
* the given cursor.
*
* The extent of a cursor starts with the file/line/column pointing at the
* first character within the source construct that the cursor refers to and
* ends with the last character within that source construct. For a
* declaration, the extent covers the declaration itself. For a reference,
* the extent covers the location of the reference (e.g., where the referenced
* entity was actually used).
*/
VALUE
c_Cursor_get_extent(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  SourceRange_t *s;
  VALUE src_rge;
  R_GET_CLASS_DATA("Clangc", "SourceRange", src_rge, SourceRange_t, s);
  s->data = clang_getCursorExtent(c->data);
  s->parent = self;
  return src_rge;
}

/**
* call-seq:
*   Clangc::Cursor#spelling => String
*
* Retrieve a name for the entity referenced by this cursor.
*/
VALUE
c_Cursor_get_spelling(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  CXString str = clang_getCursorSpelling(c->data);
  VALUE spelling = rb_str_new2( clang_getCString(str) );
  clang_disposeString(str);
  return spelling;
}

/**
* call-seq:
*   Clangc::Cursor#typedef_decl_underlying_type => Clangc::Type
*
* Retrieve the underlying type of a typedef declaration.
*
* If the cursor does not reference a typedef declaration, an invalid type is
* returned.
*/
VALUE
c_Cursor_get_typedef_decl_underlying_type(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  Type_t *t;
  VALUE type;
  R_GET_CLASS_DATA("Clangc", "Type", type, Type_t, t);
  t->data = clang_getTypedefDeclUnderlyingType(c->data);
  t->parent = c->parent;
  return type;
}

/**
* call-seq:
*   Clangc::Cursor#included_file => Clangc::File
*
* Retrieve the file that is included by the given inclusion directive
* cursor.
*/
VALUE
c_Cursor_get_included_file(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  VALUE included;
  File_t *f;
  R_GET_CLASS_DATA("Clangc", "File", included, File_t, f);
  f->data = clang_getIncludedFile(c->data);
  f->parent = c->parent;
  return included;
}

/**
* call-seq:
*   Clangc::Cursor#is_declaration => true/false
*
* Determine whether the given cursor kind represents a declaration.
*/
VALUE
c_Cursor_is_declaration(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return clang_isDeclaration(clang_getCursorKind(c->data)) == 0 ? Qfalse : Qtrue;
}

/**
* call-seq:
*   Clangc::Cursor#is_reference => true/false
*
* Determine whether the given cursor kind represents a simple
* reference.
*
* Note that other kinds of cursors (such as expressions) can also refer to
* other cursors. Use Clangc::Curosr#cursor_referenced to determine whether a
* particular cursor refers to another entity.
*/
VALUE
c_Cursor_is_reference(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return clang_isReference(clang_getCursorKind(c->data)) == 0 ? Qfalse : Qtrue;
}

/**
* call-seq:
*   Clangc::Cursor#is_expression => true/false
*
* Determine whether the given cursor kind represents an expression.
*/
VALUE
c_Cursor_is_expression(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return clang_isExpression(clang_getCursorKind(c->data)) == 0 ? Qfalse : Qtrue;
}

/**
* call-seq:
*   Clangc::Cursor#is_statement => true/false
*
* Determine whether the given cursor kind represents a statement.
*/
VALUE
c_Cursor_is_statement(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return clang_isStatement(clang_getCursorKind(c->data)) == 0 ? Qfalse : Qtrue;
}

/**
* call-seq:
*   Clangc::Cursor#is_attribute => true/false
*
* Determine whether the given cursor kind represents an attribute.
*/
VALUE
c_Cursor_is_attribute(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return clang_isAttribute(clang_getCursorKind(c->data)) == 0 ? Qfalse : Qtrue;
}

/**
* call-seq:
*   Clangc::Cursor#is_invalid => true/false
*
* Determine whether the given cursor kind represents an invalid
* cursor.
*/
VALUE
c_Cursor_is_invalid(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return clang_isInvalid(clang_getCursorKind(c->data)) == 0 ? Qfalse : Qtrue;
}

/**
* call-seq:
*   Clangc::Cursor#is_translation_unit => true/false
*
* Determine whether the given cursor kind represents a translation
* unit.
*/
VALUE
c_Cursor_is_translation_unit(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return clang_isTranslationUnit(clang_getCursorKind(c->data)) == 0 ? Qfalse : Qtrue;
}

/**
* call-seq:
*   Clangc::Cursor#is_preprocessing => true/false
*
* Determine whether the given cursor represents a preprocessing
* element, such as a preprocessor directive or macro instantiation.
*/
VALUE
c_Cursor_is_preprocessing(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return clang_isPreprocessing(clang_getCursorKind(c->data)) == 0 ? Qfalse : Qtrue;
}
/**
* call-seq:
*   Clangc::Cursor#enum_integer_type => Clangc::Type
*
* Retrieve the integer type of an enum declaration.
*
* If the cursor does not reference an enum declaration, an invalid type is
* returned.
*/
VALUE
c_Cursor_get_enum_decl_integer_type(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  Type_t *t;
  VALUE type;
  R_GET_CLASS_DATA("Clangc", "Type", type, Type_t, t);
  t->data = clang_getEnumDeclIntegerType(c->data);
  t->parent = c->parent;
  return type;
}

/**
* call-seq:
*   Clangc::Cursor#enum_const_decl_value => Number
*
* Retrieve the integer value of an enum constant declaration as a signed
* long long.
*
* If the cursor does not reference an enum constant declaration, ULLONG_MIN is returned.
* Since this is also potentially a valid constant value, the kind of the cursor
* must be verified before calling this function.
*/
VALUE
c_Cursor_get_enum_const_decl_value(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return CLLONG_2_NUM(clang_getEnumConstantDeclValue(c->data));
}

/**
* call-seq:
*   Clangc::Cursor#enum_const_decl_unsigned_value => Number
*
* Retrieve the integer value of an enum constant declaration as an unsigned
* long long.
*
* If the cursor does not reference an enum constant declaration, ULLONG_MAX is returned.
* Since this is also potentially a valid constant value, the kind of the cursor
* must be verified before calling this function.
*/
VALUE
c_Cursor_get_enum_const_decl_unsigned_value(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return CULLONG_2_NUM(clang_getEnumConstantDeclUnsignedValue(c->data));
}

/**
* call-seq:
*   Clangc::Cursor#field_decl_bit_width => Integer
*
* Retrieve the bit width of a bit field declaration as an integer.
*
* If a cursor that is not a bit field declaration is passed in, -1 is returned.
*/
VALUE
c_Cursor_get_field_decl_bit_width(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return CINT_2_NUM(clang_getFieldDeclBitWidth(c->data));
}

/**
* call-seq:
*   Clangc::Cursor#num_arguments => Integer
*
* Retrieve the number of non-variadic arguments associated with a given
* cursor.
*
* The number of arguments can be determined for calls as well as for
* declarations of functions or methods. For other cursors -1 is returned.
*/
VALUE
c_Cursor_get_num_arguments(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return CINT_2_NUM(clang_Cursor_getNumArguments(c->data));
}

/**
* call-seq:
*   Clangc::Cursor#get_argument(index) => Clangc::Cursor
*
* Retrieve the argument cursor of a function or method.
*
* The argument cursor can be determined for calls as well as for declarations
* of functions or methods. For other cursors and for invalid indices, an
* invalid cursor is returned.
*/
VALUE
c_Cursor_get_argument(VALUE self, VALUE index)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  int max = clang_Cursor_getNumArguments(c->data);
  if(max < 0)
    max = 0;
  unsigned int c_index;
  RNUM_2_UINT(index, c_index);
  CHECK_IN_RANGE(c_index, 0, max);
  Cursor_t *a;
  VALUE arg;
  R_GET_CLASS_DATA("Clangc", "Cursor", arg, Cursor_t, a);
  a->data = clang_Cursor_getArgument(c->data, c_index);
  a->parent = c->parent;
  return arg;
}

/**
* call-seq:
*   Clangc::Cursor#num_template_arguments => Integer
*
* Returns the number of template args of a function decl representing a
* template specialization.
*
* If the argument cursor cannot be converted into a template function
* declaration, -1 is returned.
*
* For example, for the following declaration and specialization:

*    template <typename T, int kInt, bool kBool>
*    void foo() { ... }
*    
*    template <>
*    void foo<float, -7, true>();
*
* The value 3 would be returned from this call.
*/
VALUE
c_Cursor_get_num_template_arguments(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return CINT_2_NUM(clang_Cursor_getNumTemplateArguments(c->data));  
}
/**
* call-seq:
*   Clangc::Cursor#decl_objectC_type_encoding => string
*
* Returns the Objective-C type encoding for the specified declaration.
*/
VALUE
c_Cursor_get_decl_objectC_type_encoding(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  CXString str = clang_getDeclObjCTypeEncoding(c->data);
  VALUE type_encoding = rb_str_new2( clang_getCString(str) );
  clang_disposeString(str);
  return type_encoding;
}

/**
* call-seq:
*   Clangc::Cursor#result_tye => Clangc::Type
*
* Retrieve the return type associated with a function type.
*
* If a non-function type is passed in, an invalid type is returned.
*/
VALUE
c_Cursor_get_result_type(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  Type_t *t;
  VALUE result_type;
  R_GET_CLASS_DATA("Clangc", "Type", result_type, Type_t, t);
  t->data = clang_getCursorResultType(c->data);
  t->parent = self;
  return result_type;
}

/**
* call-seq:
*   Clangc::Cursor#offset_field => Integer
*
* Return the offset of the field represented by the Cursor.
*
* If the cursor is not a field declaration, -1 is returned.
* If the cursor semantic parent is not a record field declaration,
* Clangc::TypeLayoutError::INVALID is returned.
* If the field's type declaration is an incomplete type,
* Clangc::TypeLayoutError::INCOMPLETE is returned.
* If the field's type declaration is a dependent type,
* Clangc::TypeLayoutError::DEPENDENT is returned.
* If the field's name S is not found,
* Clangc::TypeLayoutError::INVALIDfIELD_NAME is returned.
*/
VALUE
c_Cursor_get_offset_of_field(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return CLLONG_2_NUM(clang_Cursor_getOffsetOfField(c->data));
}

/**
* call-seq:
*   Clangc::Cursor#is_anonymous => true / false
*
* Determine whether the given cursor represents an anonymous record
* declaration.
*/
VALUE
c_Cursor_is_anonymous(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  
  if(clang_Cursor_isAnonymous(c->data) != 0)
    return Qtrue;
  else
    return Qfalse;
}

/**
* call-seq:
*   Clangc::Cursor#is_bit_field => true/false
*
* Returns true if the cursor specifies a Record member that is a
* bitfield.
*/
VALUE
c_Cursor_is_bit_field(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);

  if(clang_Cursor_isBitField(c->data) != 0)
    return Qtrue;
  else
    return Qfalse;
}

/**
* call-seq:
*   Clangc::Cursor#is_virtual_base => true/false
*
* Returns true if the base class specified by the cursor with kind
* Clangc::CursorKind::CXX_BASE_SPECIFIER is virtual.
*/
VALUE
c_Cursor_is_virtual_base(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);

  if(clang_isVirtualBase(c->data) == 1)
    return Qtrue;
  else
    return Qfalse;
}

/**
* call-seq:
*   Clangc::Cursor#cxx_access_specifier =>  Clangc::CXXAccessSpecifier.constants
*
* Returns the access control level for the referenced object. 
* The returned value is one of the Clangc::CXXAccesSpecifier.constants.
* It represents the C++ access control level to a base class for a
* cursor with kind Clangc::Cursor::CXX_BASE_SPECIFIER.
*
* If the cursor refers to a C++ declaration, its access control level within its
* parent scope is returned. Otherwise, if the cursor refers to a base specifier or
* access specifier, the specifier itself is returned.
*/
VALUE
c_Cursor_get_cxx_access_specifier(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return CUINT_2_NUM(clang_getCXXAccessSpecifier(c->data));  
}
/**
* call-seq:
*   Clangc::Cursor#storage_class => Clangc::StorageClass.constants
*
* Returns the storage class for a function or variable declaration.
*
* If the passed in Cursor is not a function or variable declaration,
* Clangc::StorageClass::SC_INVALID is returned else the storage class.
*/
VALUE
c_Cursor_get_storage_class(VALUE self)
{
  Cursor_t *c;
  Data_Get_Struct(self, Cursor_t, c);
  return CUINT_2_NUM(clang_Cursor_getStorageClass(c->data));  
}
