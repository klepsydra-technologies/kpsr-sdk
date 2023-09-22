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

#ifndef SERVICE_STATS_SDK_H
#define SERVICE_STATS_SDK_H

#include <klepsydra/sdk/function_stats.h>

namespace kpsr {
/*!
 * @brief ServiceStats class.
 *
 * @copyright Klepsydra Technologies 2019-2020.
 *
 * @version   2.1.0
 *
 * @ingroup kpsr-monitoring
 *
 * @details Statistics associated to the performance of the services. The measures include the FunctionStats measures plus the total running time. A service can be dynamically stopped and started during the execution life time of the process.
 */
struct ServiceStats : public FunctionStats
{
public:
    /*!
     * @brief ServiceStats
     * @param serviceName service name to gather stats for.
     */
    explicit ServiceStats(const std::string &serviceName, const bool hasContainer = true);

    /*!
     * \brief start
     */
    void start() override;

    /*!
     * @brief startTimeWatch
     */
    void startTimeWatch();

    /*!
     * @brief stopTimeWatch
     */
    void stopTimeWatch();

    /*!
     * @brief getTotalRunningTimeMs
     * @return
     */
    long long unsigned int getTotalRunningTimeMs();

private:
    std::atomic_ullong _totalRunningTimeMs;

    std::atomic_ullong _timetWatchMs;

    std::atomic_bool _running;
};
} // namespace kpsr

#endif // SERVICE_STATS_H
