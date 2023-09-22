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

#include <klepsydra/sdk/subscriber.h>

#include "mock_classes.h"

namespace kpsr {

TEST(SubscriberBaseTest, NominalTest)
{
    MockContainer container;

    EXPECT_CALL(container, attach(::testing::A<SubscriptionStats *>())).Times(0);
    EXPECT_CALL(container, detach(::testing::A<SubscriptionStats *>())).Times(0);

    std::string subName{"testSubscriber"};
    std::string subType{"test"};
    {
        ASSERT_NO_THROW(SubscriberBase subscriber(&container, subName, subType));
    }

    {
        ASSERT_NO_THROW(SubscriberBase subscriber(nullptr, subName, subType));
    }

    {
        SubscriberBase subscriber(nullptr, subName, subType);
        ASSERT_NO_THROW(subscriber.setContainer(&container));
    }
}

} // namespace kpsr
