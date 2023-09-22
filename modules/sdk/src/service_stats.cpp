#include <klepsydra/sdk/service_stats.h>
#include <klepsydra/sdk/time_utils.h>

namespace kpsr {
ServiceStats::ServiceStats(const std::string &serviceName, const bool hasContainer)
    : FunctionStats(serviceName, hasContainer)
    , _totalRunningTimeMs(0)
    , _running(false)
{}

void ServiceStats::start()
{
    if (!_processingStarted) {
        _totalRunningTimeMs = 0;
        _processingStarted = true;
        this->_processingStartedTimeMs = TimeUtils::getCurrentMillisecondsAsLlu();
    }
}

void ServiceStats::startTimeWatch()
{
    if (!_running) {
        _timetWatchMs = TimeUtils::getCurrentMillisecondsAsLlu();
    }
    _running = true;
}

void ServiceStats::stopTimeWatch()
{
    if (_running) {
        _totalRunningTimeMs += TimeUtils::getCurrentMillisecondsAsLlu() - _timetWatchMs;
    }
    _running = false;
}

long long unsigned int ServiceStats::getTotalRunningTimeMs()
{
    if (_running) {
        return _totalRunningTimeMs + TimeUtils::getCurrentMillisecondsAsLlu() - _timetWatchMs;
    } else {
        return _totalRunningTimeMs;
    }
}
} // namespace kpsr
