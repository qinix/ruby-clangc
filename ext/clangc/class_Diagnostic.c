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
/*Diagnostic ruby class*/
#include "class_Diagnostic.h"
#include "macros.h"
#include "class_SourceRange.h"
#include "class_SourceLocation.h"

static void c_Diagnostic_struct_free(Diagnostic_t *s)
{
    if (s)
    {

        if (s->data) clang_disposeDiagnostic(s->data);

        ruby_xfree(s);
    }
}
static void c_Diagnostic_mark(void *s)
{
    if (s)
    {
        Diagnostic_t *d = (Diagnostic_t *) s;
        rb_gc_mark(d->parent);
    }
}
VALUE
c_Diagnostic_struct_alloc(VALUE klass)
{

    Diagnostic_t *ptr;
    ptr = (Diagnostic_t *) ruby_xmalloc(sizeof(Diagnostic_t));
    ptr->data = NULL;
    ptr->parent = Qnil;
    return Data_Wrap_Struct(
        klass, c_Diagnostic_mark, c_Diagnostic_struct_free, (void *) ptr);
}

/**
* call-seq:
*   Clangc::Diagnostic#severity => Fixnum
*
* Determine the severity of the given diagnostic. It returns one of the
* constants defined
* in Clangc::DiagnosticSeverity.constants
*/
VALUE
c_Diagnostic_get_severity(VALUE self)
{
    Diagnostic_t *d;
    Data_Get_Struct(self, Diagnostic_t, d);
    unsigned int severity = clang_getDiagnosticSeverity(d->data);
    return CUINT_2_NUM(severity);
}

/**
* call-seq:
*   Clangc::Diagnostic#spelling => String
*
* Retrieve the text of the given diagnostic.
*/
VALUE
c_Diagnostic_get_spelling(VALUE self)
{
    Diagnostic_t *d;
    Data_Get_Struct(self, Diagnostic_t, d);
    return CXSTR_2_RVAL(clang_getDiagnosticSpelling(d->data));
}

/**
* call-seq:
*   Clangc::Diagnostic#category => Fixnum
*
* Retrieve the category number for this diagnostic.
*
* Diagnostics can be categorized into groups along with other, related
* diagnostics (e.g., diagnostics under the same warning flag). This routine
* retrieves the category number for the given diagnostic.
*
* The number of the category that contains this diagnostic, or zero
* if this diagnostic is uncategorized.
*/
VALUE
c_Diagnostic_get_category(VALUE self)
{
    Diagnostic_t *d;
    Data_Get_Struct(self, Diagnostic_t, d);
    unsigned int category = clang_getDiagnosticCategory(d->data);
    return CUINT_2_NUM(category);
}

/**
* call-seq:
*   Clangc::Diagnostic#category_name => String
*
* Retrieve the name of a particular diagnostic category.  This
* is now deprecated.  Use Clangc::Diagnostic#category_text
* instead.
*/
VALUE
c_Diagnostic_get_category_name(VALUE self)
{
    // TODO deprecated write if macro based on clang vervion
    Diagnostic_t *d;
    Data_Get_Struct(self, Diagnostic_t, d);
    return CXSTR_2_RVAL(
        clang_getDiagnosticCategoryName(clang_getDiagnosticCategory(d->data)));
}

/**
* call-seq:
*   Clangc::Diagnostic#category_text => String
*
* Retrieve the diagnostic category text for a given diagnostic.
* Returns The text of the given diagnostic category.
*/
VALUE
c_Diagnostic_get_category_text(VALUE self)
{
    Diagnostic_t *d;
    Data_Get_Struct(self, Diagnostic_t, d);
    return CXSTR_2_RVAL(clang_getDiagnosticCategoryText(d->data));
}

/**
* call-seq:
*   Clangc::Diagnostic#num_ranges => Fixnum
*
* Determine the number of source ranges associated with the given
* diagnostic.
*/
VALUE
c_Diagnostic_get_num_ranges(VALUE self)
{
    Diagnostic_t *d;
    Data_Get_Struct(self, Diagnostic_t, d);
    unsigned int num = clang_getDiagnosticNumRanges(d->data);
    return CUINT_2_NUM(num);
}

/**
* call-seq:
*   Clangc::Diagnostic#num_fixits => Fixnum
*
* Determine the number of fix-it hints associated with the given
* diagnostic.
*/
VALUE
c_Diagnostic_get_num_fixits(VALUE self)
{
    Diagnostic_t *d;
    Data_Get_Struct(self, Diagnostic_t, d);
    unsigned int num = clang_getDiagnosticNumFixIts(d->data);
    return CUINT_2_NUM(num);
}

/**
* call-seq:
*   Clangc::Diagnostic#format(options) => String
*
* Format the given diagnostic in a manner that is suitable for display.
*
* This routine will format the given diagnostic to a string, rendering
* the diagnostic according to the various options given. The
* Clangc.default_diagnostic_display_options function returns the set of
* options that most closely mimics the behavior of the clang compiler.
*
* options A set of options that control the diagnostic display,
* created by combining Clangc::DiagnosticDisplayOptions constants.
*
* It returns a new string containing for formatted diagnostic.
*/
VALUE
c_Diagnostic_format(VALUE self, VALUE options)
{
    Diagnostic_t *d;
    Data_Get_Struct(self, Diagnostic_t, d);
    unsigned int c_options = CLANGC_CONSTANT_TO_UINT("DiagnosticDisplayOptions",
                                                     options);
    return CXSTR_2_RVAL(clang_formatDiagnostic(d->data, c_options));
}

/**
* call-seq:
*   Clangc::Diagnostic#option => Array
*
* Retrieve the name of the command-line option that enabled this
* diagnostic such as ("-Wconversion" or "-pedantic") and the option
* that disables it if any.
* returned_array[0] == String command-line option that enabled the diagnostic
* returned_array[1] == String or nil command-line option that disable the
* diagnostic
*/

VALUE
c_Diagnostic_get_option(VALUE self)
{
    Diagnostic_t *d;
    Data_Get_Struct(self, Diagnostic_t, d);

    CXString str1;
    CXString str2;
    str1 = clang_getDiagnosticOption(d->data, &str2);
    VALUE ret = rb_ary_new();
    rb_ary_push(ret, CXSTR_2_RVAL(str1));
    rb_ary_push(ret, CXSTR_2_RVAL(str2));

    return ret;
}

/**
* Retrieve a source range associated with the diagnostic.
* call-seq:
*   Clangc::Diagnostic#source_range(index) => Clangc::SourceRange
*
* A diagnostic's source ranges highlight important elements in the source
* code. On the command line, Clang displays source ranges by
* underlining them with '~' characters.
*
* \param Diagnostic the diagnostic whose range is being extracted.
*
* \param Range the zero-based index specifying which range to
*
* \returns the requested source range.
*/
VALUE
c_Diagnostic_get_source_range(VALUE self, VALUE index)
{
    Diagnostic_t *d;
    Data_Get_Struct(self, Diagnostic_t, d);
    unsigned int c_index = NUM2UINT(index);
    VALUE a_source_range;
    SourceRange_t *s;
    R_GET_CLASS_DATA("Clangc", SourceRange, a_source_range, s);
    s->data = clang_getDiagnosticRange(d->data, c_index);
    s->parent = self;
    return a_source_range;
}

/**
* call-seq:
*   Clangc::Diagnostic#source_location => Clangc::SourceLocation
*
* Retrieve the source location of the given diagnostic.
*
* This location is where Clang would print the caret ('^') when
* displaying the diagnostic on the command line.
*/

VALUE
c_Diagnostic_get_source_location(VALUE self)
{
    Diagnostic_t *d;
    Data_Get_Struct(self, Diagnostic_t, d);
    VALUE a_source_location;
    SourceLocation_t *sl;
    R_GET_CLASS_DATA("Clangc", SourceLocation, a_source_location, sl);
    sl->data = clang_getDiagnosticLocation(d->data);
    sl->parent = self;
    return a_source_location;
}

/**
 * call-seq:
 *  Clangc::Diagnostic#fix_it(fix_number) => Array [Str, Clangc::SourceRange]
 *
 * Retrieve the replacement information for a given fix-it.
 *
 * Fix-its are described in terms of a source range whose contents
 * should be replaced by a string. This approach generalizes over
 * three kinds of operations: removal of source code (the range covers
 * the code to be removed and the replacement string is empty),
 * replacement of source code (the range covers the code to be
 * replaced and the replacement string provides the new code), and
 * insertion (both the start and end of the range point at the
 * insertion location, and the replacement string provides the text to
 * insert).
 *
 * fix_number The zero-based index of the fix-it.
 *
 * Returns an Array with in the following order:
 *
 * A string containing text that should be replace the source
 * code indicated by the \c ReplacementRange.
 *
 * The source range whose contents will be
 * replaced with the returned replacement string. Note that source
 * ranges are half-open ranges [a, b), so the source code should be
 * replaced from a and up to (but not including) b.
 */
VALUE
c_Diagnostic_get_fixit(VALUE self, VALUE index)
{
    Diagnostic_t *d;
    Data_Get_Struct(self, Diagnostic_t, d);
    unsigned int c_index = NUM2UINT(index);
    VALUE source_range;
    SourceRange_t *s;
    CXString fixit_str;
    VALUE ret = rb_ary_new();
    R_GET_CLASS_DATA("Clangc", SourceRange, source_range, s);
    s->parent = self;
    fixit_str = clang_getDiagnosticFixIt(d->data, c_index, &(s->data));
    rb_ary_push(ret, CXSTR_2_RVAL(fixit_str));
    rb_ary_push(ret, source_range);
    return ret;
}
