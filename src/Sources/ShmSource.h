#pragma once

#include <boost/interprocess/managed_shared_memory.hpp>

#include "ofxCvColorImage.h"

#include "BaseSource.h"

namespace ofx {
namespace piMapper {

class ShmSource : public BaseSource {

	public:
        ShmSource();
        ~ShmSource();

        void update();
        void setup();

        void addAppListeners();
        void removeAppListeners();
	private:
        ofxCvColorImage image_;

};

} // namespace piMapper
} // namespace ofx
