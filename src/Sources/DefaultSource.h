#pragma once

#include "ofMain.h"
#include "BaseSource.h"
#include "SourceType.h"

namespace ofx {
namespace piMapper {

class DefaultSource : public BaseSource {

	public:
		DefaultSource();
		~DefaultSource();

		void clear();

	private:
		ofTexture _texture;

};

} // namespace piMapper
} // namespace ofx
