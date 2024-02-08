#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace obiect2D
{
    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length,float width, glm::vec3 color, bool fill = false);
    Mesh* CreateRomb(const std::string& name,glm::vec3 center,float rhombusWidth,float rhombusHeight, float rectangleWidth, float rectangleHeight,glm::vec3 rhombusColor);
    Mesh* CreateHexagon(const std::string& name, glm::vec3 leftBottomCorner, float outerRadius,float innerRadius, glm::vec3 outerColor, glm::vec3 innerColor);
    Mesh* CreateStar(const std::string& name,glm::vec3 center,float outerRadius,float innerRadius,glm::vec3 color,bool fill = false);
}
