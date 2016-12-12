#include "BaseSource.h"

#include <DefaultSource.h>

namespace ofx {
namespace piMapper {

BaseSource::BaseSource(ofTexture & texture) : _texture(texture){
	init();
}

BaseSource::~BaseSource(){}

ofTexture & BaseSource::getTexture(){
	return _texture;
}

string & BaseSource::getName(){
	return name;
}

bool BaseSource::isLoadable(){
	return loadable;
}

bool BaseSource::isLoaded(){
	return loaded;
}

int BaseSource::getType(){
	return type;
}

string & BaseSource::getPath(){
	return path;
}

void BaseSource::init(){
	name = "";
	path = "";
	loadable = false;
	loaded = false;
	type = SourceType::SOURCE_TYPE_NONE;
	referenceCount = 1;   // We have one instance on init
}

void BaseSource::setNameFromPath(string & fullPath){
	vector <string> pathParts;
	//cout << "fullPath: " << fullPath << endl;
	pathParts = ofSplitString(fullPath, "/");   // Maybe on win "/" is "\", have to test
	//cout << "lastPathPart: " << pathParts[pathParts.size() - 1] << endl;
	name = pathParts[pathParts.size() - 1];
}

} // namespace piMapper
} // namespace ofx