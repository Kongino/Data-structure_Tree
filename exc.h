#pragma once

#include <string>
using namespace std;
class NonexistentElement
{
private:
	string errMsg;
public:
	NonexistentElement(const string & err)
	{
		errMsg = err;
	}
};