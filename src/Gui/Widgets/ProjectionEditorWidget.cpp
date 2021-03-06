#include "ProjectionEditorWidget.h"

namespace ofx {
namespace piMapper {

ProjectionEditorWidget::ProjectionEditorWidget(){
	surfaceManager = 0;
	bShiftKeyDown = false;
	fSnapDistance = 10.0f;
}

void ProjectionEditorWidget::update(){
	// update surface if one of the joints is being dragged
	for(int i = 0; i < joints.size(); i++){
		if(joints[i]->isDragged() || joints[i]->isSelected()){
			if(surfaceManager->getSelectedSurface() != 0){
				// update vertex to new location
				surfaceManager->getSelectedSurface()->setVertex(i, Vec3(
					joints[i]->position.x,
					joints[i]->position.y,
					0.0f));
			}else{
				// clear joints if there is no surface selected
				// as the remove selected surface in the surface manager
				// is not supposed to access joints here
				joints.clear();
			}
			break;
		}
	}
}

void ProjectionEditorWidget::draw(){
	if(surfaceManager == 0){
		return;
	}
	if(surfaceManager->getSelectedSurface() == 0){
		return;
	}
	if(joints.size() <= 0){
		createJoints();
	}
	drawJoints();
}

void ProjectionEditorWidget::mouseDragged(ofMouseEventArgs & args){
	
	// Pass args to joint mouse events
	for(unsigned int i = 0; i < joints.size(); ++i){
		joints[i]->mouseDragged(args);
	}
	
	Vec2 mousePosition = Vec2(args.x, args.y);

	// Collect all vertices of the projection surfaces
	std::vector<Vec3> allVertices;
	for(int i = 0; i < surfaceManager->size(); i++){
		BaseSurface * surface = surfaceManager->getSurface(i);
		
		if(surface == surfaceManager->getSelectedSurface()){
			continue; // Don't add vertices of the selected surface
		}
		
		for(int j = 0; j < surface->getVertices().size(); j++){
			allVertices.push_back(surface->getVertices()[j]);
		}
	}

	// Snap currently dragged joint to nearest vertex
	for(int i = 0; i < joints.size(); i++){
		if(joints[i]->isDragged()){
			for(int j = 0; j < allVertices.size(); j++){
				Vec2 v(allVertices[j].x, allVertices[j].y);
				float distance = mousePosition.distance(v);
				
				if(distance < fSnapDistance){
					joints[i]->position = v;
					Vec2 clickDistance = joints[i]->position - Vec2(args.x, args.y);
					joints[i]->setClickDistance(clickDistance);
					break;
				}
			}
		}
	}
}

void ProjectionEditorWidget::gotMessage(ofMessage & msg){
	if(msg.message == "surfaceSelected"){
		clearJoints();
		createJoints();
	}
}

void ProjectionEditorWidget::setSurfaceManager(SurfaceManager * newSurfaceManager){
	if(surfaceManager != 0){
		ofRemoveListener(surfaceManager->vertexChangedEvent, this,
			&ProjectionEditorWidget::onVertexChanged);
		ofRemoveListener(surfaceManager->verticesChangedEvent, this,
			&ProjectionEditorWidget::onVerticesChanged);
		ofRemoveListener(surfaceManager->surfaceSelectedEvent, this,
			&ProjectionEditorWidget::onSurfaceSelected);
		ofRemoveListener(surfaceManager->vertexSelectedEvent, this,
			&ProjectionEditorWidget::onVertexSelected);
		ofRemoveListener(surfaceManager->vertexUnselectedEvent, this,
			&ProjectionEditorWidget::onVertexUnselected);
	}
	
	surfaceManager = newSurfaceManager;
	
	ofAddListener(surfaceManager->vertexChangedEvent, this,
		&ProjectionEditorWidget::onVertexChanged);
	ofAddListener(surfaceManager->verticesChangedEvent, this,
		&ProjectionEditorWidget::onVerticesChanged);
	ofAddListener(surfaceManager->surfaceSelectedEvent, this,
		&ProjectionEditorWidget::onSurfaceSelected);
	ofAddListener(surfaceManager->vertexSelectedEvent, this,
		&ProjectionEditorWidget::onVertexSelected);
	ofAddListener(surfaceManager->vertexUnselectedEvent, this,
		&ProjectionEditorWidget::onVertexUnselected);
}

void ProjectionEditorWidget::clearJoints(){
	while(joints.size()){
		delete joints.back();
		joints.pop_back();
	}
}

void ProjectionEditorWidget::createJoints(){
	if(surfaceManager == 0){
		return;
	}
	clearJoints();

	if(surfaceManager->getSelectedSurface() == 0){
		ofLog(OF_LOG_WARNING, "Trying to create joints while no surface selected.");
		return;
	}

	std::vector<Vec3> vertices = surfaceManager->getSelectedSurface()->getVertices();

	for(int i = 0; i < vertices.size(); i++){
		joints.push_back(new CircleJoint());
		joints.back()->position = Vec2(vertices[i].x, vertices[i].y);
	}
}

void ProjectionEditorWidget::updateJoints(){
	if(surfaceManager->getSelectedSurface()){
		std::vector<Vec3> vertices = surfaceManager->getSelectedSurface()->getVertices();
		
		for(int i = 0; i < vertices.size(); i++){
			joints[i]->position = Vec2(vertices[i].x, vertices[i].y);
		}
	}

}

void ProjectionEditorWidget::unselectAllJoints(){
	for(int i = 0; i < joints.size(); i++){
		joints[i]->unselect();
	}
}

void ProjectionEditorWidget::moveSelectedSurface(Vec3 by){
	if(surfaceManager == 0){
		return;
	}
	
	if(surfaceManager->getSelectedSurface() == 0){
		return;
	}
	
	surfaceManager->getSelectedSurface()->moveBy(by);
	updateJoints();
}

void ProjectionEditorWidget::stopDragJoints(){
	for(int i = 0; i < joints.size(); i++){
		joints[i]->stopDrag();
	}
}

void ProjectionEditorWidget::setSnapDistance(float newSnapDistance){
	fSnapDistance = newSnapDistance;
}

CircleJoint * ProjectionEditorWidget::hitTestJoints(Vec2 pos){
	if(surfaceManager->getSelectedSurface() == 0){
		return 0;
	}
	for(int i = 0; i < joints.size(); i++){
		if(joints[i]->hitTest(pos)){
			return joints[i];
		}
	}
	return 0;
}

std::vector<CircleJoint *> * ProjectionEditorWidget::getJoints(){
	return &joints;
}

void ProjectionEditorWidget::onVertexChanged(int & i){
	bool isDragged = getJoints()->at(i)->isDragged();
	createJoints();
	getJoints()->at(i)->select();
	if(isDragged){
		getJoints()->at(i)->startDrag();
	}else{
		getJoints()->at(i)->stopDrag();
	}
}

void ProjectionEditorWidget::onVerticesChanged(std::vector<Vec3> & vertices){
	createJoints();
}

void ProjectionEditorWidget::onSurfaceSelected(int & surfaceIndex){
	createJoints();
}

void ProjectionEditorWidget::onVertexSelected(int & vertexIndex){
	if(getJoints()->size() == 0){
		return;
	}
	
	unselectAllJoints();
	getJoints()->at(vertexIndex)->select();
}

void ProjectionEditorWidget::onVertexUnselected(int & vertexIndex){
	if(getJoints()->size() == 0){
		return;
	}
	
	unselectAllJoints();
}

void ProjectionEditorWidget::drawJoints(){
	for(int i = 0; i < joints.size(); i++){
		joints[i]->draw();
	}
}

} // namespace piMapper
} // namespace ofx
