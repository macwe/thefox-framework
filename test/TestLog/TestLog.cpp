// TestLog.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <log/log.h>

int _tmain(int argc, _TCHAR* argv[])
{
	thefox::initLog("ffffff");

	LOG_TRACE <<"dddddddd" << "dfdfd";
	LOG_DEBUG << "dfdf" << 12 << -12.23;
	LOG_INFO << "dfdf";
	LOG_WARN << "dfdf";
	LOG_ERROR << "dfdf";

	return 0;
}
