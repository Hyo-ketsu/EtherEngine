#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <concepts>
#include <float.h> 
#include <functional>
#include <deque>
#include <limits.h>
#include <list>
#include <math.h>  
#include <memory>
#include <mutex>
#include <optional>
#include <random>
#include <vector>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <algorithm>

#include <Base/Json/nlohmann/json.hpp>
#include <Eigen/Core>

#include <DirectXMath.h>


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


namespace EtherEngine {
    constexpr float ONE_FRAME = 1.f / 60.f;
}
