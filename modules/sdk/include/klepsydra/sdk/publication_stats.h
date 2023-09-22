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

#ifndef PUBLICATION_STATS_SDK_H
#define PUBLICATION_STATS_SDK_H

#include <klepsydra/sdk/function_stats.h>

namespace kpsr {
/*!
 * \brief PublicationStats class.
 *
 * @copyright Klepsydra Technologies 2019-2031.
 *
 * @version   2.1.0
 *
 * @ingroup kpsr-monitoring
 *
 * @details Statistics associated to the performance of the publisher. The measures include the FunctionStats
 * measures plus discarded event and total event object allocations.
 */
struct PublicationStats : public FunctionStats
{
    /*!
     * @brief PublicationStats
     * @param name service name to gather stats for.
     * @param type service name to gather stats for.
     * @param hasContainer track container for additional stats
     */
    PublicationStats(const std::string &name,
                     const std::string &type,
                     const bool hasContainer = true);

    /*!
     * \brief _type
     */
    const std::string _type;

    /*!
     * \brief _totalEventAllocations
     */
    std::atomic_ullong _totalEventAllocations;

    /*!
     * \brief totalDiscardedEvents
     */
    std::atomic_ullong totalDiscardedEvents;
};
} // namespace kpsr

#endif // PUBLICATION_STATS_H
