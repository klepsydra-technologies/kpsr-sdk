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

#include <string>

#include <klepsydra/sdk/service.h>

#include "mock_classes.h"

namespace kpsr {

TEST(ServiceTest, NominalTest)
{
    MockContainer container;
    MockEnvironment environment;

    EXPECT_CALL(container, attach(::testing::A<ServiceStats *>())).Times(1);
    // EXPECT_CALL(container, detach(::testing::A<ServiceStats *>())).Times(1);

    {
        ASSERT_NO_THROW(MockService service(&container, &environment, "test"));
    }

    {
        ASSERT_NO_THROW(MockService service(nullptr, &environment, "test"));
    }
}

TEST(ServiceTest, NominalRunTest)
{
    MockContainer container;
    MockEnvironment environment;

    EXPECT_CALL(container, attach(::testing::A<ServiceStats *>())).Times(1);

    MockService service(&container, &environment, "test");

    EXPECT_FALSE(service.started);
    EXPECT_EQ(service.serviceStats.totalProcessed, 0);

    ASSERT_NO_THROW(service.runOnce());
    EXPECT_FALSE(service.started);
    EXPECT_EQ(service.serviceStats.totalProcessed, 0);

    ASSERT_NO_THROW(service.startup());
    EXPECT_TRUE(service.started);
    ASSERT_NO_THROW(service.startup());
    EXPECT_TRUE(service.started);

    ASSERT_NO_THROW(service.runOnce());
    EXPECT_EQ(service.serviceStats.totalProcessed, 1);
    EXPECT_GT(service.serviceStats.totalProcessingTimeInNanoSecs, 0);

    ASSERT_NO_THROW(service.shutdown());
    EXPECT_FALSE(service.started);
    ASSERT_NO_THROW(service.shutdown());
    EXPECT_FALSE(service.started);
}

TEST(ServiceTest, NoContainerNominalRunTest)
{
    MockEnvironment environment;

    MockService service(nullptr, &environment, "test");

    EXPECT_FALSE(service.started);
    EXPECT_EQ(service.serviceStats.totalProcessed, 0);

    ASSERT_NO_THROW(service.runOnce());
    EXPECT_FALSE(service.started);

    ASSERT_NO_THROW(service.startup());
    EXPECT_TRUE(service.started);
    ASSERT_NO_THROW(service.startup());
    EXPECT_TRUE(service.started);

    ASSERT_NO_THROW(service.runOnce());
    EXPECT_EQ(service.serviceStats.totalProcessed, 1);

    ASSERT_NO_THROW(service.shutdown());
    EXPECT_FALSE(service.started);
    ASSERT_NO_THROW(service.shutdown());
    EXPECT_FALSE(service.started);
    EXPECT_EQ(service.serviceStats.totalProcessingTimeInNanoSecs, 0);
}
} // namespace kpsr
