cmake_minimum_required(VERSION 3.10)
project(AbyssCraft)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------------
# 1. Dependencias Externas (Librerías del Sistema)
# ------------------------------------------------------------------
# Buscar librerías
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)


# ------------------------------------------------------------------
# 2. Definición de Archivos Fuente
# ------------------------------------------------------------------
# Archivos fuente
set(SOURCES 
    src/main.cpp 
    src/glad.c  # La descarga para glad desde https://glad.dav1d.de/
    src/core/Window.cpp
    src/core/Game.cpp
    src/render/Tessellator.cpp
    src/render/Shader.cpp
    src/core/Camera.cpp
)

# ------------------------------------------------------------------
# 3. Crear el Ejecutable
# ------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${SOURCES})

# ------------------------------------------------------------------
# 4. Configuración de Includes
# ------------------------------------------------------------------
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    /usr/include/glm  # Aseguramos que encuentre GLM si está instalado en el sistema
)

# ------------------------------------------------------------------
# 5. Linkear Librerías
# ------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
    glfw
    ${OPENGL_LIBRARIES}
    ${CMAKE_DL_LIBS} # Necesario para GLAD en Linux (dynamic loading)
)