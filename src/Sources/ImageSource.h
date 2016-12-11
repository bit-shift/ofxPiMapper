#pragma once

#include <memory>

#include "BaseSource.h"

namespace ofx {
namespace piMapper {

class ImageSource : public BaseSource {

	public:
		ImageSource();
		~ImageSource();
		string & getPath();
		void loadImage(string & filePath);
		void clear();
	
	private:
		std::unique_ptr<ofImage> _image;

};

} // namespace piMapper
} // namespace ofx