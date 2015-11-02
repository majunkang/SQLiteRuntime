#include "pch.h"

#include <sqlite3.h>

#include "SQLiteConnection.h"
#include "SQLiteStatement.h"
#include "SQLiteConfig.h"

#define THROW_SQL_EXCEPTION(CONNECTION, RESULT) \
const wchar_t* errmsg = (const wchar_t*)sqlite3_errmsg16(CONNECTION); \
auto exceptionMessage = ref new Platform::String(errmsg); \
int errorCode = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_SQLITE, RESULT); \
throw Platform::Exception::CreateException(errorCode, exceptionMessage);

namespace SQLiteRuntime
{
	SQLiteConnection::~SQLiteConnection()
	{
		if (m_connection != nullptr)
		{
			sqlite3_close(m_connection);
			m_connection = nullptr;
		}
	}

	SQLiteConnection^ SQLiteConnection::Open(Platform::String^ filename)
	{
		SQLiteConfig^ config = SQLiteConfig::Default;

		if (!config->IsTempDirectorySet)
		{
			config->SetTempDirectory();
		}

		const wchar_t* filenameData = filename->Data();
		sqlite3* pDb = nullptr;

		int result = sqlite3_open16(
			filenameData,
			&pDb
			);

		if (SQLITE_OK == result)
		{
			auto connection = ref new SQLiteConnection(pDb);
			return connection;
		}
		else
		{
			// TODO: Log Error
			return nullptr;
		}
	}

	SQLiteConnection::SQLiteConnection(sqlite3* connection)
	{
		m_connection = connection;
	}

	SQLiteStatement ^ SQLiteConnection::Prepare(Platform::String ^ sql)
	{
		const wchar_t* sqlData = sql->Data();

		sqlite3_stmt* stmt = nullptr;
		int result = sqlite3_prepare16_v2(m_connection, sqlData, -1, &stmt, nullptr);

		if (result == SQLITE_OK)
		{
			SQLiteStatement^ statement = ref new SQLiteStatement(stmt, m_connection);
			return statement;
		}

		if (stmt != nullptr)
		{
			sqlite3_finalize(stmt);
		}

		THROW_SQL_EXCEPTION(m_connection, result);

		return nullptr;
	}
}
