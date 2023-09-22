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

#ifndef TIME_UTILS_H
#define TIME_UTILS_H

namespace kpsr {
/*!
 * @brief The TimeUtils class
 *
 * @copyright Klepsydra Technologies 2019-2020.
 *
 * @version   2.1.0
 *
 * @ingroup kpsr-monitoring
 *
 */
class TimeUtils
{
public:
    /*!
     * @brief getCurrentMilliseconds
     * @return
     */
    static long getCurrentMilliseconds();
    /*!
     * @brief getCurrentMillisecondsAsLlu
     * @return
     */
    static long long unsigned int getCurrentMillisecondsAsLlu();

    /*!
     * @brief getCurrentNanoseconds
     */
    static long getCurrentNanoseconds();

    /*!
     * @brief getCurrentNanosecondsAsLlu
     * @return
     */
    static long long unsigned int getCurrentNanosecondsAsLlu();
};
} // namespace kpsr

#endif // TIME_UTILS_H
