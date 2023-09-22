#include <chrono>

#include <klepsydra/sdk/time_utils.h>

namespace kpsr {
long TimeUtils::getCurrentMilliseconds()
{
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch());
    return ms.count();
}

long long unsigned int TimeUtils::getCurrentMillisecondsAsLlu()
{
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch());
    return static_cast<long long unsigned int>(ms.count());
}

long TimeUtils::getCurrentNanoseconds()
{
    std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::system_clock::now().time_since_epoch());
    return ns.count();
}

long long unsigned int TimeUtils::getCurrentNanosecondsAsLlu()
{
    std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::system_clock::now().time_since_epoch());
    return static_cast<long long unsigned int>(ns.count());
}
} // namespace kpsr
