/*
 * Copyright 2023 Klepsydra Technologies AG
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <klepsydra/sdk/function_stats.h>
#include <klepsydra/sdk/time_utils.h>

namespace kpsr {

FunctionStats::FunctionStats(const std::string &name, const bool hasContainer)
    : name(name)
    , _creationTimeMs(TimeUtils::getCurrentMillisecondsAsLlu())
    , _processingStarted(false)
{
    setMeasurementFunctions(hasContainer);
}

void FunctionStats::setMeasurementFunctions(const bool hasContainer)
{
    if (hasContainer) {
        startProcessMeasure = [this]() { _beforeTimeNs = TimeUtils::getCurrentNanosecondsAsLlu(); };
        stopProcessMeasure = [this]() {
            totalProcessingTimeInNanoSecs += TimeUtils::getCurrentNanosecondsAsLlu() -
                                             _beforeTimeNs;
            totalProcessed++;
        };
    } else {
        startProcessMeasure = []() {};
        stopProcessMeasure = [this]() { totalProcessed++; };
    }
}

long long unsigned int FunctionStats::getMillisecondsSinceCreation()
{
    return TimeUtils::getCurrentMillisecondsAsLlu() - _creationTimeMs;
}

void FunctionStats::start()
{
    if (!_processingStarted) {
        _processingStartedTimeMs = TimeUtils::getCurrentMillisecondsAsLlu();
        _processingStarted = true;
    }
}

void FunctionStats::stop()
{
    if (_processingStarted) {
        _processingStarted = false;
    }
}

/*!
     * @brief getMillisecondsSinceStart
     * @return
     */
long long unsigned int FunctionStats::getMillisecondsSinceStart()
{
    if (_processingStartedTimeMs != 0) {
        return TimeUtils::getCurrentMillisecondsAsLlu() - _processingStartedTimeMs;
    }
    return 0;
}

} // namespace kpsr
