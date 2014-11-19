#include "precompiled.h"

#include "StringUtil.h"

#include <sstream>
#include <vector>

void explode(std::vector<String> *result, String &src, char delim)
{
	std::istringstream iss(src);

	for (String token; std::getline(iss, token, delim);){
		if (!token.empty()){
			result->push_back(token);
		}
	}
}