#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
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

Mesh* object2D::CreateLife(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float size1,
    float size2,
    float size3,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        
        VertexFormat(corner, color), // 0 = B
        VertexFormat(corner + glm::vec3(0, -size1 , 0), color), // 1 = A
        VertexFormat(corner + glm::vec3(-size2 / 2, size2 /2, 0), color), // 2 = C

        VertexFormat(corner + glm::vec3(-size2, size3, 0), color), // 3 = E
        VertexFormat(corner + glm::vec3(-size2, -size3, 0), color), // 4 = G
        VertexFormat(corner + glm::vec3(size2 / 2, size2 / 2, 0), color), // 5 = D
        VertexFormat(corner + glm::vec3(size2, size3, 0), color), // 16
        VertexFormat(corner + glm::vec3(size2, -size3, 0), color), // 17

    };

    Mesh* life = new Mesh(name);
    std::vector<unsigned int> indices = {
        0, 1, 2,
        1, 2, 3,
        1, 3, 4,
        1, 0, 5,
        1, 5, 6,
        1, 6, 7
    };

    life->InitFromData(vertices, indices);
    return life;
}

Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float width,
    glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(0, width, 0), color),
        VertexFormat(corner + glm::vec3(length, width, 0), color)

    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
        1, 3, 2 };

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateHexagon(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float size1,
    float size2,
    float size3,
    glm::vec3 color,
    glm::vec3 color1,
    float tx,
    float ty)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color1), // 0
        VertexFormat(corner + glm::vec3(0, size1/2 , 0), color1), // 1
        VertexFormat(corner + glm::vec3(size2/2, size3 / 2, 0), color1), // 2

        VertexFormat(corner + glm::vec3(size2 / 2, 0, 0), color1), // 3
        VertexFormat(corner + glm::vec3(size2 / 2, -size3 / 2, 0), color1), // 4
        VertexFormat(corner + glm::vec3(0, -size1/2, 0), color1), // 5
        VertexFormat(corner + glm::vec3(-size2 / 2, -size3 / 2, 0), color1), // 6
        VertexFormat(corner + glm::vec3(-size2 / 2, 0, 0), color1), // 7
        VertexFormat(corner + glm::vec3(-size2 / 2,  size3 / 2, 0), color1), // 8

      
        VertexFormat(corner, color), //10
        VertexFormat(corner + glm::vec3(0, size1 , 0), color), // 11
        VertexFormat(corner + glm::vec3(size2, size3, 0), color), // 12
        
        VertexFormat(corner + glm::vec3(size2, 0, 0), color), // 13
        VertexFormat(corner + glm::vec3(size2, -size3, 0), color), // 14
        VertexFormat(corner + glm::vec3(0, -size1, 0), color), // 15
        VertexFormat(corner + glm::vec3(-size2, -size3, 0), color), // 16
        VertexFormat(corner + glm::vec3(-size2, 0, 0), color), // 17
        VertexFormat(corner + glm::vec3(-size2,  size3, 0), color) // 18

        

    };

    Mesh* hex = new Mesh(name);
    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 7,
        0, 7, 8,
        0, 8, 1,

        10, 11, 12,
        10, 12, 13,
        10, 13, 14,
        10, 14, 15,
        10, 15, 16,
        10, 16, 17,
        10, 17, 18,
        10, 18, 11,
       };

    hex->InitFromData(vertices, indices);
    return hex;
}


Mesh* object2D::CreateDiamond(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float width,
    float length1,
    float width1,
    glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color), // 0
        VertexFormat(corner + glm::vec3(length, width, 0), color), // 1
        VertexFormat(corner + glm::vec3(length * 2, 0, 0), color), //2
        VertexFormat(corner + glm::vec3(length , -width, 0), color), //3

        VertexFormat(corner + glm::vec3(length * 2 - width1,  -width1, 0), color), //4
        VertexFormat(corner + glm::vec3(length * 2 - width1, width1, 0), color),  // 5
        VertexFormat(corner + glm::vec3(length * 2 + length1  , -width1, 0), color), // 6
        VertexFormat(corner + glm::vec3(length * 2 + length1, width1, 0), color) // 7

    };

    Mesh* diamond = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
        0, 2, 3,
        4, 5, 6,
        5, 7, 6
       };

    diamond->InitFromData(vertices, indices);
    return diamond;
}


Mesh* object2D::CreateStar(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float size1Star,
    float size2Star,
    float size3star,
    float size4Star,
    float size5Star,
    float size6Star,
    float size7Star,
    glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color), // 0
        VertexFormat(corner + glm::vec3(size1Star, 0 , 0), color), // 1
        VertexFormat(corner + glm::vec3(0, -size2Star, 0), color), // 2


        VertexFormat(corner + glm::vec3(-size1Star, 0, 0), color), // 3
        VertexFormat(corner + glm::vec3(-size1Star/2, size3star, 0), color), // 4
        VertexFormat(corner + glm::vec3(size1Star/2, size3star, 0), color), // 5

        VertexFormat(corner + glm::vec3(0, size7Star , 0), color), // 6
        VertexFormat(corner + glm::vec3(size5Star, size3star, 0), color), // 7
        VertexFormat(corner + glm::vec3(-size5Star, size3star, 0), color), // 8

        VertexFormat(corner + glm::vec3(size6Star, -size4Star, 0), color), // 9
        VertexFormat(corner + glm::vec3(-size6Star, -size4Star, 0), color), // 10
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 1,
        4, 6, 5,
        5, 7, 1,
        8, 4, 3,
        1, 9, 2,
        2, 10, 3
    };

    star->InitFromData(vertices, indices);
    return star;
}
