#include <klepsydra/sdk/subscriber.h>

namespace kpsr {

SubscriberBase::SubscriberBase(Container *containerIn,
                               const std::string &name,
                               const std::string &type)
    : name(name)
    , type(type)
    , container(containerIn)
{}

void SubscriberBase::setContainer(Container *containerIn)
{
    container = containerIn;
}
} // namespace kpsr
