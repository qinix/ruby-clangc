var search_data = {"index":{"searchIndex":["clangc","cursor","diagnostic","file","index","sourcelocation","sourcerange","translationunit","type","availability()","category()","category_name()","category_text()","create_translation_unit()","create_translation_unit2()","create_translation_unit_from_source_file()","cursor()","default_code_complete_options()","default_diagnostic_display_options()","default_editing_translation_unit_options()","default_reparse_options()","default_save_options()","diagnostic()","diagnostics()","diagnostics_num()","end()","file()","file_location()","format()","global_options()","global_options=()","hash()","is_equal()","is_equal()","is_equal()","is_equal()","is_from_main_file()","is_in_system_header()","is_multiple_include_guarded()","is_null()","is_null()","kind()","language()","linkage()","mtime()","name()","new()","null_cursor()","null_source_location()","null_source_range()","num_fixits()","num_ranges()","option()","parse_translation_unit()","parse_translation_unit2()","semantic_parent()","severity()","source_location()","source_range()","source_ranges()","spelling()","spelling()","spelling()","start()","type()","version()","visit_children()","visit_children_with_block()","visit_children_with_proc()","readme"],"longSearchIndex":["clangc","clangc::cursor","clangc::diagnostic","clangc::file","clangc::index","clangc::sourcelocation","clangc::sourcerange","clangc::translationunit","clangc::type","clangc::cursor#availability()","clangc::diagnostic#category()","clangc::diagnostic#category_name()","clangc::diagnostic#category_text()","clangc::index#create_translation_unit()","clangc::index#create_translation_unit2()","clangc::index#create_translation_unit_from_source_file()","clangc::translationunit#cursor()","clangc::default_code_complete_options()","clangc::default_diagnostic_display_options()","clangc::default_editing_translation_unit_options()","clangc::translationunit#default_reparse_options()","clangc::translationunit#default_save_options()","clangc::translationunit#diagnostic()","clangc::translationunit#diagnostics()","clangc::translationunit#diagnostics_num()","clangc::sourcerange#end()","clangc::translationunit#file()","clangc::sourcelocation#file_location()","clangc::diagnostic#format()","clangc::index#global_options()","clangc::index#global_options=()","clangc::cursor#hash()","clangc::cursor#is_equal()","clangc::file#is_equal()","clangc::sourcelocation#is_equal()","clangc::sourcerange#is_equal()","clangc::sourcelocation#is_from_main_file()","clangc::sourcelocation#is_in_system_header()","clangc::file#is_multiple_include_guarded()","clangc::cursor#is_null()","clangc::sourcerange#is_null()","clangc::cursor#kind()","clangc::cursor#language()","clangc::cursor#linkage()","clangc::file#mtime()","clangc::file#name()","clangc::index::new()","clangc::null_cursor()","clangc::null_source_location()","clangc::null_source_range()","clangc::diagnostic#num_fixits()","clangc::diagnostic#num_ranges()","clangc::diagnostic#option()","clangc::index#parse_translation_unit()","clangc::index#parse_translation_unit2()","clangc::cursor#semantic_parent()","clangc::diagnostic#severity()","clangc::diagnostic#source_location()","clangc::diagnostic#source_range()","clangc::diagnostic#source_ranges()","clangc::diagnostic#spelling()","clangc::sourcelocation#spelling()","clangc::translationunit#spelling()","clangc::sourcerange#start()","clangc::cursor#type()","clangc::version()","clangc::visit_children()","clangc::visit_children_with_block()","clangc::visit_children_with_proc()",""],"info":[["Clangc","","Clangc.html","",""],["Clangc::Cursor","","Clangc/Cursor.html","","<p>A cursor representing some element in the abstract syntax tree for a\ntranslation unit.\n<p>The cursor abstraction …\n"],["Clangc::Diagnostic","","Clangc/Diagnostic.html","","<p>A diagnostic object, containing the diagnostic&#39;s severity, location,\ntext, source ranges, and fix-it …\n"],["Clangc::File","","Clangc/File.html","","<p>A particular source file that is part of a translation unit\n"],["Clangc::Index","","Clangc/Index.html","","<p>An “index” consists of a set of translation units that would typically be\nlinked together into …\n"],["Clangc::SourceLocation","","Clangc/SourceLocation.html","","<p>Identifies a specific source location within a translation unit.\n<p>Use Clangc::SourceLocation#expansion …\n"],["Clangc::SourceRange","","Clangc/SourceRange.html","","<p>Identifies a half-open character range in the source code.\n<p>Use Clangc::Range#start and Clangc::Range#end …\n"],["Clangc::TranslationUnit","","Clangc/TranslationUnit.html","","<p>A single TranslationUnit which resides in an Index\n"],["Clangc::Type","","Clangc/Type.html","","<p>Type informations for Clangc::Cursor\n"],["availability","Clangc::Cursor","Clangc/Cursor.html#method-i-availability","()","<p>Determine the availability of the entity that this cursor refers to, taking\nthe current target platform …\n"],["category","Clangc::Diagnostic","Clangc/Diagnostic.html#method-i-category","()","<p>Retrieve the category number for this diagnostic.\n<p>Diagnostics can be categorized into groups along with …\n"],["category_name","Clangc::Diagnostic","Clangc/Diagnostic.html#method-i-category_name","()","<p>Retrieve the name of a particular diagnostic category.  This is now\ndeprecated.  Use Clangc::Diagnostic#category_text …\n"],["category_text","Clangc::Diagnostic","Clangc/Diagnostic.html#method-i-category_text","()","<p>Retrieve the diagnostic category text for a given diagnostic. Returns The\ntext of the given diagnostic …\n"],["create_translation_unit","Clangc::Index","Clangc/Index.html#method-i-create_translation_unit","(p1)","<p>Create a translation unit from an AST file name. If the creation fail, it\nreturns nil. The AST file is …\n"],["create_translation_unit2","Clangc::Index","Clangc/Index.html#method-i-create_translation_unit2","(p1)","<p>Create a translation unit from an AST file name. If the creation fail, it\nreturns an error code Clangc::ErrorCode …\n"],["create_translation_unit_from_source_file","Clangc::Index","Clangc/Index.html#method-i-create_translation_unit_from_source_file","(p1, p2)","<p>Return a TranslationUnit instance for a given source file and the provided\ncommand line arguments one …\n"],["cursor","Clangc::TranslationUnit","Clangc/TranslationUnit.html#method-i-cursor","()","<p>Retrieve the cursor that represents the given translation unit.\n<p>The translation unit cursor can be used …\n"],["default_code_complete_options","Clangc","Clangc.html#method-c-default_code_complete_options","()","<p>Returns a default set of code-completion options that can be passed to\nClangc::TranslationUnit#codeCompleteAt …\n"],["default_diagnostic_display_options","Clangc","Clangc.html#method-c-default_diagnostic_display_options","()","<p>Retrieve the set of display options most similar to the default behavior of\nthe clang compiler.\n<p>A set …\n"],["default_editing_translation_unit_options","Clangc","Clangc.html#method-c-default_editing_translation_unit_options","()","<p>Returns the set of flags that is suitable for parsing a translation unit\nthat is being edited. (Clangc::TranslationUnit_Flags …\n"],["default_reparse_options","Clangc::TranslationUnit","Clangc/TranslationUnit.html#method-i-default_reparse_options","()","<p>Returns the set of flags that is suitable for reparsing a translation unit.\n<p>The set of flags returned …\n"],["default_save_options","Clangc::TranslationUnit","Clangc/TranslationUnit.html#method-i-default_save_options","()","<p>Returns the set of flags that is suitable for saving a translation unit.\nThose flags should be Clangc::SaveTranslationUnit_Flags …\n"],["diagnostic","Clangc::TranslationUnit","Clangc/TranslationUnit.html#method-i-diagnostic","(p1)","<p>Retrieve a diagnostic associated with the given translation unit.\n<p>index the zero-based diagnostic number …\n"],["diagnostics","Clangc::TranslationUnit","Clangc/TranslationUnit.html#method-i-diagnostics","()",""],["diagnostics_num","Clangc::TranslationUnit","Clangc/TranslationUnit.html#method-i-diagnostics_num","()","<p>Determine the number of diagnostics produced for the given translation\nunit.\n"],["end","Clangc::SourceRange","Clangc/SourceRange.html#method-i-end","()","<p>Retrieve a source location representing the last character within a source\nrange.\n"],["file","Clangc::TranslationUnit","Clangc/TranslationUnit.html#method-i-file","(p1)","<p>Retrieve a file handle within the given translation unit. file_name a\nString for the name of the file. …\n"],["file_location","Clangc::SourceLocation","Clangc/SourceLocation.html#method-i-file_location","()","<p>Retrieve the file, line, column, and offset represented by the given source\nlocation.\n<p>If the location …\n"],["format","Clangc::Diagnostic","Clangc/Diagnostic.html#method-i-format","(p1)","<p>Format the given diagnostic in a manner that is suitable for display.\n<p>This routine will format the given …\n"],["global_options","Clangc::Index","Clangc/Index.html#method-i-global_options","()","<p>Gets the general options associated with an Index. A bitmask of options, a\nbitwise OR of the Clangc::GlobalOptFlags …\n"],["global_options=","Clangc::Index","Clangc/Index.html#method-i-global_options-3D","(p1)","<p>Sets general options associated with an Index instance.\n<p>options:\n\n<p>A bitmask of options, a bitwise OR of …\n"],["hash","Clangc::Cursor","Clangc/Cursor.html#method-i-hash","()","<p>Compute a hash value for the given cursor.\n"],["is_equal","Clangc::Cursor","Clangc/Cursor.html#method-i-is_equal","(p1)","<p>Determine whether two cursors are equivalent.\n"],["is_equal","Clangc::File","Clangc/File.html#method-i-is_equal","(p1)","<p>Returns true if the file1 and file2 point to the same file, or both null.\nTwo ruby objects Clangc::File …\n"],["is_equal","Clangc::SourceLocation","Clangc/SourceLocation.html#method-i-is_equal","(p1)","<p>Determine whether two source locations, which must refer into the same\ntranslation unit, refer to exactly …\n"],["is_equal","Clangc::SourceRange","Clangc/SourceRange.html#method-i-is_equal","(p1)","<p>Determine whether two ranges are equivalent. Returns true if the ranges are\nthe same, false if they differ. …\n"],["is_from_main_file","Clangc::SourceLocation","Clangc/SourceLocation.html#method-i-is_from_main_file","()","<p>Returns true if the given source location is in the main file of the\ncorresponding translation unit. …\n"],["is_in_system_header","Clangc::SourceLocation","Clangc/SourceLocation.html#method-i-is_in_system_header","()","<p>Returns true if the given source location is in a system header.\n"],["is_multiple_include_guarded","Clangc::File","Clangc/File.html#method-i-is_multiple_include_guarded","()","<p>Determine whether the given header is guarded against multiple inclusions,\neither with the conventional …\n"],["is_null","Clangc::Cursor","Clangc/Cursor.html#method-i-is_null","()","<p>return true is the cursor is a null Cursor or false otherwise\n"],["is_null","Clangc::SourceRange","Clangc/SourceRange.html#method-i-is_null","()","<p>Returns true is the underlying CXSourceRange is NULL or false otherwise\n"],["kind","Clangc::Cursor","Clangc/Cursor.html#method-i-kind","()","<p>Retrieve the kind of the given cursor. The value should refer to the\nconstants in Clangc::CursorKind …\n"],["language","Clangc::Cursor","Clangc/Cursor.html#method-i-language","()","<p>Determine the “language” of the entity referred to by a given cursor. The\nvalue should refer …\n"],["linkage","Clangc::Cursor","Clangc/Cursor.html#method-i-linkage","()","<p>Determine the linkage of the entity referred to by a given cursor. The\nvalue should refer to the constants …\n"],["mtime","Clangc::File","Clangc/File.html#method-i-mtime","()","<p>Retrieve the last modification time of the given file.\n"],["name","Clangc::File","Clangc/File.html#method-i-name","()","<p>Retrieve the complete file and path name of the given file. Returns Qnil if\nthe CXFile pointer is NULL …\n"],["new","Clangc::Index","Clangc/Index.html#method-c-new","(p1, p2)","<p>Provides a shared context for creating translation units.\n<p>It provides two options:\n<p>excludeDeclarationsFromPCH: …\n"],["null_cursor","Clangc","Clangc.html#method-c-null_cursor","()","<p>Retrieve a NULL cursor which represents no entity\n"],["null_source_location","Clangc","Clangc.html#method-c-null_source_location","()","<p>Retrieve a NULL (invalid) source location.\n"],["null_source_range","Clangc","Clangc.html#method-c-null_source_range","()","<p>Retrieve a NULL (invalid) source range\n"],["num_fixits","Clangc::Diagnostic","Clangc/Diagnostic.html#method-i-num_fixits","()","<p>Determine the number of fix-it hints associated with the given diagnostic.\n"],["num_ranges","Clangc::Diagnostic","Clangc/Diagnostic.html#method-i-num_ranges","()","<p>Determine the number of source ranges associated with the given diagnostic.\n"],["option","Clangc::Diagnostic","Clangc/Diagnostic.html#method-i-option","()","<p>Retrieve the name of the command-line option that enabled this diagnostic\nsuch as (“-Wconversion” …\n"],["parse_translation_unit","Clangc::Index","Clangc/Index.html#method-i-parse_translation_unit","(p1, p2, p3)","<p>Parse the given source file and generate the translation unit corresponding\nto that file.\n<p>This routine …\n"],["parse_translation_unit2","Clangc::Index","Clangc/Index.html#method-i-parse_translation_unit2","(p1, p2, p3)","<p>Parse the given source file and generate the translation unit corresponding\nto that file. If its fails, …\n"],["semantic_parent","Clangc::Cursor","Clangc/Cursor.html#method-i-semantic_parent","()","<p>Determine the semantic parent of the given cursor.\n<p>The semantic parent of a cursor is the cursor that …\n"],["severity","Clangc::Diagnostic","Clangc/Diagnostic.html#method-i-severity","()","<p>Determine the severity of the given diagnostic. It returns one of the\nconstants defined in Clangc::DiagnosticSeverity.constants …\n"],["source_location","Clangc::Diagnostic","Clangc/Diagnostic.html#method-i-source_location","()","<p>Retrieve the source location of the given diagnostic.\n<p>This location is where Clang would print the caret …\n"],["source_range","Clangc::Diagnostic","Clangc/Diagnostic.html#method-i-source_range","(p1)","<p>Retrieve a source range associated with the diagnostic.\n<p>A diagnostic&#39;s source ranges highlight important …\n"],["source_ranges","Clangc::Diagnostic","Clangc/Diagnostic.html#method-i-source_ranges","()",""],["spelling","Clangc::Diagnostic","Clangc/Diagnostic.html#method-i-spelling","()","<p>Retrieve the text of the given diagnostic.\n"],["spelling","Clangc::SourceLocation","Clangc/SourceLocation.html#method-i-spelling","()","<p>Retrieve the file, line, column, and offset represented by the given source\nlocation.\n<p>If the location …\n"],["spelling","Clangc::TranslationUnit","Clangc/TranslationUnit.html#method-i-spelling","()","<p>Get the original translation unit source file name.\n"],["start","Clangc::SourceRange","Clangc/SourceRange.html#method-i-start","()","<p>Retrieve a source location representing the first character within a source\nrange.\n"],["type","Clangc::Cursor","Clangc/Cursor.html#method-i-type","()","<p>Retrieve the type of a CXCursor (if any).\n"],["version","Clangc","Clangc.html#method-c-version","()","<p>Return a version string, suitable for showing to a user, but not intended\nto be parsed (the format is …\n"],["visit_children","Clangc","Clangc.html#method-c-visit_children","(args)",""],["visit_children_with_block","Clangc","Clangc.html#method-c-visit_children_with_block","(p1)","<p>Visit the children of a particular cursor.\n<p>This function visits all the direct children of the given cursor, …\n"],["visit_children_with_proc","Clangc","Clangc.html#method-c-visit_children_with_proc","(p1, p2)","<p>Visit the children of a particular cursor.\n<p>This function visits all the direct children of the given cursor, …\n"],["README","","README_rdoc.html","","<p>Ruby bindings for libclang \n<p>This module provides bindings for the C interface of Clang. clang.llvm.org\n…\n"]]}}