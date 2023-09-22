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

#ifndef ENVIRONMENT_SDK_H
#define ENVIRONMENT_SDK_H

#include <string>

namespace kpsr {

std::string const DEFAULT_ROOT("");

/**
 * @brief The Environment interface.
 *
 * @copyright Klepsydra Technologies AG 2023-2031.
 *
 * @ingroup kpsr-application
 *
 * @details This class is a facility class that was born to isolate the ROS environment from the application classes so that they can stay agnostic of ROS.
 * There are several implementations including a mock one based on memory maps that can be used for unit testing.
 *
*/

class Environment
{
public:
    virtual ~Environment() {}
    /**
     * @brief getPropertyString
     * @param key
     * @param value
     */
    virtual bool getPropertyString(const std::string &key,
                                   std::string &value,
                                   std::string const &defaultValue = "",
                                   std::string const &rootNode = DEFAULT_ROOT) = 0;

    /**
     * @brief getPropertyInt
     * @param key
     * @param value
     */
    virtual bool getPropertyInt(const std::string &key,
                                int &value,
                                const int defaultValue = 0,
                                std::string const &rootNode = DEFAULT_ROOT) = 0;

    /**
     * @brief getPropertyFloat
     * @param key
     * @param value
     */
    virtual bool getPropertyFloat(const std::string &key,
                                  float &value,
                                  const float defaultValue = 0.0f,
                                  std::string const &rootNode = DEFAULT_ROOT) = 0;

    /**
     * @brief getPropertyBool
     * @param key
     * @param value
     */
    virtual bool getPropertyBool(const std::string &key,
                                 bool &value,
                                 const bool defaultValue = false,
                                 std::string const &rootNode = DEFAULT_ROOT) = 0;

    /**
     * @brief setPropertyString
     * @param key
     * @param value
     */
    virtual void setPropertyString(const std::string &key,
                                   const std::string &value,
                                   std::string const &rootNode = DEFAULT_ROOT) = 0;

    /**
     * @brief setPropertyInt
     * @param key
     * @param value
     */
    virtual void setPropertyInt(const std::string &key,
                                const int &value,
                                std::string const &rootNode = DEFAULT_ROOT) = 0;

    /**
     * @brief setPropertyFloat
     * @param key
     * @param value
     */
    virtual void setPropertyFloat(const std::string &key,
                                  const float &value,
                                  std::string const &rootNode = DEFAULT_ROOT) = 0;

    /**
     * @brief setPropertyBool
     * @param key
     * @param value
     */
    virtual void setPropertyBool(const std::string &key,
                                 const bool &value,
                                 std::string const &rootNode = DEFAULT_ROOT) = 0;

    /**
     * @brief loadFile
     * @param fileName
     * @param nodeName
     *
     * This method is used to load additional configuration data from another file. It might be used in cases where
     * additional data may be loaded later, like in kpsr::ConfigurationEnvironment
     */
    virtual bool loadFile(const std::string &fileName, const std::string &nodeName) = 0;
};
} // namespace kpsr
#endif
