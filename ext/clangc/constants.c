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
#include "constants.h"
void init_clang_enums_to_constants(VALUE m_clang){
VALUE m_AvailabilityKind = rb_define_module_under(m_clang,"AvailabilityKind");
rb_define_const(m_AvailabilityKind,"Available", INT2NUM(0));
rb_define_const(m_AvailabilityKind,"Deprecated", INT2NUM(1));
rb_define_const(m_AvailabilityKind,"Notavailable", INT2NUM(2));
rb_define_const(m_AvailabilityKind,"Notaccessible", INT2NUM(3));

VALUE m_GlobalOptFlags = rb_define_module_under(m_clang,"GlobalOptFlags");
rb_define_const(m_GlobalOptFlags,"None", INT2NUM(0));
rb_define_const(m_GlobalOptFlags,"Threadbackgroundpriorityforindexing", INT2NUM(1));
rb_define_const(m_GlobalOptFlags,"Threadbackgroundpriorityforediting", INT2NUM(2));
rb_define_const(m_GlobalOptFlags,"Threadbackgroundpriorityforall", INT2NUM(3));

VALUE m_DiagnosticSeverity = rb_define_module_under(m_clang,"DiagnosticSeverity");
rb_define_const(m_DiagnosticSeverity,"Ignored", INT2NUM(0));
rb_define_const(m_DiagnosticSeverity,"Note", INT2NUM(1));
rb_define_const(m_DiagnosticSeverity,"Warning", INT2NUM(2));
rb_define_const(m_DiagnosticSeverity,"Error", INT2NUM(3));
rb_define_const(m_DiagnosticSeverity,"Fatal", INT2NUM(4));

VALUE m_LoadDiag_Error = rb_define_module_under(m_clang,"LoadDiag_Error");
rb_define_const(m_LoadDiag_Error,"None", INT2NUM(0));
rb_define_const(m_LoadDiag_Error,"Unknown", INT2NUM(1));
rb_define_const(m_LoadDiag_Error,"Cannotload", INT2NUM(2));
rb_define_const(m_LoadDiag_Error,"Invalidfile", INT2NUM(3));

VALUE m_DiagnosticDisplayOptions = rb_define_module_under(m_clang,"DiagnosticDisplayOptions");
rb_define_const(m_DiagnosticDisplayOptions,"Displaysourcelocation", INT2NUM(1));
rb_define_const(m_DiagnosticDisplayOptions,"Displaycolumn", INT2NUM(2));
rb_define_const(m_DiagnosticDisplayOptions,"Displaysourceranges", INT2NUM(4));
rb_define_const(m_DiagnosticDisplayOptions,"Displayoption", INT2NUM(8));
rb_define_const(m_DiagnosticDisplayOptions,"Displaycategoryid", INT2NUM(16));
rb_define_const(m_DiagnosticDisplayOptions,"Displaycategoryname", INT2NUM(32));

/*
* Flags that control the creation of translation units.
*
* The enumerators in this enumeration type are meant to be bitwise
* ORed together to specify which options should be used when
* constructing the translation unit.
*/
VALUE m_TranslationUnit_Flags = rb_define_module_under(m_clang,"TranslationUnit_Flags");
/*
* Used to indicate that no special translation-unit options are needed.
*/
rb_define_const(m_TranslationUnit_Flags,"None", INT2NUM(0));
/*
* Used to indicate that the parser should construct a "detailed"
* preprocessing record, including all macro definitions and instantiations.
*
* Constructing a detailed preprocessing record requires more memory
* and time to parse, since the information contained in the record
* is usually not retained. However, it can be useful for
* applications that require more detailed information about the
* behavior of the preprocessor.
*/
rb_define_const(m_TranslationUnit_Flags,"Detailedpreprocessingrecord", INT2NUM(1));
/*
* Used to indicate that the translation unit is incomplete.
*
* When a translation unit is considered "incomplete", semantic
* analysis that is typically performed at the end of the
* translation unit will be suppressed. For example, this suppresses
* the completion of tentative declarations in C and of
* instantiation of implicitly-instantiation function templates in
* C++. This option is typically used when parsing a header with the
* intent of producing a precompiled header.
*/
rb_define_const(m_TranslationUnit_Flags,"Incomplete", INT2NUM(2));
/*
* Used to indicate that the translation unit should be built with an 
* implicit precompiled header for the preamble.
*
* An implicit precompiled header is used as an optimization when a
* particular translation unit is likely to be reparsed many times
* when the sources aren't changing that often. In this case, an
* implicit precompiled header will be built containing all of the
* initial includes at the top of the main file (what we refer to as
* the "preamble" of the file). In subsequent parses, if the
* preamble or the files in it have not changed, \c
* clang_reparseTranslationUnit() will re-use the implicit
* precompiled header to improve parsing performance.
*/
rb_define_const(m_TranslationUnit_Flags,"Precompiledpreamble", INT2NUM(4));
/*
* Used to indicate that the translation unit should cache some
* code-completion results with each reparse of the source file.
*
* Caching of code-completion results is a performance optimization that
* introduces some overhead to reparsing but improves the performance of
* code-completion operations.
*/
rb_define_const(m_TranslationUnit_Flags,"Cachecompletionresults", INT2NUM(8));
/*
* Used to indicate that the translation unit will be serialized with
* clang_saveTranslationUnit.
*
* This option is typically used when parsing a header with the intent of
* producing a precompiled header.
*/
rb_define_const(m_TranslationUnit_Flags,"Forserialization", INT2NUM(16));
/*
* DEPRECATED: Enabled chained precompiled preambles in C++.
*
* Note: this is a *temporary* option that is available only while
* we are testing C++ precompiled preamble support. It is deprecated.
*/
rb_define_const(m_TranslationUnit_Flags,"Cxxchainedpch", INT2NUM(32));
/*
* Used to indicate that function/method bodies should be skipped while
* parsing.
*
* This option can be used to search for declarations/definitions while
* ignoring the usages.
*/
rb_define_const(m_TranslationUnit_Flags,"Skipfunctionbodies", INT2NUM(64));
/*
* Used to indicate that brief documentation comments should be
* included into the set of code completions returned from this translation
* unit.
*/
rb_define_const(m_TranslationUnit_Flags,"Includebriefcommentsincodecompletion", INT2NUM(128));

VALUE m_SaveTranslationUnit_Flags = rb_define_module_under(m_clang,"SaveTranslationUnit_Flags");
rb_define_const(m_SaveTranslationUnit_Flags,"None", INT2NUM(0));

VALUE m_SaveError = rb_define_module_under(m_clang,"SaveError");
rb_define_const(m_SaveError,"None", INT2NUM(0));
rb_define_const(m_SaveError,"Unknown", INT2NUM(1));
rb_define_const(m_SaveError,"Translationerrors", INT2NUM(2));
rb_define_const(m_SaveError,"Invalidtu", INT2NUM(3));

VALUE m_Reparse_Flags = rb_define_module_under(m_clang,"Reparse_Flags");
rb_define_const(m_Reparse_Flags,"None", INT2NUM(0));

VALUE m_TUResourceUsageKind = rb_define_module_under(m_clang,"TUResourceUsageKind");
rb_define_const(m_TUResourceUsageKind,"Ast", INT2NUM(1));
rb_define_const(m_TUResourceUsageKind,"Identifiers", INT2NUM(2));
rb_define_const(m_TUResourceUsageKind,"Selectors", INT2NUM(3));
rb_define_const(m_TUResourceUsageKind,"Globalcompletionresults", INT2NUM(4));
rb_define_const(m_TUResourceUsageKind,"Sourcemanagercontentcache", INT2NUM(5));
rb_define_const(m_TUResourceUsageKind,"Ast_sidetables", INT2NUM(6));
rb_define_const(m_TUResourceUsageKind,"Sourcemanager_membuffer_malloc", INT2NUM(7));
rb_define_const(m_TUResourceUsageKind,"Sourcemanager_membuffer_mmap", INT2NUM(8));
rb_define_const(m_TUResourceUsageKind,"Externalastsource_membuffer_malloc", INT2NUM(9));
rb_define_const(m_TUResourceUsageKind,"Externalastsource_membuffer_mmap", INT2NUM(10));
rb_define_const(m_TUResourceUsageKind,"Preprocessor", INT2NUM(11));
rb_define_const(m_TUResourceUsageKind,"Preprocessingrecord", INT2NUM(12));
rb_define_const(m_TUResourceUsageKind,"Sourcemanager_datastructures", INT2NUM(13));
rb_define_const(m_TUResourceUsageKind,"Preprocessor_headersearch", INT2NUM(14));
rb_define_const(m_TUResourceUsageKind,"Memory_in_bytes_begin", INT2NUM(1));
rb_define_const(m_TUResourceUsageKind,"Memory_in_bytes_end", INT2NUM(14));
rb_define_const(m_TUResourceUsageKind,"First", INT2NUM(1));
rb_define_const(m_TUResourceUsageKind,"Last", INT2NUM(14));

VALUE m_CursorKind = rb_define_module_under(m_clang,"CursorKind");
rb_define_const(m_CursorKind,"Unexposeddecl", INT2NUM(1));
rb_define_const(m_CursorKind,"Structdecl", INT2NUM(2));
rb_define_const(m_CursorKind,"Uniondecl", INT2NUM(3));
rb_define_const(m_CursorKind,"Classdecl", INT2NUM(4));
rb_define_const(m_CursorKind,"Enumdecl", INT2NUM(5));
rb_define_const(m_CursorKind,"Fielddecl", INT2NUM(6));
rb_define_const(m_CursorKind,"Enumconstantdecl", INT2NUM(7));
rb_define_const(m_CursorKind,"Functiondecl", INT2NUM(8));
rb_define_const(m_CursorKind,"Vardecl", INT2NUM(9));
rb_define_const(m_CursorKind,"Parmdecl", INT2NUM(10));
rb_define_const(m_CursorKind,"Objcinterfacedecl", INT2NUM(11));
rb_define_const(m_CursorKind,"Objccategorydecl", INT2NUM(12));
rb_define_const(m_CursorKind,"Objcprotocoldecl", INT2NUM(13));
rb_define_const(m_CursorKind,"Objcpropertydecl", INT2NUM(14));
rb_define_const(m_CursorKind,"Objcivardecl", INT2NUM(15));
rb_define_const(m_CursorKind,"Objcinstancemethoddecl", INT2NUM(16));
rb_define_const(m_CursorKind,"Objcclassmethoddecl", INT2NUM(17));
rb_define_const(m_CursorKind,"Objcimplementationdecl", INT2NUM(18));
rb_define_const(m_CursorKind,"Objccategoryimpldecl", INT2NUM(19));
rb_define_const(m_CursorKind,"Typedefdecl", INT2NUM(20));
rb_define_const(m_CursorKind,"Cxxmethod", INT2NUM(21));
rb_define_const(m_CursorKind,"Namespace", INT2NUM(22));
rb_define_const(m_CursorKind,"Linkagespec", INT2NUM(23));
rb_define_const(m_CursorKind,"Constructor", INT2NUM(24));
rb_define_const(m_CursorKind,"Destructor", INT2NUM(25));
rb_define_const(m_CursorKind,"Conversionfunction", INT2NUM(26));
rb_define_const(m_CursorKind,"Templatetypeparameter", INT2NUM(27));
rb_define_const(m_CursorKind,"Nontypetemplateparameter", INT2NUM(28));
rb_define_const(m_CursorKind,"Templatetemplateparameter", INT2NUM(29));
rb_define_const(m_CursorKind,"Functiontemplate", INT2NUM(30));
rb_define_const(m_CursorKind,"Classtemplate", INT2NUM(31));
rb_define_const(m_CursorKind,"Classtemplatepartialspecialization", INT2NUM(32));
rb_define_const(m_CursorKind,"Namespacealias", INT2NUM(33));
rb_define_const(m_CursorKind,"Usingdirective", INT2NUM(34));
rb_define_const(m_CursorKind,"Usingdeclaration", INT2NUM(35));
rb_define_const(m_CursorKind,"Typealiasdecl", INT2NUM(36));
rb_define_const(m_CursorKind,"Objcsynthesizedecl", INT2NUM(37));
rb_define_const(m_CursorKind,"Objcdynamicdecl", INT2NUM(38));
rb_define_const(m_CursorKind,"Cxxaccessspecifier", INT2NUM(39));
rb_define_const(m_CursorKind,"Firstdecl", INT2NUM(1));
rb_define_const(m_CursorKind,"Lastdecl", INT2NUM(39));
rb_define_const(m_CursorKind,"Firstref", INT2NUM(40));
rb_define_const(m_CursorKind,"Objcsuperclassref", INT2NUM(40));
rb_define_const(m_CursorKind,"Objcprotocolref", INT2NUM(41));
rb_define_const(m_CursorKind,"Objcclassref", INT2NUM(42));
rb_define_const(m_CursorKind,"Typeref", INT2NUM(43));
rb_define_const(m_CursorKind,"Cxxbasespecifier", INT2NUM(44));
rb_define_const(m_CursorKind,"Templateref", INT2NUM(45));
rb_define_const(m_CursorKind,"Namespaceref", INT2NUM(46));
rb_define_const(m_CursorKind,"Memberref", INT2NUM(47));
rb_define_const(m_CursorKind,"Labelref", INT2NUM(48));
rb_define_const(m_CursorKind,"Overloadeddeclref", INT2NUM(49));
rb_define_const(m_CursorKind,"Variableref", INT2NUM(50));
rb_define_const(m_CursorKind,"Lastref", INT2NUM(50));
rb_define_const(m_CursorKind,"Firstinvalid", INT2NUM(70));
rb_define_const(m_CursorKind,"Invalidfile", INT2NUM(70));
rb_define_const(m_CursorKind,"Nodeclfound", INT2NUM(71));
rb_define_const(m_CursorKind,"Notimplemented", INT2NUM(72));
rb_define_const(m_CursorKind,"Invalidcode", INT2NUM(73));
rb_define_const(m_CursorKind,"Lastinvalid", INT2NUM(73));
rb_define_const(m_CursorKind,"Firstexpr", INT2NUM(100));
rb_define_const(m_CursorKind,"Unexposedexpr", INT2NUM(100));
rb_define_const(m_CursorKind,"Declrefexpr", INT2NUM(101));
rb_define_const(m_CursorKind,"Memberrefexpr", INT2NUM(102));
rb_define_const(m_CursorKind,"Callexpr", INT2NUM(103));
rb_define_const(m_CursorKind,"Objcmessageexpr", INT2NUM(104));
rb_define_const(m_CursorKind,"Blockexpr", INT2NUM(105));
rb_define_const(m_CursorKind,"Integerliteral", INT2NUM(106));
rb_define_const(m_CursorKind,"Floatingliteral", INT2NUM(107));
rb_define_const(m_CursorKind,"Imaginaryliteral", INT2NUM(108));
rb_define_const(m_CursorKind,"Stringliteral", INT2NUM(109));
rb_define_const(m_CursorKind,"Characterliteral", INT2NUM(110));
rb_define_const(m_CursorKind,"Parenexpr", INT2NUM(111));
rb_define_const(m_CursorKind,"Unaryoperator", INT2NUM(112));
rb_define_const(m_CursorKind,"Arraysubscriptexpr", INT2NUM(113));
rb_define_const(m_CursorKind,"Binaryoperator", INT2NUM(114));
rb_define_const(m_CursorKind,"Compoundassignoperator", INT2NUM(115));
rb_define_const(m_CursorKind,"Conditionaloperator", INT2NUM(116));
rb_define_const(m_CursorKind,"Cstylecastexpr", INT2NUM(117));
rb_define_const(m_CursorKind,"Compoundliteralexpr", INT2NUM(118));
rb_define_const(m_CursorKind,"Initlistexpr", INT2NUM(119));
rb_define_const(m_CursorKind,"Addrlabelexpr", INT2NUM(120));
rb_define_const(m_CursorKind,"Stmtexpr", INT2NUM(121));
rb_define_const(m_CursorKind,"Genericselectionexpr", INT2NUM(122));
rb_define_const(m_CursorKind,"Gnunullexpr", INT2NUM(123));
rb_define_const(m_CursorKind,"Cxxstaticcastexpr", INT2NUM(124));
rb_define_const(m_CursorKind,"Cxxdynamiccastexpr", INT2NUM(125));
rb_define_const(m_CursorKind,"Cxxreinterpretcastexpr", INT2NUM(126));
rb_define_const(m_CursorKind,"Cxxconstcastexpr", INT2NUM(127));
rb_define_const(m_CursorKind,"Cxxfunctionalcastexpr", INT2NUM(128));
rb_define_const(m_CursorKind,"Cxxtypeidexpr", INT2NUM(129));
rb_define_const(m_CursorKind,"Cxxboolliteralexpr", INT2NUM(130));
rb_define_const(m_CursorKind,"Cxxnullptrliteralexpr", INT2NUM(131));
rb_define_const(m_CursorKind,"Cxxthisexpr", INT2NUM(132));
rb_define_const(m_CursorKind,"Cxxthrowexpr", INT2NUM(133));
rb_define_const(m_CursorKind,"Cxxnewexpr", INT2NUM(134));
rb_define_const(m_CursorKind,"Cxxdeleteexpr", INT2NUM(135));
rb_define_const(m_CursorKind,"Unaryexpr", INT2NUM(136));
rb_define_const(m_CursorKind,"Objcstringliteral", INT2NUM(137));
rb_define_const(m_CursorKind,"Objcencodeexpr", INT2NUM(138));
rb_define_const(m_CursorKind,"Objcselectorexpr", INT2NUM(139));
rb_define_const(m_CursorKind,"Objcprotocolexpr", INT2NUM(140));
rb_define_const(m_CursorKind,"Objcbridgedcastexpr", INT2NUM(141));
rb_define_const(m_CursorKind,"Packexpansionexpr", INT2NUM(142));
rb_define_const(m_CursorKind,"Sizeofpackexpr", INT2NUM(143));
rb_define_const(m_CursorKind,"Lambdaexpr", INT2NUM(144));
rb_define_const(m_CursorKind,"Objcboolliteralexpr", INT2NUM(145));
rb_define_const(m_CursorKind,"Objcselfexpr", INT2NUM(146));
rb_define_const(m_CursorKind,"Lastexpr", INT2NUM(146));
rb_define_const(m_CursorKind,"Firststmt", INT2NUM(200));
rb_define_const(m_CursorKind,"Unexposedstmt", INT2NUM(200));
rb_define_const(m_CursorKind,"Labelstmt", INT2NUM(201));
rb_define_const(m_CursorKind,"Compoundstmt", INT2NUM(202));
rb_define_const(m_CursorKind,"Casestmt", INT2NUM(203));
rb_define_const(m_CursorKind,"Defaultstmt", INT2NUM(204));
rb_define_const(m_CursorKind,"Ifstmt", INT2NUM(205));
rb_define_const(m_CursorKind,"Switchstmt", INT2NUM(206));
rb_define_const(m_CursorKind,"Whilestmt", INT2NUM(207));
rb_define_const(m_CursorKind,"Dostmt", INT2NUM(208));
rb_define_const(m_CursorKind,"Forstmt", INT2NUM(209));
rb_define_const(m_CursorKind,"Gotostmt", INT2NUM(210));
rb_define_const(m_CursorKind,"Indirectgotostmt", INT2NUM(211));
rb_define_const(m_CursorKind,"Continuestmt", INT2NUM(212));
rb_define_const(m_CursorKind,"Breakstmt", INT2NUM(213));
rb_define_const(m_CursorKind,"Returnstmt", INT2NUM(214));
rb_define_const(m_CursorKind,"Gccasmstmt", INT2NUM(215));
rb_define_const(m_CursorKind,"Asmstmt", INT2NUM(215));
rb_define_const(m_CursorKind,"Objcattrystmt", INT2NUM(216));
rb_define_const(m_CursorKind,"Objcatcatchstmt", INT2NUM(217));
rb_define_const(m_CursorKind,"Objcatfinallystmt", INT2NUM(218));
rb_define_const(m_CursorKind,"Objcatthrowstmt", INT2NUM(219));
rb_define_const(m_CursorKind,"Objcatsynchronizedstmt", INT2NUM(220));
rb_define_const(m_CursorKind,"Objcautoreleasepoolstmt", INT2NUM(221));
rb_define_const(m_CursorKind,"Objcforcollectionstmt", INT2NUM(222));
rb_define_const(m_CursorKind,"Cxxcatchstmt", INT2NUM(223));
rb_define_const(m_CursorKind,"Cxxtrystmt", INT2NUM(224));
rb_define_const(m_CursorKind,"Cxxforrangestmt", INT2NUM(225));
rb_define_const(m_CursorKind,"Sehtrystmt", INT2NUM(226));
rb_define_const(m_CursorKind,"Sehexceptstmt", INT2NUM(227));
rb_define_const(m_CursorKind,"Sehfinallystmt", INT2NUM(228));
rb_define_const(m_CursorKind,"Msasmstmt", INT2NUM(229));
rb_define_const(m_CursorKind,"Nullstmt", INT2NUM(230));
rb_define_const(m_CursorKind,"Declstmt", INT2NUM(231));
rb_define_const(m_CursorKind,"Ompparalleldirective", INT2NUM(232));
rb_define_const(m_CursorKind,"Ompsimddirective", INT2NUM(233));
rb_define_const(m_CursorKind,"Ompfordirective", INT2NUM(234));
rb_define_const(m_CursorKind,"Ompsectionsdirective", INT2NUM(235));
rb_define_const(m_CursorKind,"Ompsectiondirective", INT2NUM(236));
rb_define_const(m_CursorKind,"Ompsingledirective", INT2NUM(237));
rb_define_const(m_CursorKind,"Ompparallelfordirective", INT2NUM(238));
rb_define_const(m_CursorKind,"Ompparallelsectionsdirective", INT2NUM(239));
rb_define_const(m_CursorKind,"Omptaskdirective", INT2NUM(240));
rb_define_const(m_CursorKind,"Ompmasterdirective", INT2NUM(241));
rb_define_const(m_CursorKind,"Ompcriticaldirective", INT2NUM(242));
rb_define_const(m_CursorKind,"Omptaskyielddirective", INT2NUM(243));
rb_define_const(m_CursorKind,"Ompbarrierdirective", INT2NUM(244));
rb_define_const(m_CursorKind,"Omptaskwaitdirective", INT2NUM(245));
rb_define_const(m_CursorKind,"Ompflushdirective", INT2NUM(246));
rb_define_const(m_CursorKind,"Sehleavestmt", INT2NUM(247));
rb_define_const(m_CursorKind,"Ompordereddirective", INT2NUM(248));
rb_define_const(m_CursorKind,"Ompatomicdirective", INT2NUM(249));
rb_define_const(m_CursorKind,"Ompforsimddirective", INT2NUM(250));
rb_define_const(m_CursorKind,"Ompparallelforsimddirective", INT2NUM(251));
rb_define_const(m_CursorKind,"Omptargetdirective", INT2NUM(252));
rb_define_const(m_CursorKind,"Ompteamsdirective", INT2NUM(253));
rb_define_const(m_CursorKind,"Laststmt", INT2NUM(253));
rb_define_const(m_CursorKind,"Translationunit", INT2NUM(300));
rb_define_const(m_CursorKind,"Firstattr", INT2NUM(400));
rb_define_const(m_CursorKind,"Unexposedattr", INT2NUM(400));
rb_define_const(m_CursorKind,"Ibactionattr", INT2NUM(401));
rb_define_const(m_CursorKind,"Iboutletattr", INT2NUM(402));
rb_define_const(m_CursorKind,"Iboutletcollectionattr", INT2NUM(403));
rb_define_const(m_CursorKind,"Cxxfinalattr", INT2NUM(404));
rb_define_const(m_CursorKind,"Cxxoverrideattr", INT2NUM(405));
rb_define_const(m_CursorKind,"Annotateattr", INT2NUM(406));
rb_define_const(m_CursorKind,"Asmlabelattr", INT2NUM(407));
rb_define_const(m_CursorKind,"Packedattr", INT2NUM(408));
rb_define_const(m_CursorKind,"Pureattr", INT2NUM(409));
rb_define_const(m_CursorKind,"Constattr", INT2NUM(410));
rb_define_const(m_CursorKind,"Noduplicateattr", INT2NUM(411));
rb_define_const(m_CursorKind,"Cudaconstantattr", INT2NUM(412));
rb_define_const(m_CursorKind,"Cudadeviceattr", INT2NUM(413));
rb_define_const(m_CursorKind,"Cudaglobalattr", INT2NUM(414));
rb_define_const(m_CursorKind,"Cudahostattr", INT2NUM(415));
rb_define_const(m_CursorKind,"Cudasharedattr", INT2NUM(416));
rb_define_const(m_CursorKind,"Lastattr", INT2NUM(416));
rb_define_const(m_CursorKind,"Preprocessingdirective", INT2NUM(500));
rb_define_const(m_CursorKind,"Macrodefinition", INT2NUM(501));
rb_define_const(m_CursorKind,"Macroexpansion", INT2NUM(502));
rb_define_const(m_CursorKind,"Macroinstantiation", INT2NUM(502));
rb_define_const(m_CursorKind,"Inclusiondirective", INT2NUM(503));
rb_define_const(m_CursorKind,"Firstpreprocessing", INT2NUM(500));
rb_define_const(m_CursorKind,"Lastpreprocessing", INT2NUM(503));
rb_define_const(m_CursorKind,"Moduleimportdecl", INT2NUM(600));
rb_define_const(m_CursorKind,"Firstextradecl", INT2NUM(600));
rb_define_const(m_CursorKind,"Lastextradecl", INT2NUM(600));

VALUE m_LinkageKind = rb_define_module_under(m_clang,"LinkageKind");
rb_define_const(m_LinkageKind,"Invalid", INT2NUM(0));
rb_define_const(m_LinkageKind,"Nolinkage", INT2NUM(1));
rb_define_const(m_LinkageKind,"Internal", INT2NUM(2));
rb_define_const(m_LinkageKind,"Uniqueexternal", INT2NUM(3));
rb_define_const(m_LinkageKind,"External", INT2NUM(4));

VALUE m_LanguageKind = rb_define_module_under(m_clang,"LanguageKind");
rb_define_const(m_LanguageKind,"Invalid", INT2NUM(0));
rb_define_const(m_LanguageKind,"C", INT2NUM(1));
rb_define_const(m_LanguageKind,"Objc", INT2NUM(2));
rb_define_const(m_LanguageKind,"Cplusplus", INT2NUM(3));

VALUE m_TypeKind = rb_define_module_under(m_clang,"TypeKind");
rb_define_const(m_TypeKind,"Invalid", INT2NUM(0));
rb_define_const(m_TypeKind,"Unexposed", INT2NUM(1));
rb_define_const(m_TypeKind,"Void", INT2NUM(2));
rb_define_const(m_TypeKind,"Bool", INT2NUM(3));
rb_define_const(m_TypeKind,"Char_u", INT2NUM(4));
rb_define_const(m_TypeKind,"Uchar", INT2NUM(5));
rb_define_const(m_TypeKind,"Char16", INT2NUM(6));
rb_define_const(m_TypeKind,"Char32", INT2NUM(7));
rb_define_const(m_TypeKind,"Ushort", INT2NUM(8));
rb_define_const(m_TypeKind,"Uint", INT2NUM(9));
rb_define_const(m_TypeKind,"Ulong", INT2NUM(10));
rb_define_const(m_TypeKind,"Ulonglong", INT2NUM(11));
rb_define_const(m_TypeKind,"Uint128", INT2NUM(12));
rb_define_const(m_TypeKind,"Char_s", INT2NUM(13));
rb_define_const(m_TypeKind,"Schar", INT2NUM(14));
rb_define_const(m_TypeKind,"Wchar", INT2NUM(15));
rb_define_const(m_TypeKind,"Short", INT2NUM(16));
rb_define_const(m_TypeKind,"Int", INT2NUM(17));
rb_define_const(m_TypeKind,"Long", INT2NUM(18));
rb_define_const(m_TypeKind,"Longlong", INT2NUM(19));
rb_define_const(m_TypeKind,"Int128", INT2NUM(20));
rb_define_const(m_TypeKind,"Float", INT2NUM(21));
rb_define_const(m_TypeKind,"Double", INT2NUM(22));
rb_define_const(m_TypeKind,"Longdouble", INT2NUM(23));
rb_define_const(m_TypeKind,"Nullptr", INT2NUM(24));
rb_define_const(m_TypeKind,"Overload", INT2NUM(25));
rb_define_const(m_TypeKind,"Dependent", INT2NUM(26));
rb_define_const(m_TypeKind,"Objcid", INT2NUM(27));
rb_define_const(m_TypeKind,"Objcclass", INT2NUM(28));
rb_define_const(m_TypeKind,"Objcsel", INT2NUM(29));
rb_define_const(m_TypeKind,"Firstbuiltin", INT2NUM(2));
rb_define_const(m_TypeKind,"Lastbuiltin", INT2NUM(29));
rb_define_const(m_TypeKind,"Complex", INT2NUM(100));
rb_define_const(m_TypeKind,"Pointer", INT2NUM(101));
rb_define_const(m_TypeKind,"Blockpointer", INT2NUM(102));
rb_define_const(m_TypeKind,"Lvaluereference", INT2NUM(103));
rb_define_const(m_TypeKind,"Rvaluereference", INT2NUM(104));
rb_define_const(m_TypeKind,"Record", INT2NUM(105));
rb_define_const(m_TypeKind,"Enum", INT2NUM(106));
rb_define_const(m_TypeKind,"Typedef", INT2NUM(107));
rb_define_const(m_TypeKind,"Objcinterface", INT2NUM(108));
rb_define_const(m_TypeKind,"Objcobjectpointer", INT2NUM(109));
rb_define_const(m_TypeKind,"Functionnoproto", INT2NUM(110));
rb_define_const(m_TypeKind,"Functionproto", INT2NUM(111));
rb_define_const(m_TypeKind,"Constantarray", INT2NUM(112));
rb_define_const(m_TypeKind,"Vector", INT2NUM(113));
rb_define_const(m_TypeKind,"Incompletearray", INT2NUM(114));
rb_define_const(m_TypeKind,"Variablearray", INT2NUM(115));
rb_define_const(m_TypeKind,"Dependentsizedarray", INT2NUM(116));
rb_define_const(m_TypeKind,"Memberpointer", INT2NUM(117));

VALUE m_CallingConv = rb_define_module_under(m_clang,"CallingConv");
rb_define_const(m_CallingConv,"Default", INT2NUM(0));
rb_define_const(m_CallingConv,"C", INT2NUM(1));
rb_define_const(m_CallingConv,"X86stdcall", INT2NUM(2));
rb_define_const(m_CallingConv,"X86fastcall", INT2NUM(3));
rb_define_const(m_CallingConv,"X86thiscall", INT2NUM(4));
rb_define_const(m_CallingConv,"X86pascal", INT2NUM(5));
rb_define_const(m_CallingConv,"Aapcs", INT2NUM(6));
rb_define_const(m_CallingConv,"Aapcs_vfp", INT2NUM(7));
rb_define_const(m_CallingConv,"Pnaclcall", INT2NUM(8));
rb_define_const(m_CallingConv,"Inteloclbicc", INT2NUM(9));
rb_define_const(m_CallingConv,"X86_64win64", INT2NUM(10));
rb_define_const(m_CallingConv,"X86_64sysv", INT2NUM(11));
rb_define_const(m_CallingConv,"X86vectorcall", INT2NUM(12));
rb_define_const(m_CallingConv,"Invalid", INT2NUM(100));
rb_define_const(m_CallingConv,"Unexposed", INT2NUM(200));

VALUE m_TemplateArgumentKind = rb_define_module_under(m_clang,"TemplateArgumentKind");
rb_define_const(m_TemplateArgumentKind,"Null", INT2NUM(0));
rb_define_const(m_TemplateArgumentKind,"Type", INT2NUM(1));
rb_define_const(m_TemplateArgumentKind,"Declaration", INT2NUM(2));
rb_define_const(m_TemplateArgumentKind,"Nullptr", INT2NUM(3));
rb_define_const(m_TemplateArgumentKind,"Integral", INT2NUM(4));
rb_define_const(m_TemplateArgumentKind,"Template", INT2NUM(5));
rb_define_const(m_TemplateArgumentKind,"Templateexpansion", INT2NUM(6));
rb_define_const(m_TemplateArgumentKind,"Expression", INT2NUM(7));
rb_define_const(m_TemplateArgumentKind,"Pack", INT2NUM(8));
rb_define_const(m_TemplateArgumentKind,"Invalid", INT2NUM(9));

VALUE m_TypeLayoutError = rb_define_module_under(m_clang,"TypeLayoutError");
rb_define_const(m_TypeLayoutError,"Invalid", INT2NUM(-1));
rb_define_const(m_TypeLayoutError,"Incomplete", INT2NUM(-2));
rb_define_const(m_TypeLayoutError,"Dependent", INT2NUM(-3));
rb_define_const(m_TypeLayoutError,"Notconstantsize", INT2NUM(-4));
rb_define_const(m_TypeLayoutError,"Invalidfieldname", INT2NUM(-5));

VALUE m_RefQualifierKind = rb_define_module_under(m_clang,"RefQualifierKind");
rb_define_const(m_RefQualifierKind,"None", INT2NUM(0));
rb_define_const(m_RefQualifierKind,"Lvalue", INT2NUM(1));
rb_define_const(m_RefQualifierKind,"Rvalue", INT2NUM(2));

VALUE m__XAccessSpecifier = rb_define_module_under(m_clang,"_XAccessSpecifier");
rb_define_const(m__XAccessSpecifier,"Cxxinvalidaccessspecifier", INT2NUM(0));
rb_define_const(m__XAccessSpecifier,"Cxxpublic", INT2NUM(1));
rb_define_const(m__XAccessSpecifier,"Cxxprotected", INT2NUM(2));
rb_define_const(m__XAccessSpecifier,"Cxxprivate", INT2NUM(3));

VALUE m__StorageClass = rb_define_module_under(m_clang,"_StorageClass");
rb_define_const(m__StorageClass,"Sc_invalid", INT2NUM(0));
rb_define_const(m__StorageClass,"Sc_none", INT2NUM(1));
rb_define_const(m__StorageClass,"Sc_extern", INT2NUM(2));
rb_define_const(m__StorageClass,"Sc_static", INT2NUM(3));
rb_define_const(m__StorageClass,"Sc_privateextern", INT2NUM(4));
rb_define_const(m__StorageClass,"Sc_openclworkgrouplocal", INT2NUM(5));
rb_define_const(m__StorageClass,"Sc_auto", INT2NUM(6));
rb_define_const(m__StorageClass,"Sc_register", INT2NUM(7));

VALUE m_ChildVisitResult = rb_define_module_under(m_clang,"ChildVisitResult");
rb_define_const(m_ChildVisitResult,"Break", INT2NUM(0));
rb_define_const(m_ChildVisitResult,"Continue", INT2NUM(1));
rb_define_const(m_ChildVisitResult,"Recurse", INT2NUM(2));

VALUE m_ObjCPropertyAttrKind = rb_define_module_under(m_clang,"ObjCPropertyAttrKind");
rb_define_const(m_ObjCPropertyAttrKind,"Noattr", INT2NUM(0));
rb_define_const(m_ObjCPropertyAttrKind,"Readonly", INT2NUM(1));
rb_define_const(m_ObjCPropertyAttrKind,"Getter", INT2NUM(2));
rb_define_const(m_ObjCPropertyAttrKind,"Assign", INT2NUM(4));
rb_define_const(m_ObjCPropertyAttrKind,"Readwrite", INT2NUM(8));
rb_define_const(m_ObjCPropertyAttrKind,"Retain", INT2NUM(16));
rb_define_const(m_ObjCPropertyAttrKind,"Copy", INT2NUM(32));
rb_define_const(m_ObjCPropertyAttrKind,"Nonatomic", INT2NUM(64));
rb_define_const(m_ObjCPropertyAttrKind,"Setter", INT2NUM(128));
rb_define_const(m_ObjCPropertyAttrKind,"Atomic", INT2NUM(256));
rb_define_const(m_ObjCPropertyAttrKind,"Weak", INT2NUM(512));
rb_define_const(m_ObjCPropertyAttrKind,"Strong", INT2NUM(1024));
rb_define_const(m_ObjCPropertyAttrKind,"Unsafe_unretained", INT2NUM(2048));

VALUE m_ObjCDeclQualifierKind = rb_define_module_under(m_clang,"ObjCDeclQualifierKind");
rb_define_const(m_ObjCDeclQualifierKind,"None", INT2NUM(0));
rb_define_const(m_ObjCDeclQualifierKind,"In", INT2NUM(1));
rb_define_const(m_ObjCDeclQualifierKind,"Inout", INT2NUM(2));
rb_define_const(m_ObjCDeclQualifierKind,"Out", INT2NUM(4));
rb_define_const(m_ObjCDeclQualifierKind,"Bycopy", INT2NUM(8));
rb_define_const(m_ObjCDeclQualifierKind,"Byref", INT2NUM(16));
rb_define_const(m_ObjCDeclQualifierKind,"Oneway", INT2NUM(32));

VALUE m_NameRefFlags = rb_define_module_under(m_clang,"NameRefFlags");
rb_define_const(m_NameRefFlags,"Wantqualifier", INT2NUM(1));
rb_define_const(m_NameRefFlags,"Wanttemplateargs", INT2NUM(2));
rb_define_const(m_NameRefFlags,"Wantsinglepiece", INT2NUM(4));

VALUE m_TokenKind = rb_define_module_under(m_clang,"TokenKind");
rb_define_const(m_TokenKind,"Punctuation", INT2NUM(0));
rb_define_const(m_TokenKind,"Keyword", INT2NUM(1));
rb_define_const(m_TokenKind,"Identifier", INT2NUM(2));
rb_define_const(m_TokenKind,"Literal", INT2NUM(3));
rb_define_const(m_TokenKind,"Comment", INT2NUM(4));

VALUE m_CompletionChunkKind = rb_define_module_under(m_clang,"CompletionChunkKind");
rb_define_const(m_CompletionChunkKind,"Optional", INT2NUM(0));
rb_define_const(m_CompletionChunkKind,"Typedtext", INT2NUM(1));
rb_define_const(m_CompletionChunkKind,"Text", INT2NUM(2));
rb_define_const(m_CompletionChunkKind,"Placeholder", INT2NUM(3));
rb_define_const(m_CompletionChunkKind,"Informative", INT2NUM(4));
rb_define_const(m_CompletionChunkKind,"Currentparameter", INT2NUM(5));
rb_define_const(m_CompletionChunkKind,"Leftparen", INT2NUM(6));
rb_define_const(m_CompletionChunkKind,"Rightparen", INT2NUM(7));
rb_define_const(m_CompletionChunkKind,"Leftbracket", INT2NUM(8));
rb_define_const(m_CompletionChunkKind,"Rightbracket", INT2NUM(9));
rb_define_const(m_CompletionChunkKind,"Leftbrace", INT2NUM(10));
rb_define_const(m_CompletionChunkKind,"Rightbrace", INT2NUM(11));
rb_define_const(m_CompletionChunkKind,"Leftangle", INT2NUM(12));
rb_define_const(m_CompletionChunkKind,"Rightangle", INT2NUM(13));
rb_define_const(m_CompletionChunkKind,"Comma", INT2NUM(14));
rb_define_const(m_CompletionChunkKind,"Resulttype", INT2NUM(15));
rb_define_const(m_CompletionChunkKind,"Colon", INT2NUM(16));
rb_define_const(m_CompletionChunkKind,"Semicolon", INT2NUM(17));
rb_define_const(m_CompletionChunkKind,"Equal", INT2NUM(18));
rb_define_const(m_CompletionChunkKind,"Horizontalspace", INT2NUM(19));
rb_define_const(m_CompletionChunkKind,"Verticalspace", INT2NUM(20));

VALUE m_CodeComplete_Flags = rb_define_module_under(m_clang,"CodeComplete_Flags");
rb_define_const(m_CodeComplete_Flags,"Includemacros", INT2NUM(1));
rb_define_const(m_CodeComplete_Flags,"Includecodepatterns", INT2NUM(2));
rb_define_const(m_CodeComplete_Flags,"Includebriefcomments", INT2NUM(4));

VALUE m_CompletionContext = rb_define_module_under(m_clang,"CompletionContext");
rb_define_const(m_CompletionContext,"Unexposed", INT2NUM(0));
rb_define_const(m_CompletionContext,"Anytype", INT2NUM(1));
rb_define_const(m_CompletionContext,"Anyvalue", INT2NUM(2));
rb_define_const(m_CompletionContext,"Objcobjectvalue", INT2NUM(4));
rb_define_const(m_CompletionContext,"Objcselectorvalue", INT2NUM(8));
rb_define_const(m_CompletionContext,"Cxxclasstypevalue", INT2NUM(16));
rb_define_const(m_CompletionContext,"Dotmemberaccess", INT2NUM(32));
rb_define_const(m_CompletionContext,"Arrowmemberaccess", INT2NUM(64));
rb_define_const(m_CompletionContext,"Objcpropertyaccess", INT2NUM(128));
rb_define_const(m_CompletionContext,"Enumtag", INT2NUM(256));
rb_define_const(m_CompletionContext,"Uniontag", INT2NUM(512));
rb_define_const(m_CompletionContext,"Structtag", INT2NUM(1024));
rb_define_const(m_CompletionContext,"Classtag", INT2NUM(2048));
rb_define_const(m_CompletionContext,"Namespace", INT2NUM(4096));
rb_define_const(m_CompletionContext,"Nestednamespecifier", INT2NUM(8192));
rb_define_const(m_CompletionContext,"Objcinterface", INT2NUM(16384));
rb_define_const(m_CompletionContext,"Objcprotocol", INT2NUM(32768));
rb_define_const(m_CompletionContext,"Objccategory", INT2NUM(65536));
rb_define_const(m_CompletionContext,"Objcinstancemessage", INT2NUM(131072));
rb_define_const(m_CompletionContext,"Objcclassmessage", INT2NUM(262144));
rb_define_const(m_CompletionContext,"Objcselectorname", INT2NUM(524288));
rb_define_const(m_CompletionContext,"Macroname", INT2NUM(1048576));
rb_define_const(m_CompletionContext,"Naturallanguage", INT2NUM(2097152));
rb_define_const(m_CompletionContext,"Unknown", INT2NUM(4194303));

VALUE m_VisitorResult = rb_define_module_under(m_clang,"VisitorResult");
rb_define_const(m_VisitorResult,"Break", INT2NUM(0));
rb_define_const(m_VisitorResult,"Continue", INT2NUM(1));

VALUE m_Result = rb_define_module_under(m_clang,"Result");
rb_define_const(m_Result,"Success", INT2NUM(0));
rb_define_const(m_Result,"Invalid", INT2NUM(1));
rb_define_const(m_Result,"Visitbreak", INT2NUM(2));

VALUE m_IdxEntityKind = rb_define_module_under(m_clang,"IdxEntityKind");
rb_define_const(m_IdxEntityKind,"Unexposed", INT2NUM(0));
rb_define_const(m_IdxEntityKind,"Typedef", INT2NUM(1));
rb_define_const(m_IdxEntityKind,"Function", INT2NUM(2));
rb_define_const(m_IdxEntityKind,"Variable", INT2NUM(3));
rb_define_const(m_IdxEntityKind,"Field", INT2NUM(4));
rb_define_const(m_IdxEntityKind,"Enumconstant", INT2NUM(5));
rb_define_const(m_IdxEntityKind,"Objcclass", INT2NUM(6));
rb_define_const(m_IdxEntityKind,"Objcprotocol", INT2NUM(7));
rb_define_const(m_IdxEntityKind,"Objccategory", INT2NUM(8));
rb_define_const(m_IdxEntityKind,"Objcinstancemethod", INT2NUM(9));
rb_define_const(m_IdxEntityKind,"Objcclassmethod", INT2NUM(10));
rb_define_const(m_IdxEntityKind,"Objcproperty", INT2NUM(11));
rb_define_const(m_IdxEntityKind,"Objcivar", INT2NUM(12));
rb_define_const(m_IdxEntityKind,"Enum", INT2NUM(13));
rb_define_const(m_IdxEntityKind,"Struct", INT2NUM(14));
rb_define_const(m_IdxEntityKind,"Union", INT2NUM(15));
rb_define_const(m_IdxEntityKind,"Cxxclass", INT2NUM(16));
rb_define_const(m_IdxEntityKind,"Cxxnamespace", INT2NUM(17));
rb_define_const(m_IdxEntityKind,"Cxxnamespacealias", INT2NUM(18));
rb_define_const(m_IdxEntityKind,"Cxxstaticvariable", INT2NUM(19));
rb_define_const(m_IdxEntityKind,"Cxxstaticmethod", INT2NUM(20));
rb_define_const(m_IdxEntityKind,"Cxxinstancemethod", INT2NUM(21));
rb_define_const(m_IdxEntityKind,"Cxxconstructor", INT2NUM(22));
rb_define_const(m_IdxEntityKind,"Cxxdestructor", INT2NUM(23));
rb_define_const(m_IdxEntityKind,"Cxxconversionfunction", INT2NUM(24));
rb_define_const(m_IdxEntityKind,"Cxxtypealias", INT2NUM(25));
rb_define_const(m_IdxEntityKind,"Cxxinterface", INT2NUM(26));

VALUE m_IdxEntityLanguage = rb_define_module_under(m_clang,"IdxEntityLanguage");
rb_define_const(m_IdxEntityLanguage,"None", INT2NUM(0));
rb_define_const(m_IdxEntityLanguage,"C", INT2NUM(1));
rb_define_const(m_IdxEntityLanguage,"Objc", INT2NUM(2));
rb_define_const(m_IdxEntityLanguage,"Cxx", INT2NUM(3));

VALUE m_IdxEntityXTemplateKind = rb_define_module_under(m_clang,"IdxEntityXTemplateKind");
rb_define_const(m_IdxEntityXTemplateKind,"Nontemplate", INT2NUM(0));
rb_define_const(m_IdxEntityXTemplateKind,"Template", INT2NUM(1));
rb_define_const(m_IdxEntityXTemplateKind,"Templatepartialspecialization", INT2NUM(2));
rb_define_const(m_IdxEntityXTemplateKind,"Templatespecialization", INT2NUM(3));

VALUE m_IdxAttrKind = rb_define_module_under(m_clang,"IdxAttrKind");
rb_define_const(m_IdxAttrKind,"Unexposed", INT2NUM(0));
rb_define_const(m_IdxAttrKind,"Ibaction", INT2NUM(1));
rb_define_const(m_IdxAttrKind,"Iboutlet", INT2NUM(2));
rb_define_const(m_IdxAttrKind,"Iboutletcollection", INT2NUM(3));

VALUE m_IdxDeclInfoFlags = rb_define_module_under(m_clang,"IdxDeclInfoFlags");
rb_define_const(m_IdxDeclInfoFlags,"Skipped", INT2NUM(1));

VALUE m_IdxObjCContainerKind = rb_define_module_under(m_clang,"IdxObjCContainerKind");
rb_define_const(m_IdxObjCContainerKind,"Forwardref", INT2NUM(0));
rb_define_const(m_IdxObjCContainerKind,"Interface", INT2NUM(1));
rb_define_const(m_IdxObjCContainerKind,"Implementation", INT2NUM(2));

VALUE m_IdxEntityRefKind = rb_define_module_under(m_clang,"IdxEntityRefKind");
rb_define_const(m_IdxEntityRefKind,"Direct", INT2NUM(1));
rb_define_const(m_IdxEntityRefKind,"Implicit", INT2NUM(2));

VALUE m_IndexOptFlags = rb_define_module_under(m_clang,"IndexOptFlags");
rb_define_const(m_IndexOptFlags,"None", INT2NUM(0));
rb_define_const(m_IndexOptFlags,"Suppressredundantrefs", INT2NUM(1));
rb_define_const(m_IndexOptFlags,"Indexfunctionlocalsymbols", INT2NUM(2));
rb_define_const(m_IndexOptFlags,"Indeximplicittemplateinstantiations", INT2NUM(4));
rb_define_const(m_IndexOptFlags,"Suppresswarnings", INT2NUM(8));
rb_define_const(m_IndexOptFlags,"Skipparsedbodiesinsession", INT2NUM(16));

//From CXErrorCode.h
VALUE m_ErrorCode = rb_define_module_under(m_clang,"ErrorCode");
rb_define_const(m_ErrorCode,"Success", INT2NUM(0));
rb_define_const(m_ErrorCode,"Failure", INT2NUM(1));
rb_define_const(m_ErrorCode,"Crashed", INT2NUM(2));
rb_define_const(m_ErrorCode,"Invalidarguments", INT2NUM(3));
rb_define_const(m_ErrorCode,"Astreaderror", INT2NUM(4));

}
