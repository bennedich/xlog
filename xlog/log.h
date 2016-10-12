#pragma once

#include <iostream>
#include <cstdio>

#define _XLOG( file )                     \
va_list argptr;                           \
va_start( argptr, format.c_str() );       \
vfprintf( file, format.c_str(), argptr ); \
va_end( argptr );

namespace xlog
{
	const char* VERSION =
		#include "version.txt"
	;
	
	using FuncLogFile = void(*)( FILE* file, const std::string& format, ... );
	using FuncLogFileCat = void(*)( FILE* file, const std::string& category, const std::string& format, ... );

	using FuncLog = void(*)( const std::string& format, ... );
	using FuncLogCat = void(*)( const std::string& category, const std::string& format, ... );

	void flog_void( FILE*, const std::string&, ... ) {}
	void flog_cat_void( FILE*, const std::string&, const std::string&, ... ) {}

	void log_void( const std::string&, ... ) {}
	void log_cat_void( const std::string&, const std::string&, ... ) {}

	void flog_default( FILE* f, const std::string& format, ... )
	{
		_XLOG( f );
		fprintf( f, "\n" );
	}

	void flog_cat_default( FILE* f, const std::string& category, const std::string& format, ... )
	{
		fprintf( f, "[%s] ", category.c_str() );
		_XLOG( f );
		fprintf( f, "\n" );
	}

	void log_default( const std::string& format, ... )
	{
		_XLOG( stdout );
		fprintf( stdout, "\n" );
	}

	void log_cat_default( const std::string& category, const std::string& format, ... )
	{
		fprintf( stdout, "[%s] ", category.c_str() );
		_XLOG( stdout );
		fprintf( stdout, "\n" );
	}

	FuncLogFile flog = flog_default;
	FuncLogFileCat flog_cat = flog_cat_default;

	FuncLog log = log_default;
	FuncLogCat log_cat = log_cat_default;
}

#undef _XLOG

#define XLOG     xlog::log
#define XLOG_CAT xlog::log_cat
