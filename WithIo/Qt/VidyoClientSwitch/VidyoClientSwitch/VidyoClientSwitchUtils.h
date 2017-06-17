#pragma once

#include <string>
#include <map>
using namespace std;

#define SAFE_STRING_CPY(destination, source, limit){\
	size_t sizeToCopy = (limit > 0) ? (limit - 1) : 0; \
	strncpy(destination, source, sizeToCopy); \
}

const char* VidyoClientSwitchGetPara(map<string, string> &parameter, const string& key, string& value, const string& defValue = "");
int VidyoClientSwitchGetPara(map<string, string> &parameter, const string& key, int defValue = 0);