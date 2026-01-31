#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace AbyssCore{
    enum CameraMovement {
        FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN
    };

    class Camera{
        public:
            float c_Yaw = -90.0f;
            float c_Pitch = 0.0f;
            float c_Speed = 5.5f;
            float c_Sensitivity = 0.1f;
            float c_Zoom = 45.0f;

            glm::vec3 c_Position;
            glm::vec3 c_Front;
            glm::vec3 c_Up;
            glm::vec3 c_Right;
            glm::vec3 c_WorldUp;

            Camera(glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f));

            glm::mat4 GetViewMatrix();
            void ProcessKeyboard(CameraMovement direction, float deltaTime);

            void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

        private:
            void updateCameraVectors();
    };
    
} // namespace AbyssCore


#endif // CAMERA_H