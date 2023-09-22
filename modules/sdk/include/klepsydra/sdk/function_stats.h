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

#ifndef KPSR_FUNC_STATS_SDK_H
#define KPSR_FUNC_STATS_SDK_H

#include <atomic>
#include <functional>
#include <string>

namespace kpsr {
/*!
 * @brief FunctionStats class.
 *
 * @ingroup kpsr-monitoring
 *
 * @details Statistics associated to the performance of a customer function. It gathers three main messures: number of invocations, total invocation time, starting time.
 * The use of this class is very simple can be split into three parts: construct, attach to container and surround the code block to be messured. This can be seen in the following example:
@code
class MeasuredClass {
public:
   MeasuredClass(Container * container)
      : functionStats("measured_class")
   {
      if (container) {
         container->attach(&functionStats);
      }
   }

   void measuredFunction() {
      functionStats.startProcessMeasure();
      // DO STUFF
      functionStats.stopProcessMeasure();
   }
private:
   FunctionStats functionStats;
}
@endcode
 */
struct FunctionStats
{
    explicit FunctionStats(const std::string &name, const bool hasContainer = true);

    void setMeasurementFunctions(const bool hasContainer);

    /*!
     * @brief name
     */
    const std::string name;

    /*!
     * @brief totalProcessed
     */
    long long unsigned int totalProcessed = 0;

    /*!
     * @brief totalProcessingTimeInNanoSecs
     */
    long long unsigned int totalProcessingTimeInNanoSecs = 0;

    /*!
     * @brief getMillisecondsSinceCreation
     * @return
     */
    long long unsigned int getMillisecondsSinceCreation();

    /*!
     * \brief start
     */
    virtual void start();

    /*!
     * \brief stop
     */
    virtual void stop();

    /*!
     * @brief getMillisecondsSinceStart
     * @return
     */
    long long unsigned int getMillisecondsSinceStart();

    std::function<void(void)> startProcessMeasure;

    std::function<void(void)> stopProcessMeasure;

protected:
    long long unsigned int _creationTimeMs;

    std::atomic_ullong _beforeTimeNs;

    std::atomic_bool _processingStarted;

    std::atomic_ullong _processingStartedTimeMs;
};

} // namespace kpsr

#endif // KPSR_FUNC_STATS_H
