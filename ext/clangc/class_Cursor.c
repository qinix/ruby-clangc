/*
 * ruby-clangc ruby bindings for the C interface of Clang
 * Copyright (C) 2015-2016 Cedric Le Moigne cedlemo <cedlemo@gmx.com>
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
#include "class_CompletionString.h"
#include "class_TranslationUnit.h"
#include "class_OverriddenCursor.h"
#include "class_Module.h"
#include "macros.h"

static void c_Cursor_struct_free(Cursor_t *s)
{
    if (s)
    {
        ruby_xfree(s);
    }
}

static void c_Cursor_mark(void *s)
{
    if (s)
    {
        Cursor_t *t = (Cursor_t *) s;
        rb_gc_mark(t->parent);
    }
}

VALUE
c_Cursor_struct_alloc(VALUE klass)
{

    Cursor_t *ptr;
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
    return NOT_0_2_RVAL(clang_Cursor_isNull(c->data));
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
    CHECK_ARG_TYPE(cursor1, Cursor);
    Data_Get_Struct(cursor1, Cursor_t, c1);

    return NOT_0_2_RVAL(clang_equalCursors(c->data, c1->data));
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
    R_GET_CLASS_DATA("Clangc", Type, type, t);
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
    R_GET_CLASS_DATA("Clangc", Cursor, sem_par, s);
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
    R_GET_CLASS_DATA("Clangc", Cursor, lex_par, l);
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
    R_GET_CLASS_DATA("Clangc", SourceLocation, src_loc, s);
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
    R_GET_CLASS_DATA("Clangc", SourceRange, src_rge, s);
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
    return CXSTR_2_RVAL(clang_getCursorSpelling(c->data));
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
    R_GET_CLASS_DATA("Clangc", Type, type, t);
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
    R_GET_CLASS_DATA("Clangc", File, included, f);
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
    return NOT_0_2_RVAL(clang_isDeclaration(clang_getCursorKind(c->data)));
}

/**
* call-seq:
*   Clangc::Cursor#is_reference => true/false
*
* Determine whether the given cursor kind represents a simple
* reference.
*
* Note that other kinds of cursors (such as expressions) can also refer to
* other cursors. Use Clangc::Cursor#cursor_referenced to determine whether a
* particular cursor refers to another entity.
*/
VALUE
c_Cursor_is_reference(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return NOT_0_2_RVAL(clang_isReference(clang_getCursorKind(c->data)));
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
    return NOT_0_2_RVAL(clang_isExpression(clang_getCursorKind(c->data)));
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
    return NOT_0_2_RVAL(clang_isStatement(clang_getCursorKind(c->data)));
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
    return NOT_0_2_RVAL(clang_isAttribute(clang_getCursorKind(c->data)));
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
    return NOT_0_2_RVAL(clang_isInvalid(clang_getCursorKind(c->data)));
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
    return NOT_0_2_RVAL(clang_isTranslationUnit(clang_getCursorKind(c->data)));
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
    return NOT_0_2_RVAL(clang_isPreprocessing(clang_getCursorKind(c->data)));
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
    R_GET_CLASS_DATA("Clangc", Type, type, t);
    t->data = clang_getEnumDeclIntegerType(c->data);
    t->parent = c->parent;
    return type;
}

/**
* call-seq:
*   Clangc::Cursor#enum_const_decl_value => Fixnum
*
* Retrieve the integer value of an enum constant declaration as a signed
* long long.
*
* If the cursor does not reference an enum constant declaration, ULLONG_MIN is
* returned.
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
*   Clangc::Cursor#enum_const_decl_unsigned_value => Fixnum
*
* Retrieve the integer value of an enum constant declaration as an unsigned
* long long.
*
* If the cursor does not reference an enum constant declaration, ULLONG_MAX is
* returned.
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
*   Clangc::Cursor#field_decl_bit_width => Fixnum
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
*   Clangc::Cursor#num_arguments => Fixnum
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
    if (max < 0) max = 0;
    unsigned int c_index = NUM2UINT(index);
    CHECK_IN_RANGE(c_index, 0, max);
    Cursor_t *a;
    VALUE arg;
    R_GET_CLASS_DATA("Clangc", Cursor, arg, a);
    a->data = clang_Cursor_getArgument(c->data, c_index);
    a->parent = c->parent;
    return arg;
}

#if (CINDEX_VERSION_MINOR >= 29)
/**
* call-seq:
*   Clangc::Cursor#num_template_arguments => Fixnum
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
#endif

/**
* call-seq:
*   Clangc::Cursor#decl_objectC_type_encoding => string
*
* Returns the Objective-C type encoding for the specified declaration.
*/
VALUE
c_Cursor_get_decl_obj_c_type_encoding(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return CXSTR_2_RVAL(clang_getDeclObjCTypeEncoding(c->data));
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
    R_GET_CLASS_DATA("Clangc", Type, result_type, t);
    t->data = clang_getCursorResultType(c->data);
    t->parent = self;
    return result_type;
}

#if (CINDEX_VERSION_MINOR >= 30)
/**
* call-seq:
*   Clangc::Cursor#offset_field => Fixnum
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
    return NOT_0_2_RVAL(clang_Cursor_isAnonymous(c->data));
}
#endif

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
    return NOT_0_2_RVAL(clang_Cursor_isBitField(c->data));
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

    return EQ_1_2_RVAL(clang_isVirtualBase(c->data));
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
* parent scope is returned. Otherwise, if the cursor refers to a base specifier
* or
* access specifier, the specifier itself is returned.
*/
VALUE
c_Cursor_get_cxx_access_specifier(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return CUINT_2_NUM(clang_getCXXAccessSpecifier(c->data));
}

#if (CINDEX_VERSION_MINOR >= 29)
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
#endif
/**
* call-seq:
*   Clangc::Cursor#num_overloaded_decls => Fixnum >= 0
*
* Determine the number of overloaded declarations referenced by a
* Clangc::CursorKind::OVERLOADED_DECL_REF cursor.
*
* The number of overloaded declarations referenced by cursor. If it
* is not a Clangc::CursorKind::OVERLOADED_DECL_REF cursor, returns 0.
*/
VALUE
c_Cursor_get_num_overloaded_decls(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return CUINT_2_NUM(clang_getNumOverloadedDecls(c->data));
}

/**
* call-seq:
*   Clangc::Cursor#overloaded_decl(index) => Clangc::Cursor
*
* Retrieve a cursor for one of the overloaded declarations referenced
* by a Clangc::CursorKind::OVERLOADED_DECL_REF cursor.
*
* index The zero-based index into the set of overloaded declarations in
* the cursor.
*
* Returns a cursor representing the declaration referenced by the given
* cursor at the specified index. If the cursor does not have an
* associated set of overloaded declarations, or if the index is out of bounds,
* returns a nul cursor;
*/
VALUE
c_Cursor_get_overloaded_decl(VALUE self, VALUE index)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    unsigned int c_index = NUM2UINT(index);
    Cursor_t *o;
    VALUE overl_decl;
    R_GET_CLASS_DATA("Clangc", Cursor, overl_decl, o);
    o->data = clang_getOverloadedDecl(c->data, c_index);
    o->parent = c->parent;
    return overl_decl;
}
/**
* call-seq:
*   Clangc::Cursor#display_name => String
*
* Retrieve the display name for the entity referenced by this cursor.
*
* The display name contains extra information that helps identify the cursor,
* such as the parameters of a function or template or the arguments of a
* class template specialization.
*/
VALUE
c_Cursor_get_display_name(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return CXSTR_2_RVAL(clang_getCursorDisplayName(c->data));
}

/**
* call-seq:
*   Clangc::Cursor#ib_outlet_collection_type => Clangc::Type
*
* For cursors representing an iboutletcollection attribute,
*  this function returns the collection element type.
*/
VALUE
c_Cursor_get_ib_outlet_collection_type(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    Type_t *t;
    VALUE collection_type;
    R_GET_CLASS_DATA("Clangc", Type, collection_type, t);
    t->data = clang_getIBOutletCollectionType(c->data);
    t->parent = self;
    return collection_type;
}

/**
* call-seq:
*   Clangc::Cursor#usr => String
*
* Retrieve a Unified Symbol Resolution (USR) for the entity referenced
* by the given cursor.
*
* A Unified Symbol Resolution (USR) is a string that identifies a particular
* entity (function, class, variable, etc.) within a program. USRs can be
* compared across translation units to determine, e.g., when references in
* one translation refer to an entity defined in another translation unit.
*/
VALUE
c_Cursor_get_usr(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return CXSTR_2_RVAL(clang_getCursorUSR(c->data));
}
/**
* call-seq:
*   Clangc::Cursor#referenced => Clangc::Cursor
*
* For a cursor that is a reference, retrieve a cursor representing the
* entity that it references.
*
* Reference cursors refer to other entities in the AST. For example, an
* Objective-C superclass reference cursor refers to an Objective-C class.
* This function produces the cursor for the Objective-C class from the
* cursor for the superclass reference. If the input cursor is a declaration or
* definition, it returns that declaration or definition unchanged.
* Otherwise, returns the NULL cursor.
*/
VALUE
c_Cursor_get_referenced(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    Cursor_t *r;
    VALUE referenced;
    R_GET_CLASS_DATA("Clangc", Cursor, referenced, r);
    r->data = clang_getCursorReferenced(c->data);
    r->parent = c->parent;
    return referenced;
}

/**
* call-seq:
*   Clangc::Cursor#definition => Clangc::Cursor
*
* For a cursor that is either a reference to or a declaration
* of some entity, retrieve a cursor that describes the definition of
* that entity.
*
* Some entities can be declared multiple times within a translation
* unit, but only one of those declarations can also be a
* definition. For example, given:
*
*     int f(int, int);
*     int g(int x, int y) { return f(x, y); }
*     int f(int a, int b) { return a + b; }
*     int f(int, int);
*
* there are three declarations of the function "f", but only the
* second one is a definition. The clang_getCursorDefinition()
* function will take any cursor pointing to a declaration of "f"
* (the first or fourth lines of the example) or a cursor referenced
* that uses "f" (the call to "f' inside "g") and will return a
* declaration cursor pointing to the definition (the second "f"
* declaration).
*
* If given a cursor for which there is no corresponding definition,
* e.g., because there is no definition of that entity within this
* translation unit, returns a NULL cursor.
*/
VALUE
c_Cursor_get_definition(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    Cursor_t *d;
    VALUE definition;
    R_GET_CLASS_DATA("Clangc", Cursor, definition, d);
    d->data = clang_getCursorDefinition(c->data);
    d->parent = c->parent;
    return definition;
}

/**
* call-seq:
*   Clangc::Cursor#is_definition => true/false
*
* Determine whether the declaration pointed to by this cursor
* is also a definition of that entity.
*/
VALUE
c_Cursor_is_definition(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return NOT_0_2_RVAL(clang_isCursorDefinition(c->data));
}

/**
* call-seq:
*   Clangc::Cursor#canonical_cursor => Clangc::Cursor
*
* Retrieve the canonical cursor corresponding to the given cursor.
*
* In the C family of languages, many kinds of entities can be declared several
* times within a single translation unit. For example, a structure type can
* be forward-declared (possibly multiple times) and later defined:
*
*   struct X;
*   struct X;
*   struct X {
*     int member;
*   };
*
* The declarations and the definition of \c X are represented by three
* different cursors, all of which are declarations of the same underlying
* entity. One of these cursor is considered the "canonical" cursor, which
* is effectively the representative for the underlying entity. One can
* determine if two cursors are declarations of the same underlying entity by
* comparing their canonical cursors.
*
* It returns The canonical cursor for the entity referred to by the given
* cursor.
*/
VALUE
c_Cursor_get_canonical_cursor(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    Cursor_t *cc;
    VALUE canonical_cursor;
    R_GET_CLASS_DATA("Clangc", Cursor, canonical_cursor, cc);
    cc->data = clang_getCanonicalCursor(c->data);
    cc->parent = c->parent;
    return canonical_cursor;
}
/**
* call-seq:
*   Clangc::Cursor#obj_c_selector_index => Fixnum
*
* If the cursor points to a selector identifier in an Objective-C
* method or message expression, this returns the selector index.
*
* After getting a cursor with #clang_getCursor, this can be called to
* determine if the location points to a selector identifier.
*
* It returns The selector index if the cursor is an Objective-C method or
* message
* expression and the cursor is pointing to a selector identifier, or -1
* otherwise.
*/
VALUE
c_Cursor_get_obj_c_selector_index(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return CINT_2_NUM(clang_Cursor_getObjCSelectorIndex(c->data));
}
/**
* call-seq:
*   Clangc::Cursor#is_dynamic_call => true/ false
*
* Given a cursor pointing to a C++ method call or an Objective-C
* message, returns non-zero if the method/message is "dynamic", meaning:
*
* For a C++ method: the call is virtual.
* For an Objective-C message: the receiver is an object instance, not 'super'
* or a specific class.
*
* If the method/message is "static" or the cursor does not point to a
* method/message, it will return zero.
*/
VALUE
c_Cursor_is_dynamic_call(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return NOT_0_2_RVAL(clang_Cursor_isDynamicCall(c->data));
}
/**
* call-seq:
*   Clangc::Cursor#receiver_type => Clangc::Type
*
* Given a cursor pointing to an Objective-C message, returns the CXType
* of the receiver.
*/
VALUE
c_Cursor_get_receiver_type(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    Type_t *t;
    VALUE receiver_type;
    R_GET_CLASS_DATA("Clangc", Type, receiver_type, t);
    t->data = clang_Cursor_getReceiverType(c->data);
    t->parent = self;
    return receiver_type;
}
/**
* call-seq:
*   Clangc::Cursor#obj_c_decl_qualifiers => Fixnum

* \brief Given a cursor that represents an Objective-C method or parameter
* declaration, return the associated Objective-C qualifiers for the return
* type or the parameter respectively. The bits are formed from
* Clangc::ObjCDeclQualifierKind constants.
*/
VALUE
c_Cursor_get_obj_c_decl_qualifiers(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return CUINT_2_NUM(clang_Cursor_getObjCDeclQualifiers(c->data));
}

/**
* call-seq:
*   Clangc::Cursor#is_obj_c_optional => true / false
*
* Given a cursor that represents an Objective-C method or property
* declaration, return non-zero if the declaration was affected by "@optional".
* Returns zero if the cursor is not such a declaration or it is "@required".
*/
VALUE
c_Cursor_is_obj_c_optional(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return NOT_0_2_RVAL(clang_Cursor_isObjCOptional(c->data));
}
/**
* call-seq:
*   Clangc::Cursor#is_variadic => true / false
*
* Returns non-zero if the given cursor is a variadic function or method.
*/
VALUE
c_Cursor_is_variadic(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return NOT_0_2_RVAL(clang_Cursor_isVariadic(c->data));
}
/**
* call-seq:
*   Clangc::Cursor#comment_range => Clangc::SourceRange
*
* Given a cursor that represents a declaration, return the associated
* comment's source range.  The range may include multiple consecutive comments
* with whitespace in between.
*/
VALUE
c_Cursor_get_comment_range(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    SourceRange_t *s;
    VALUE cmt_rge;
    R_GET_CLASS_DATA("Clangc", SourceRange, cmt_rge, s);
    s->data = clang_Cursor_getCommentRange(c->data);
    s->parent = self;
    return cmt_rge;
}
/**
* call-seq:
*   Clangc::Cursor#raw_comment_text => String
*
* Given a cursor that represents a declaration, return the associated
* comment text, including comment markers.
*/
VALUE
c_Cursor_get_raw_comment_text(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return CXSTR_2_RVAL(clang_Cursor_getRawCommentText(c->data));
}

/**
* call-seq:
*   Clangc::Cursor#brief_comment_text => String
*
* Given a cursor that represents a documentable entity (e.g.,
* declaration), return the associated \\brief paragraph; otherwise return the
* first paragraph.
*/
VALUE
c_Cursor_get_brief_comment_text(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return CXSTR_2_RVAL(clang_Cursor_getBriefCommentText(c->data));
}

#if (CINDEX_VERSION_MINOR >= 29)
/**
* call-seq:
*  Clangc::Cursor#mangling => String
* Retrieve the String representing the mangled name of the cursor.
*/
VALUE
c_Cursor_get_mangling(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return CXSTR_2_RVAL(clang_Cursor_getMangling(c->data));
}
#endif

/**
* call-seq:
*   Clangc::Cursor#cxx_method_is_pure_virtual => true /false
*
* Determine if a C++ member function or member function template is
* pure virtual.
*/
VALUE
c_Cursor_cxx_method_is_pure_virtual(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return NOT_0_2_RVAL(clang_CXXMethod_isPureVirtual(c->data));
}

/**
* call-seq:
*   Clangc::Cursor#cxx_method_is_static => true /false
*
* Determine if a C++ member function or member function template is
* static.
*/
VALUE
c_Cursor_cxx_method_is_static(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return NOT_0_2_RVAL(clang_CXXMethod_isStatic(c->data));
}
/**
* call-seq:
*   Clangc::Cursor#cxx_method_is_virtual => true /false
*
* Determine if a C++ member function or member function template is
* explicitly declared 'virtual' or if it overrides a virtual method from
* one of the base classes.
*/
VALUE
c_Cursor_cxx_method_is_virtual(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return NOT_0_2_RVAL(clang_CXXMethod_isVirtual(c->data));
}

/**
* call-seq:
*   Clangc::Cursor#cxx_method_is_const => true /false
*
* Determine if a C++ member function or member function template is
* constant.
*/
VALUE
c_Cursor_cxx_method_is_const(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return NOT_0_2_RVAL(clang_CXXMethod_isConst(c->data));
}

/**
* call-seq:
*   Clangc::Cursor#template_cursor_kind => Clangc::CursorKind.constants
*
* Given a cursor that represents a template, determine the cursor kind of
* the specializations would be generated by instantiating the template.
*
* This routine can be used to determine what flavor of function template,
* class template, or class template partial specialization is stored in the
* cursor. For example, it can describe whether a class template cursor is
* declared with "struct", "class" or "union".
*
* C The cursor to query should represent a template declaration.
*
* It returns the cursor kind of the specializations that would be generated
* by instantiating the template . If the cursor is not a template, it returns
* Clangc::CursorKind::NO_DECL_FOUND.
*/
VALUE
c_Cursor_get_template_cursor_kind(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    return CUINT_2_NUM(clang_getTemplateCursorKind(c->data));
}

/**
* call-seq:
*   Clangc::Cursor#specialized_cursor_template => Clangc::Cursor
*
* Given a cursor that may represent a specialization or instantiation
* of a template, retrieve the cursor that represents the template that it
* specializes or from which it was instantiated.
*
* This routine determines the template involved both for explicit
* specializations of templates and for implicit instantiations of the template,
* both of which are referred to as "specializations". For a class template
* specialization (e.g., \c std::vector<bool>), this routine will return
* either the primary template (\c std::vector) or, if the specialization was
* instantiated from a class template partial specialization, the class template
* partial specialization. For a class template partial specialization and a
* function template specialization (including instantiations), this
* this routine will return the specialized template.
*
* For members of a class template (e.g., member functions, member classes, or
* static data members), returns the specialized or instantiated member.
* Although not strictly "templates" in the C++ language, members of class
* templates have the same notions of specializations and instantiations that
* templates do, so this routine treats them similarly.
*
* The cursor  may be a specialization of a template or a member
* of a template.
*
* If the given cursor is a specialization or instantiation of a
* template or a member thereof, it returns the template or member that it
* specializes or
* from which it was instantiated. Otherwise, returns a NULL cursor.
*/
VALUE
c_Cursor_get_specialized_cursor_template(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    Cursor_t *sct;
    VALUE specialized_cursor_template;
    R_GET_CLASS_DATA("Clangc", Cursor, specialized_cursor_template, sct);
    sct->data = clang_getSpecializedCursorTemplate(c->data);
    sct->parent = c->parent;
    return specialized_cursor_template;
}

/**
* call-seq:
*   Clangc::Cursor#completion_string => Clangc::CompletionString
*
* Retrieve a completion string for an arbitrary declaration or macro
* definition cursor.
*
* It returns a non-context-sensitive completion string for declaration and macro
* definition cursors, or nil for other kinds of cursors.
*/
VALUE
c_Cursor_get_completion_string(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    CompletionString_t *cs;
    VALUE completion_string;
    R_GET_CLASS_DATA("Clangc", CompletionString, completion_string, cs);
    cs->data = clang_getCursorCompletionString(c->data);
    cs->parent = self;
    if (cs->data == NULL)
        return Qnil;
    else
        return completion_string;
}

/**
* clang_Cursor_getTranslationUnit won't be implemented
* The memory managment would be too tricky
*/

#if (CINDEX_VERSION_MINOR >= 29)
/**
* call-seq:
*   Clangc::Cursor#template_argument_kind(i) => Clangc::TemplateArgumentKind
*
* Retrieve the kind of the I'th template argument of the CXCursor C.
*
* If the argument CXCursor does not represent a
* Clangc::CursorKind::FUNCTION_DECL, an invalid
* template argument kind is returned.
*
* For example, for the following declaration and specialization:
*   template <typename T, int kInt, bool kBool>
*   void foo() { ... }
*
*   template <>
*   void foo<float, -7, true>();
*
* For I = 0, 1, and 2, Type, Integral, and Integral will be returned,
* respectively.
*/
VALUE
c_Cursor_get_template_argument_kind(VALUE self, VALUE index)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    unsigned c_index = NUM2UINT(index);
    return CUINT_2_NUM(clang_Cursor_getTemplateArgumentKind(c->data, c_index));
}

/**
 * call-seq:
 *  Clangc::Cursor#template_argument_type => Clangc::Type
 *
 * Retrieve a Clangc::Type representing the type of a TemplateArgument of a
 *  function decl representing a template specialization.
 *
 * If the Clangc::Cursor does not represent a Clangc::CursorKind::FUNCTION_DECL
 * whose I'th
 * template argument has a kind of CXTemplateArgKind_Integral, an invalid type
 * is returned.
 *
 * For example, for the following declaration and specialization:
 *   template <typename T, int kInt, bool kBool>
 *   void foo() { ... }
 *
 *   template <>
 *   void foo<float, -7, true>();
 *
 * If called with I = 0, "float", will be returned.
 * Invalid types will be returned for I == 1 or 2.
 */
VALUE
c_Cursor_get_template_argument_type(VALUE self, VALUE index)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    unsigned c_index = NUM2UINT(index);
    Type_t *t;
    VALUE type;
    R_GET_CLASS_DATA("Clangc", Type, type, t);
    t->data = clang_Cursor_getTemplateArgumentType(c->data, c_index);
    t->parent = self;
    return type;
}

/**
 * call-seq:
 *  Clangc::Cursor#template_argument_value => Integer
 *
 *  Retrieve the value of an Integral TemplateArgument (of a function
 *  decl representing a template specialization) as a signed long long.
 *
 * It is undefined to call this function on a CXCursor that does not represent a
 * FunctionDecl or whose I'th template argument is not an integral value.
 *
 * For example, for the following declaration and specialization:
 *   template <typename T, int kInt, bool kBool>
 *   void foo() { ... }
 *
 *   template <>
 *   void foo<float, -7, true>();
 *
 * If called with I = 1 or 2, -7 or true will be returned, respectively.
 * For I == 0, this function's behavior is undefined.
 */
VALUE
c_Cursor_get_template_argument_value(VALUE self, VALUE index)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    unsigned c_index = NUM2UINT(index);
    return CLLONG_2_NUM(
        clang_Cursor_getTemplateArgumentValue(c->data, c_index));
}

/**
 * call-seq:
 *  Clangc::Cursor#template_argument_unsigned_value => Integer
 *
 *  Retrieve the value of an Integral TemplateArgument (of a function
 *  decl representing a template specialization) as an unsigned long long.
 *
 * It is undefined to call this function on a CXCursor that does not represent a
 * FunctionDecl or whose I'th template argument is not an integral value.
 *
 * For example, for the following declaration and specialization:
 *   template <typename T, int kInt, bool kBool>
 *   void foo() { ... }
 *
 *   template <>
 *   void foo<float, 2147483649, true>();
 *
 * If called with I = 1 or 2, 2147483649 or true will be returned, respectively.
 * For I == 0, this function's behavior is undefined.
 */
VALUE
c_Cursor_get_template_argument_unsigned_value(VALUE self, VALUE index)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    unsigned c_index = NUM2UINT(index);
    return CULLONG_2_NUM(
        clang_Cursor_getTemplateArgumentUnsignedValue(c->data, c_index));
}
#endif
/**
 * call-seq:
 *  Clangc::Cursor#obj_c_property_attributes(reserved) => Integer
 *
 * Given a cursor that represents a property declaration, return the
 * associated property attributes. The bits are formed from
 *  Clangc::ObjCPropertyAttrKind constants.
 *
 * reserved Reserved for future use, pass 0.
 */
VALUE
c_Cursor_get_obj_c_property_attributes(VALUE self, VALUE reserved)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    unsigned c_reserved = CLANGC_CONSTANT_TO_UINT("ObjCPropertyAttrKind",
                                                  reserved);
    return CUINT_2_NUM(
        clang_Cursor_getObjCPropertyAttributes(c->data, c_reserved));
}

/**
 * call-seq:
 *  Clangc::Cursor#overriden_cursors => Array
 *
 * Determine the set of methods that are overridden by the given
 * method.
 *
 * In both Objective-C and C++, a method (aka virtual member function,
 * in C++) can override a virtual method in a base class. For
 * Objective-C, a method is said to override any method in the class's
 * base class, its protocols, or its categories' protocols, that has the same
 * selector and is of the same kind (class or instance).
 * If no such method exists, the search continues to the class's superclass,
 * its protocols, and its categories, and so on. A method from an Objective-C
 * implementation is considered to override the same methods as its
 * corresponding method in the interface.
 *
 * For C++, a virtual member function overrides any virtual member
 * function with the same signature that occurs in its base
 * classes. With multiple inheritance, a virtual member function can
 * override several virtual member functions coming from different
 * base classes.
 *
 * In all cases, this function determines the immediate overridden
 * method, rather than all of the overridden methods. For example, if
 * a method is originally declared in a class A, then overridden in B
 * (which in inherits from A) and also in C (which inherited from B),
 * then the only overridden method returned from this function when
 * invoked on C's method will be B's method. The client may then
 * invoke this function again, given the previously-found overridden
 * methods, to map out the complete method-override set.
 *
 * It returns an Array of Clangc::Cursors or an empty Array.
 */
VALUE
c_Cursor_get_overridden_cursors(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);

    CXCursor **overridden;
    unsigned num_overridden;
    clang_getOverriddenCursors(c->data, overridden, &num_overridden);

    VALUE ret = rb_ary_new();
    if (overridden == NULL) return ret;

    unsigned i;
    for (i = 0; i < num_overridden; i++)
    {
        CXCursor *ptr;
        ptr = *(overridden + i);
        VALUE overridden_cursor;
        OverriddenCursor_t *oc;
        R_GET_CLASS_DATA("Clangc", OverriddenCursor, overridden_cursor, oc);
        oc->data = *ptr;
        oc->ptr = ptr;
        rb_ary_push(ret, overridden_cursor);
    }

    return ret;
}

/**
 * call-seq:
 *   Clangc::Cursor#module => Clangc::Module
 *
 * Given a Clangc::CursorKind::MODULE_IMPORT_DECL cursor, return the associated
 * module.
 */
VALUE
c_Cursor_get_module(VALUE self)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    Module_t *m;
    VALUE module;
    R_GET_CLASS_DATA("Clangc", Module, module, m);
    m->data = clang_Cursor_getModule(c->data);
    m->parent = self;
    return module;
}

/**
 * call-seq:
 *  Clangc::Cursor#spelling_name_range(Integer, Integer) => Clangc::SourceRange
 *
 * Retrieve a range for a piece that forms the cursors spelling name.
 * Most of the times there is only one range for the complete spelling but for
 * Objective-C methods and Objective-C message expressions, there are multiple
 * pieces for each selector identifier.
 *
 * First parameter is the index of the spelling name piece. If this is greater
 * than the actual number of pieces, it will return a NULL (invalid) range.
 *
 * The second parameter is for options and are Reserved.
 */
VALUE
c_Cursor_get_spelling_name_range(VALUE self, VALUE index, VALUE options)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    SourceRange_t *sr;
    VALUE source_range;
    R_GET_CLASS_DATA("Clangc", SourceRange, source_range, sr);
    sr->data = clang_Cursor_getSpellingNameRange(
        c->data, NUM2UINT(index), NUM2UINT(options));
    sr->parent = c->parent;
    return source_range;
}

/**
 * call-seq:
 *  Clangc::Cursor#reference_name_range(Clangc::NameFlags, piece_index) =>
 * Clangc::SourceRange or Clangc::Cursor (null)
 *
 * Given a cursor that references something else, return the source range
 * covering that reference.
 *
 * For a cursor pointing to a member reference, a declaration reference, or
 * an operator call.
 *
 * First parameter is a Clangc::NameFlags. A bitset with three independent
 * flags:
 * CXNameRange_WantQualifier, CXNameRange_WantTemplateArgs, and
 * CXNameRange_WantSinglePiece.
 *
 * piece_index For contiguous names or when passing the flag
 * CXNameRange_WantSinglePiece, only one piece with index 0 is
 * available. When the CXNameRange_WantSinglePiece flag is not passed for a
 * non-contiguous names, this index can be used to retrieve the individual
 * pieces of the name. See also CXNameRange_WantSinglePiece.
 *
 * It returns the piece of the name pointed to by the given cursor. If there is
 * no
 * name, or if the PieceIndex is out-of-range, a null-cursor will be returned.
 */
VALUE
c_Cursor_get_reference_name_range(VALUE self,
                                  VALUE name_flags,
                                  VALUE piece_index)
{
    Cursor_t *c;
    Data_Get_Struct(self, Cursor_t, c);
    SourceRange_t *sr;
    VALUE source_range;
    unsigned int c_name_flags;
    unsigned int c_piece_index;
    c_name_flags = CLANGC_CONSTANT_TO_UINT("NameRefFlags", name_flags);
    c_piece_index = NUM2UINT(piece_index);
    R_GET_CLASS_DATA("Clangc", SourceRange, source_range, sr);

    sr->data = clang_getCursorReferenceNameRange(
        c->data, c_name_flags, c_piece_index);
    sr->parent = c->parent;
    return source_range;
}
