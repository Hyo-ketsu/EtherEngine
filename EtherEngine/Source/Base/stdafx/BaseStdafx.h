#include <array>
#include <list>
#include <memory>
#include <mutex>
#include <vector>
#include <thread>
#include <memory>
#include <mutex>
#include <functional>
#include <atomic>
#include <condition_variable>
#include <type_traits>
#include <optional>
#include <deque>
#include <chrono>
#include <random>
#include <unordered_map>


#include <Base/IMGUI/imgui.h>
#include <Base/Json/nlohmann/json.hpp>
#include <Eigen/Core>

namespace EtherEngine {
    constexpr float ONE_FRAME = 1.f / 60.f;
}
