//
// Created by Sadeep on 09-Jun.
//

#ifndef RT3_CAMERA_H
#define RT3_CAMERA_H


#include <glm/detail/type_mat4x4.hpp>


class Camera {
public:

    enum Projection{
        orthographic,
        perspective
    };

    Projection projection = orthographic;

    Camera();

    float w = 400, h = 400;         // Display width and height.
    void setWH(float w, float h);


    glm::vec3 eyePosition = glm::vec3(0,-10,-10); // Camera coordinates
    float angleAroundY = 0, angleAroundX = 45; // Camera direction in degrees

    float nearPlane = .01f, farPlane = 2000000.0f;

    float fov=60; // Field of view (angle from Display bottom to top) in degrees

    float zoom=600; // zoom level for orthographic

    float eyeMovementPerWheelAngle = .1f; // move forward/backward when wheel rotate
    float eyeMovementPerMouseMove = .025f; // move right/left and up/down (relative to current rotation) when mouse drag


    glm::mat4 modelViewMatrix() const;
    glm::mat4 projectionMatrix() const;

    void processMouseDrag(int deltaX, int deltaY, bool rotate);

    void processMouseWheel(int deltaWheelAngle);

    const glm::vec3  axisX = glm::vec3(1.0f,0.0f,0.0f);
    const glm::vec3  axisY = glm::vec3(0.0f,1.0f,0.0f);
    const glm::vec3  axisZ = glm::vec3(0.0f,0.0f,1.0f);
};


#endif //RT3_CAMERA_H
