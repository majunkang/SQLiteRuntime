#pragma once

#include "SQLiteResult.h"

struct sql3_stmt;

namespace SQLiteRuntime
{
	public ref class SQLiteStatement sealed
	{
	internal:
		SQLiteStatement(sqlite3_stmt* stmt, sqlite3* conn);

	public:
		virtual ~SQLiteStatement();

		SQLiteResult Step();
		SQLiteResult Reset();
		SQLiteResult Bind(int index, int value);
		SQLiteResult Bind(int index, int64 value);
		SQLiteResult Bind(int index, double value);

		[Windows::Foundation::Metadata::DefaultOverload]
		SQLiteResult Bind(int index, Platform::String^ value);
		SQLiteResult BindNull(int index);

		SQLiteResult ClearBinding();

		Platform::String^ GetColumnStringValue(int index);
		int64 GetColumnInt64Value(int index);
		int GetColumnIntValue(int index);
		double GetColumnDoubleValue(int index);


	private:
		sqlite3_stmt* m_stmt;
		sqlite3* m_conn;
	};
}

