#include "pch.h"

#include <sqlite3.h>

#include "SQLiteStatement.h"

using namespace SQLiteRuntime;

#define THROW_SQL_EXCEPTION(CONNECTION, RESULT) \
const wchar_t* errmsg = (const wchar_t*)sqlite3_errmsg16(CONNECTION); \
auto exceptionMessage = ref new Platform::String(errmsg); \
int errorCode = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_SQLITE, RESULT); \
throw Platform::Exception::CreateException(errorCode, exceptionMessage);

SQLiteStatement::SQLiteStatement(sqlite3_stmt* stmt, sqlite3* conn)
{
	m_stmt = stmt;
	m_conn = conn;
}

SQLiteStatement::~SQLiteStatement()
{
	if (m_stmt != nullptr)
	{
		sqlite3_finalize(m_stmt);
		m_stmt = nullptr;
	}
}

SQLiteResult SQLiteStatement::Step()
{
	int result = sqlite3_step(m_stmt);
	return (SQLiteResult)result;
}

SQLiteResult SQLiteRuntime::SQLiteStatement::Reset()
{
	int result = sqlite3_reset(m_stmt);
	return (SQLiteResult)result;
}

SQLiteResult SQLiteStatement::Bind(int index, int value)
{
	int result = sqlite3_bind_int(m_stmt, index, value);

	if (result == SQLITE_OK)
		return (SQLiteResult)result;

	THROW_SQL_EXCEPTION(m_conn, result);
}

SQLiteResult SQLiteStatement::Bind(int index, int64 value)
{
	int result = sqlite3_bind_int64(m_stmt, index, value);

	if (result == SQLITE_OK)
		return (SQLiteResult)result;

	THROW_SQL_EXCEPTION(m_conn, result);

}

SQLiteResult SQLiteStatement::Bind(int index, double value)
{
	int result = sqlite3_bind_double(m_stmt, index, value);

	if (result == SQLITE_OK)
		return (SQLiteResult)result;

	THROW_SQL_EXCEPTION(m_conn, result);
}

SQLiteResult SQLiteStatement::Bind(int index, Platform::String ^ value)
{
	if (value == nullptr)
	{
		return BindNull(index);
	}
	else
	{
		const char* data = (const char*)value->Data();
		int length = value->Length() * 2;

		int result = sqlite3_bind_text64(m_stmt, index, data, length, SQLITE_TRANSIENT, SQLITE_UTF16);

		if (result == SQLITE_OK)
			return (SQLiteResult)result;

		THROW_SQL_EXCEPTION(m_conn, result);
	}
}

SQLiteResult SQLiteStatement::BindNull(int index)
{
	int result = sqlite3_bind_null(m_stmt, index);

	if (result == SQLITE_OK)
		return (SQLiteResult)result;

	THROW_SQL_EXCEPTION(m_conn, result);
}

SQLiteResult SQLiteStatement::ClearBinding()
{
	int result = sqlite3_clear_bindings(m_stmt);
	return (SQLiteResult)result;
}

int64 SQLiteStatement::GetColumnInt64Value(int index)
{
	int64 value = sqlite3_column_int64(m_stmt, index);
	return value;
}

int SQLiteStatement::GetColumnIntValue(int index)
{
	int value = sqlite3_column_int(m_stmt, index);
	return value;
}

double SQLiteStatement::GetColumnDoubleValue(int index)
{
	double value = sqlite3_column_double(m_stmt, index);
	return value;
}

Platform::String^ SQLiteStatement::GetColumnStringValue(int index)
{
	// Strings returned by sqlite3_column_text() and sqlite3_column_text16()
	// , even empty strings, are always zero-terminated.
	const wchar_t* value = (const wchar_t*)sqlite3_column_text16(m_stmt, index);

	if (value != nullptr)
	{
		auto wideString = ref new Platform::String(value);
		return wideString;
	}

	return nullptr;
}
