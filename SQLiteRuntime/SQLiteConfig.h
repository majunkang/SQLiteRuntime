#pragma once

#include "SQLiteResult.h"

namespace SQLiteRuntime
{
    public ref class SQLiteConfig sealed
    {
    public:
		static property SQLiteConfig^ Default { SQLiteConfig^ get();}

		Platform::String^ GetTempDirectory();

		property bool IsTempDirectorySet { bool get() { return m_isTempDirectorySet; }}

		void SetTempDirectory();

	private:
        SQLiteConfig();
		void Init();

		Platform::String^ m_tempDirectory;

		bool m_isTempDirectorySet;
    };
}
