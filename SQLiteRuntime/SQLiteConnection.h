#pragma once


struct sqlite3;

namespace SQLiteRuntime
{
	ref class SQLiteStatement;

	public ref class SQLiteConnection sealed
	{

	internal:
		SQLiteConnection(sqlite3* connection);

	public:
		virtual ~SQLiteConnection();

		static SQLiteConnection^ Open(Platform::String^ file);
		SQLiteStatement^ Prepare(Platform::String^ sql);


	private:
		sqlite3* m_connection;
	};
}
