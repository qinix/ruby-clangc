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
*   Clangc::Cursor#kind => Fixnum
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
