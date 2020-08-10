#include <InputHandler.hpp>

InputHandler::InputHandler(GLFWwindow* window, glm::mat4* proj, glm::mat4* view) {
	mProj = proj;
	mView = view;
	mPanDelta = glm::vec2(0.0f, 0.0f);
	mPanning = 0;
	mSelecting = 0;
	// Set Callback functions for input
	glfwSetCursorPosCallback(window, mousePosition);
	glfwSetMouseButtonCallback(window, mousePressed);
	glfwSetScrollCallback(window, mouseScrolled);
	glfwSetKeyCallback(window, keyPressed);
}

void InputHandler::mousePosition(GLFWwindow* window, double xPos, double yPos){
	float width = 1 / ((*mProj)[0][0] / 2);
	float height = 1 / ((*mProj)[1][1] / 2);
	float panx = (*mView)[3][0];
	float pany = (*mView)[3][1];
	float scale = 1 / (*mView)[0][0];

	// Convert raw mouse to pixel space
	/**************************************NEVER CHANGE**************************************/
	mMousePos = glm::vec2(scale * ((xPos - width/2) - panx), -1 * (scale * ((yPos - height/2) + pany)));
	/****************************************************************************************/



	if(mPanning) {

		mPanDelta = {xPos - mPanDelta.x, yPos - mPanDelta.y};

		*mView = glm::translate(glm::mat4(1.0f), glm::vec3(mPanDelta.x,-mPanDelta.y,0.0f)) * (*mView);
	}

	mPanDelta = {xPos, yPos};
}

void InputHandler::mousePressed(GLFWwindow* window, int button, int action, int mods){
	if(action == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			// Start selecting
			break;

		case GLFW_MOUSE_BUTTON_MIDDLE:
			// Start middle click action
			break;

		case GLFW_MOUSE_BUTTON_RIGHT:
			// Start panning
			break;

		}
	}
	else if(action == GLFW_RELEASE) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			// End selecting
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			// End  middle click action
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			// End panning
			break;
		}
	}
}

void InputHandler::mouseScrolled(GLFWwindow * window, double xoffset, double yoffset){
	float scale = 1 / (*mView)[0][0];
	float panx = (*mView)[3][0];
	float pany = (*mView)[3][1];

	glm::vec3 offset (panx + mMousePos.x/scale, pany + mMousePos.y/scale, 0);

	*mView = glm::translate(glm::mat4(1.0f), offset) * glm::scale(glm::mat4(1.0f), glm::vec3( (yoffset == -1 ? 0.9 : 1/0.9 ), (yoffset == -1 ? 0.9 : 1/0.9 ), 0)) * glm::translate(glm::mat4(1.0f),-1.0f * offset) * *mView;
}

void InputHandler::keyPressed(GLFWwindow* window, int key, int scancode, int action, int mods){
	if(action == GLFW_PRESS) {
		switch(key) {
		case GLFW_KEY_ESCAPE: glfwDestroyWindow(window); break; // This should flip a flag so a non-static method in InputHandler can do the actions
		case GLFW_KEY_DELETE: /* Start delete action */ break;
		case GLFW_KEY_MINUS: /* Start minus action */ break;
		case GLFW_KEY_EQUAL: /* Start equal action */ break;
		}
	}
	else if(action == GLFW_RELEASE){
		switch(key) {
			case GLFW_KEY_ESCAPE: /* End escape action */ break;
			case GLFW_KEY_DELETE: /* End delete action */ break;
			case GLFW_KEY_MINUS: /* End minus action */ break;
			case GLFW_KEY_EQUAL: /* End equal action */ break;
		}
	}
}

// Getters and Setters

bool InputHandler::isPanning(){
	return mPanning;
}

void InputHandler::setPanning(bool panning){
	mPanning = panning;
}

bool InputHandler::isSelecting(){
	return mSelecting;
}

void InputHandler::setSelecting(bool selecting){
	mSelecting = selecting;
}

glm::vec4 InputHandler::getSelectedArea(){
	glm::vec4 points;

	// Top left point
	points[0] = (mInitSelectPos.x < mMousePos.x ? mInitSelectPos.x : mMousePos.x);
	points[1] = (mInitSelectPos.y > mMousePos.y ? mInitSelectPos.y : mMousePos.y);

	// Bottom right point
	points[2] = (mInitSelectPos.x > mMousePos.x ? mInitSelectPos.x : mMousePos.x);
	points[3] = (mInitSelectPos.y < mMousePos.y ? mInitSelectPos.y : mMousePos.y);

	return points;
}

glm::vec2 InputHandler::getMousePos(){
	return mMousePos;
}

void InputHandler::setMousePos(glm::vec2 mousePos){
	mMousePos = mousePos;
}

glm::vec2 InputHandler::getInitScenePos(){
	return mInitScenePos;
}

void InputHandler::setInitScenePos(glm::vec2 scenePos){
	mInitScenePos = scenePos;
}

glm::vec2 InputHandler::getInitSelectPos(){
	return mInitSelectPos;
}

void InputHandler::setInitSelectPos(glm::vec2 selectPos){
	mInitSelectPos = selectPos;
}

glm::vec2 InputHandler::getPanDelta(){
	return mPanDelta;
}

void InputHandler::setPanDelta(glm::vec2 panDelta){
	mPanDelta = panDelta;
}

glm::mat4* InputHandler::getView(){
	return mView;
}

glm::mat4* InputHandler::getProj(){
	return mProj;
}
