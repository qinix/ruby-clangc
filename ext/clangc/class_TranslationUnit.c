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
/*TranslationUnit ruby class*/
#include "clang-c/Index.h"
#include "class_TranslationUnit.h"

static void
c_TranslationUnit_struct_free(TranslationUnit_t *s)
{
  if(s)
  {
    
  if(s->data)
    clang_disposeTranslationUnit(s->data); 

    ruby_xfree(s);
  }
}  
VALUE
c_TranslationUnit_struct_alloc( VALUE klass)
{
  
    TranslationUnit_t * ptr;
    ptr = (TranslationUnit_t *) ruby_xmalloc(sizeof(TranslationUnit_t)); 
    ptr->data = NULL;

  return Data_Wrap_Struct(klass, NULL, c_TranslationUnit_struct_free, (void *) ptr);
}

/*static VALUE
c_TranslationUnit_initialize(VALUE self) {
  
}*/
