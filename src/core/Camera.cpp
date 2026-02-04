#include "core/Camera.h"

namespace AbyssCore{
    
    Camera::Camera(glm::vec3 position)
    : c_Position(position),
        c_Front(glm::vec3(0.0f,0.0f,-1.0f)),
        c_WorldUp(glm::vec3(0.0f,1.0f,0.0f))
    {
        updateCameraVectors();
    }

    glm::mat4 Camera::GetViewMatrix(){
        return glm::lookAt(c_Position, c_Position + c_Front, c_Up);
    }

    /**
     * @brief Procesa la entrada del teclado para mover la posición de la cámara.
     * 
     * Calcula el desplazamiento basado en la dirección solicitada, la velocidad configurada y el tiempo transcurrido.
     * 
     * @param direction Enumeración que indica hacia dónde se debe mover la cámara (FORWARD, BACKWARD, etc.).
     * @param deltaTime Tiempo transcurrido entre frames para garantizar un movimiento fluido e independiente de los FPS. No debe ser negativo.
     * @return void
     * @note El movimiento vertical (UP/DOWN) permite vuelo libre utilizando el vector 'Up' de la cámara.
     */
    void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime){
        float velocity = c_Speed * deltaTime;
        if (direction == FORWARD)  c_Position += c_Front * velocity;
        if (direction == BACKWARD) c_Position -= c_Front * velocity;
        if (direction == LEFT)     c_Position -= c_Right * velocity;
        if (direction == RIGHT)    c_Position += c_Right * velocity;
        if (direction == UP)       c_Position += c_Up * velocity; // Vuelo libre
        if (direction == DOWN)     c_Position -= c_Up * velocity;
    }

    /**
     * @brief Procesa el movimiento del ratón para rotar la cámara.
     * 
     * Calcula los nuevos valores de Yaw (guiñada) y Pitch (cabeceo) basándose en el desplazamiento del ratón.
     * 
     * @param xoffset Desplazamiento horizontal del ratón.
     * @param yoffset Desplazamiento vertical del ratón.
     * @param constrainPitch Si es true, limita el cabeceo para evitar que la cámara se invierta (máximo 89 grados).
     * @return void
     * @note Es necesario llamar a esta función en cada evento de movimiento del ratón para mantener la fluidez.
     */
    void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
        xoffset *= c_Sensitivity;
        yoffset *= c_Sensitivity;

        c_Yaw += xoffset;
        c_Pitch += yoffset;

        if (constrainPitch) {
            if (c_Pitch > 89.0f)  c_Pitch = 89.0f;
            if (c_Pitch < -89.0f) c_Pitch = -89.0f;
        }
        updateCameraVectors();
    }


    /**
     * @brief Recalcula los vectores directores de la cámara basándose en los ángulos de Euler.
     * 
     * Actualiza los vectores Front, Right y Up utilizando trigonometría a partir de los valores actuales de Yaw y Pitch.
     * 
     * @return void
     * @note Esta función debe llamarse internamente cada vez que se modifique la rotación de la cámara para mantener la coherencia en el renderizado.
     */
    void Camera::updateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(c_Yaw)) * cos(glm::radians(c_Pitch));
        front.y = sin(glm::radians(c_Pitch));
        front.z = sin(glm::radians(c_Yaw)) * cos(glm::radians(c_Pitch));
        c_Front = glm::normalize(front);
        c_Right = glm::normalize(glm::cross(c_Front, c_WorldUp));
        c_Up    = glm::normalize(glm::cross(c_Right, c_Front));
    }
}