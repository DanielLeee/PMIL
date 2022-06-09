#pragma once

#include "Common.h"
#ifdef _DEBUG
#pragma comment(lib, "commond.lib")
#else
#pragma comment(lib, "common.lib")
#endif

#define inf (1e100)
#define eps (1e-10)
#define sqr(x) ((x) * (x))
#define sigmoid(x) (1 / (1 + exp(-double(x))))
