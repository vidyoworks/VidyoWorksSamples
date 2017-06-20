#include "VidyoClientSwitchUtils.h"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include <vector>

using boost::bad_lexical_cast;

void ConvertFromStringToMap(const char* cstrPara, map<string, string> &parameter)
{
	string strPara(cstrPara);
	parameter.clear();
	vector<string> components;
	boost::split(components, strPara, boost::is_any_of("\n"));
	for (size_t i = 0; i < components.size(); ++i)
	{
		vector<string> componentDesc;
		boost::split(componentDesc, components[i], boost::is_any_of("\t"));
		if (componentDesc.size() < 2)
			continue;
		parameter.insert(std::pair<string, string>(componentDesc[0], componentDesc[1]));

	}
}

const char* VidyoClientSwitchGetPara(map<string, string> &parameter, const string& key, string& value, const string& defValue)
{
	value = defValue;
	try
	{
		auto search = parameter.find(key);
		if (search != parameter.end())
		{
			value = search->second.c_str();
		}
	}
	catch (...)
	{

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
