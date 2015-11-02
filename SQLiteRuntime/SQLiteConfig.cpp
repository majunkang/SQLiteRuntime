#include "pch.h"
#include "SQLiteConfig.h"

using namespace SQLiteRuntime;
using namespace Platform;

#include <sqlite3.h>

extern "C" { SQLITE_API int sqlite3_win32_set_directory(unsigned long type, const wchar_t* zValue); };


SQLiteConfig^ SQLiteConfig::Default::get()
{
	static SQLiteConfig^ g_sqliteConfig;

	if (g_sqliteConfig == nullptr)
	{
		g_sqliteConfig = ref new SQLiteConfig();
	}

	return g_sqliteConfig;
}

SQLiteConfig::SQLiteConfig()
{
	Init();
}

void SQLiteConfig::Init()
{
}

void SQLiteConfig::SetTempDirectory()
{
	Platform::String^ tempDirectory = Windows::Storage::ApplicationData::Current->
		TemporaryFolder->Path;

	const wchar_t* zPath = tempDirectory->Data();

	int result = sqlite3_win32_set_directory(2, zPath);

	if (result != SQLITE_OK)
	{
		// LOG Error
	}
}

//void SQLiteConfig::SetTempDirectory()
//{
//	Platform::String^ tempDirectory = Windows::Storage::ApplicationData::Current->
//		TemporaryFolder->Path;
//
//	LPCWSTR zPath = tempDirectory->Data();
//
//	char zPathBuf[MAX_PATH + 1];
//	memset(zPathBuf, 0, sizeof(zPathBuf));
//
//	WideCharToMultiByte(CP_UTF8, 0, zPath, -1, zPathBuf, sizeof(zPathBuf),
//		NULL, NULL);
//
//	char *sqliteDirectory = sqlite3_mprintf("%s", zPathBuf);
//
//	sqlite3_temp_directory = sqliteDirectory;
//
//	m_tempDirectory = tempDirectory;
//
//	m_isTempDirectorySet = true;
//}

Platform::String^ SQLiteConfig::GetTempDirectory()
{
	return m_tempDirectory;
}

LPSTR ConvertPlatformStringToUTF8(Platform::String^ filename)
{
	LPCWCH lpWideCharStr = filename->Data();
	int cchWideChar = filename->Length();

	int cbMultiByte = 0;

	int requiredBuffer = WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, cchWideChar, NULL, cbMultiByte, NULL, NULL);

	LPSTR lpMultiBufferStr = new char[requiredBuffer];

	WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, cchWideChar, lpMultiBufferStr, requiredBuffer, NULL, NULL);

	return lpMultiBufferStr;
}

