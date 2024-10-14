#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "ICameraObserver.h"
#include "CameraMovementEnum.h"

class Camera {
private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float fieldOfView;
    float zNear;
    float zFar;
    float aspectRatio;

    float horizontalAngle;
    float verticalAngle;

    float movementSpeed;
    float mouseSensitivity;

    std::vector<ICameraObserver*> observers;

    void updateCameraVectors();

public:
    Camera(float aspectRatio);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    void processMouseMovement(float xoffset, float yoffset);
    void processKeyboard(CameraMovement direction, float deltaTime);

    void addObserver(ICameraObserver* observer);
    void removeObserver(ICameraObserver* observer);
    void notifyObservers();

    void setAspectRatio(float aspectRatio);
};
