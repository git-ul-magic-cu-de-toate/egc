#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateLife(const std::string& name, glm::vec3 leftBottomCorner, float size1, float size2, float size3, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color);
    Mesh* CreateHexagon(const std::string& name, glm::vec3 leftBottomCorner, float size1, float size2, float size3, glm::vec3 color, glm::vec3 color1, float tx, float ty);
    Mesh* CreateDiamond(const std::string& name, glm::vec3 leftBottomCorner, float length, float width, float length1, float width1, glm::vec3 color);
    Mesh* CreateStar(const std::string& name,glm::vec3 leftBottomCorner, float size1Star, float size2Star, float size3star, float size4Star,
        float size5Star, float size6Star, float size7Star, glm::vec3 color);
}

