#include <string>

typedef std::string String;

#define _TO_STRING(value) #value
#define TO_STRING(value) _TO_STRING(value)