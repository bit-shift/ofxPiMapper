#include "DefaultSource.h"

namespace ofx {
namespace piMapper {

DefaultSource::DefaultSource(){
	//cout << "DefaultSource" << endl;
	loadable = true;
	loaded = false;
	type = SourceType::SOURCE_TYPE_IMAGE;

    ofPixels pixels;
	pixels.allocate(500, 500, 1);
	for(int i = 0; i < pixels.size(); i++){
		pixels[i] = 255;
	}
	int squareSize = 10;          // size of each test pattern square
	bool sy = false;
	for(int y = 0; y < pixels.getWidth(); y += squareSize){
		bool sx = false;
		for(int x = 0; x < pixels.getHeight(); x += squareSize){
			for(int yi = 0; yi < squareSize; yi++){
				for(int xi = 0; xi < squareSize; xi++){
					if(sx && sy){
						pixels[(y + yi) * pixels.getWidth() + x + xi] = 255;
					}else if(sx && !sy){
						pixels[(y + yi) * pixels.getWidth() + x + xi] = 0;
					}else if(!sx && sy){
						pixels[(y + yi) * pixels.getWidth() + x + xi] = 0;
					}else{
						pixels[(y + yi) * pixels.getWidth() + x + xi] = 255;
					}
				}
			}
			sx = !sx;
		}
		sy = !sy;
	}

    // load pixels into texture
	_texture.loadData(pixels);
}

DefaultSource::~DefaultSource(){}

void DefaultSource::clear(){
	_image->clear();
	_image.reset(nullptr);
	loaded = false;
}

} // namespace piMapper
} // namespace ofx