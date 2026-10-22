#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{
    Mesh* CreateSquare(const std::string& name, 
        glm::vec3 leftBottomCorner, 
        float length, 
        glm::vec3 color, 
        bool fill);
  
    Mesh* CreateRectangle(
        const std::string& name, 
        glm::vec3 leftBottomCorner, 
        float length, 
        float width, 
        glm::vec3 color, 
        bool fill);
  
    Mesh* CreateStar(
        const std::string& name,
        glm::vec3 leftBottomCorner,
        float size,
        glm::vec3 color,
        bool fill);

    Mesh* CreateRomb(
        const std::string& name,
        glm::vec3 leftBottomCorner,
        float size,
        glm::vec3 color,
        bool fill);

    Mesh* CreateEnemy(
        const std::string& name,
        glm::vec3 leftBottomCorner,
        float size,
        glm::vec3 color1,
        glm::vec3 color2,
        bool fill);

    Mesh* CreateLife(
        const std::string& name,
        glm::vec3 leftBottomCorner,
        float length,
        glm::vec3 color,
        bool fill);
}