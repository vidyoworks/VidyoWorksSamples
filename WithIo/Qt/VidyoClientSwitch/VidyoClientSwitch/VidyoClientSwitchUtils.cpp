#include "VidyoClientSwitchUtils.h"
#include <boost/lexical_cast.hpp>

using boost::bad_lexical_cast;


const char* VidyoClientSwitchGetPara(map<string, string> &parameter, const string& key, string& value, const string& defValue)
{
	value = defValue;
	auto search = parameter.find(key);
	if (search != parameter.end())
	{
		value = search->second.c_str();
	}
	return value.c_str();

}

int VidyoClientSwitchGetPara(map<string, string> &parameter, const string& key, int defValue)
{
	int value = defValue;
	auto search = parameter.find(key);
	if (search == parameter.end())
	{
		return value;
	}
	
	try
	{
		value = boost::lexical_cast<int>(search->second);
	}
	catch (const bad_lexical_cast &)
	{

	}
	return value;

}
