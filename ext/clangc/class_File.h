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
#ifndef FILE_H
#define FILE_H
#include <ruby/ruby.h>
#include "clang-c/Index.h"
typedef struct File_t
{
    CXFile data;
    VALUE parent; // A translation unit ( a CXFile is a file related to a
                  // translation unit)
} File_t;

VALUE
c_File_struct_alloc(VALUE);

VALUE
c_File_get_name(VALUE);

VALUE
c_File_get_mtime(VALUE);

VALUE
c_File_is_multiple_include_guarded(VALUE);

#if (CINDEX_VERSION_MINOR >= 29)
VALUE
c_File_is_equal(VALUE, VALUE);
#endif
#endif // FILE_H
