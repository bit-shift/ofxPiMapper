#pragma once

#include "BaseCmd.h"
#include "GridWarpSurface.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class AddGridColCmd : public BaseUndoCmd {

	public:
		AddGridColCmd(GridWarpSurface * s);
		void exec();
		void undo();

	private:
		vector <ofVec3f> _vertices;
		vector <ofVec2f> _texCoords;
		GridWarpSurface * _surface;

};

} // namespace piMapper
} // namespace ofx

