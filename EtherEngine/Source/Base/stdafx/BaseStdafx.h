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


// �񕄍������R�[�h�̕ʖ���`
using uchar = unsigned char;
// �񕄍�4Byte�����̕ʖ���`
using usint = unsigned short;
// �񕄍������̕ʖ���`
using uint = unsigned int;
// ����8Byte�����̕ʖ���`
using llint = long long;
// �񕄍�8Byte�����̕ʖ���`
using ullint = unsigned long long;


namespace EtherEngine {
    constexpr float ONE_FRAME = 1.f / 60.f;
}
