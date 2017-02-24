#include "ShmSource.h"

namespace ofx {
namespace piMapper {

ShmSource::ShmSource()
{
    name = "glmixer";
}

ShmSource::~ShmSource()
{

}

void ShmSource::onAppUpdate(ofEventArgs & args)
{
    ofLogNotice("ShmSource") << "Reading shared memory.";
}

void ShmSource::addAppListeners()
{
    ofLogNotice("ShmSource") << "Adding app listeners";
    ofAddListener(ofEvents().update, this,
                   &ShmSource::onAppUpdate, OF_EVENT_ORDER_BEFORE_APP);
}

void ShmSource::removeAppListeners()
{
    ofRemoveListener(ofEvents().update, this,
                     &ShmSource::onAppUpdate, OF_EVENT_ORDER_BEFORE_APP);
}

}}
