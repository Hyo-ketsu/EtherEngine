#ifndef I_BASEINCLUDE_H
#define I_BASEINCLUDE_H


#include <algorithm>
#include <array>
#include <atomic>
#include <condition_variable>
#include <concepts>
#include <deque>
#include <float.h> 
#include <fstream>
#include <functional>
#include <limits.h>
#include <list>
#include <cmath>
#include <memory>
#include <optional>
#include <random>
#include <vector>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <source_location>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <variant>

#include <Eigen/Core>
#include <DirectXMath.h>
#include <Windows.h>
#include <windows.h>
#pragma comment (lib, "winmm.lib")
#include <Base/Json/nlohmann/json.hpp>
#include <Base/Xml/tinyxml2.h>


// 非符号文字コードの別名定義
using uchar = unsigned char;
// 非符号4Byte整数の別名定義
using usint = unsigned short;
// 非符号整数の別名定義
using uint = unsigned int;
// 符号8Byte整数の別名定義
using llint = long long;
// 非符号8Byte整数の別名定義
using ullint = unsigned long long;


#endif // !I_BASEINCLUDE_H
