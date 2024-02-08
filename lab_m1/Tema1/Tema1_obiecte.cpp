#include "Tema1_obiecte.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* obiect2D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* obiect2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float width,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* obiect2D::CreateRomb(
    const std::string& name,
    glm::vec3 center,
    float rhombusWidth,
    float rhombusHeight,
    float rectangleWidth,
    float rectangleHeight,
    glm::vec3 rhombusColor
) {
    std::vector<VertexFormat> vertices;

    vertices.push_back(VertexFormat(center + glm::vec3(-rhombusWidth / 2, 0.0f, 0.0f), rhombusColor));
    vertices.push_back(VertexFormat(center + glm::vec3(0.0f, rhombusHeight / 2, 0.0f), rhombusColor));
    vertices.push_back(VertexFormat(center + glm::vec3(rhombusWidth / 2, 0.0f, 0.0f), rhombusColor));
    vertices.push_back(VertexFormat(center + glm::vec3(0.0f, -rhombusHeight / 2, 0.0f), rhombusColor));

    glm::vec3 rectCenter = center + glm::vec3(rhombusWidth / 2 , 0.0f, 0.0f);
    vertices.push_back(VertexFormat(rectCenter + glm::vec3(-rectangleWidth / 2, rectangleHeight / 2, 0.0f), rhombusColor));
    vertices.push_back(VertexFormat(rectCenter + glm::vec3(-rectangleWidth / 2, -rectangleHeight / 2, 0.0f), rhombusColor));
    vertices.push_back(VertexFormat(rectCenter + glm::vec3(rectangleWidth / 2, rectangleHeight / 2, 0.0f), rhombusColor));
    vertices.push_back(VertexFormat(rectCenter + glm::vec3(rectangleWidth / 2, -rectangleHeight / 2, 0.0f), rhombusColor));

    Mesh* romb = new Mesh(name);

    std::vector<unsigned int> indices = { 0, 1, 2, 3 };
    indices.push_back(0);
    indices.push_back(2);
    std::vector<unsigned int> rectangleIndices = { 4, 5, 7, 4, 6, 7 };

    indices.insert(indices.end(), rectangleIndices.begin(), rectangleIndices.end());

    romb->InitFromData(vertices, indices);
    return romb;
}

Mesh* obiect2D::CreateHexagon(
    const std::string& name,
    glm::vec3 center,
    float outerRadius,
    float innerRadius,
    glm::vec3 outerColor,
    glm::vec3 innerColor
) {
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
  
    for (int i = 0; i < 6; i++) {
        float angle = glm::radians(60.0f * i);
        glm::vec3 outerPoint = center + glm::vec3(outerRadius * cos(angle), outerRadius * sin(angle), 0.0f);
        vertices.push_back(VertexFormat(outerPoint, outerColor));
    }

    for (int i = 0; i < 6; i++) {
        float angle = glm::radians(60.0f * i);
        glm::vec3 innerPoint = center + glm::vec3(innerRadius * cos(angle), innerRadius * sin(angle), 0.0f);
        vertices.push_back(VertexFormat(innerPoint, innerColor));
    }

    for (int i = 0; i < 6; i++) {
        indices.push_back(i);
        indices.push_back((i + 1) % 6);
        indices.push_back(6); 
    }

    for (int i = 0; i < 6; i++) {
        indices.push_back(i + 6);
        indices.push_back(6 + (i + 1) % 6 );
        indices.push_back(12); 
    }

    vertices.push_back(VertexFormat(center, innerColor));
    vertices.push_back(VertexFormat(center, outerColor));
    
    Mesh* hexagon = new Mesh(name);
    hexagon->InitFromData(vertices, indices);
    return hexagon;
}


Mesh* obiect2D::CreateStar(
    const std::string& name,
    glm::vec3 center,
    float outerRadius,
    float innerRadius,
    glm::vec3 color,
    bool fill
) {
    std::vector<VertexFormat> vertices;

    for (int i = 0; i < 10; i++) {
        float angle = glm::radians(-90.0f) + glm::radians(i * 36.0f);
        float radius = i % 2 == 0 ? outerRadius : innerRadius;

        glm::vec3 point = center + glm::vec3(radius * cos(angle), radius * sin(angle), 0.0f);
        vertices.push_back(VertexFormat(point, color));
    }

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices;

    if (!fill) {
        indices = {
            0, 2, 4,
            6, 8, 0,
            2, 4, 6,
            8, 0, 2
        };
    }
    else {
        indices = {
            0,1,2,
            0,2,3,
            0,3,4,
            0,4,5,
            0,5,6,
            0,6,7,
            0,7,8,
            0,8,9
        };
    }

    star->InitFromData(vertices, indices);
    return star;
}