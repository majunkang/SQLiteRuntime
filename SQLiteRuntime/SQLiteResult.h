#pragma once

namespace SQLiteRuntime
{
	// Mapping SQLite Result Codes from C Macro to C++/CX Enum
	// See https://www.sqlite.org/rescode.html for full list of SQLite Result Codes
	public enum class SQLiteResult : int
	{
		OK = 0,
		Error = 1,
		Internal = 2,
		Perm = 3,
		Abort = 4,
		Budy = 5,
		Locked = 6,
		Nomem = 7,
		Readonly = 8,
		Interrupt = 9,
		IOErr = 10,
		Corrupt = 11,
		NotFound = 12,
		Full = 13,
		CantOpen = 14,
		Protocol = 15,
		Empty = 16,
		Schema = 17,
		TooBig = 18,
		Constraint = 19,
		MisMatch = 20,
		MisUse = 21,
		NoLFS = 22,
		Auth = 23,
		Format = 24,
		Range = 25,
		NotADB = 26,
		Notice = 27,
		Warning = 28,

		Row = 100,
		Done = 101,

		BusyRecovery = 261,
		LockedSharedCache = 262,
		ReadonlyRecovery = 264,
		IOErrRead = 266,
		CorruptVTab = 267,
		CantOpenNoTempDir = 270,
		ConstraintCheck = 275,
		NoticeRecoverWAL = 283,
		WarningAutoIndex = 284,

		AbortRollback = 516,
		BusySnapshot = 517,
		ReadOnlyCantLock = 520,
		IOErrShortRead =522,
		CantOpenIsDIR = 526,
		ConstraintCommitHook = 531,
		NoticeRecoverRollback = 539,

		ReadonlyRollback = 776,
		IOErrWrite = 778,
		CantOpenFullPath = 782,
		ConstraintForeignKey = 787,

		ReadonlyDBMoved = 1032,
		IOErrFSync = 1034,
		CantOpenConvPath = 1038,
		ConstraintFunction = 1043,

		IOErrDirFSync = 1290,
		ConstraintNotNULL = 1299,

		IOErrTruncate = 1546,
		ConstraintPrimaryKey = 1555,

		IOErrFStat = 1802,
		ConstraintTrigger = 1811,

		IOErrUnlock = 2058,
		ConstraintUnique = 2067,

		IOErrRDLock = 2314,
		ConstraintVTab = 2323,

		IOErrDelete = 2570,
		ConstraintRowId = 2579,

		IOErrBLocked = 2826,

		IOErrNoMem = 3082,

		IOErrAccess = 3338,

		IOErrCheckReservedLock = 3594,

		IOErrLock = 3850,

		IOErrClose = 4106,

		IOErrDirClose = 4362,

		IOErrShmOpen = 4618,

		IOErrShmSize = 4874,

		IOErrShmLock = 5130,

		IOErrShmMap = 5386,

		IOErrSeek = 5642,

		IOErrDeleteNoEnt = 5898,

		IOErrMMap = 6154,

		IOErrGetTempPath = 6410,

		IOErrConvPath = 6666
	};
}
