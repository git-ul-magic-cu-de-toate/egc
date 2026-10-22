#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
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

Mesh* object2D::CreateRectangle(
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
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, width, 0), color),
        VertexFormat(corner + glm::vec3(0, width, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateRomb(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float size,
    glm::vec3 color,
    bool fill)
{

    Mesh* romb = new Mesh(name);
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0 * size, 0 * size, 2) , color), //CENTRU
        VertexFormat(corner + glm::vec3(0 * size, 0.5f * size, 2) , color), //A
        VertexFormat(corner + glm::vec3(0.2f * size, 0.1f * size ,2) , color),  //D
        VertexFormat(corner + glm::vec3(0.6f * size, 0.1f * size, 2) , color),  //F
        VertexFormat(corner + glm::vec3(0.6f * size, -0.1f * size, 2) , color),  //G
        VertexFormat(corner + glm::vec3(0.2f * size, -0.1f * size, 2) , color),  //E
        VertexFormat(corner + glm::vec3(0 * size, -0.5f * size, 2) , color),  //C
        VertexFormat(corner + glm::vec3(-0.3f * size, 0 * size, 2) , color),  //B
    };

    std::vector<unsigned int> indices = { 
        0, 1, 2, 
        0, 2, 3, 
        0, 3, 4, 
        0, 4, 5, 
        0, 5, 6, 
        0, 6, 7, 
        0, 7, 1 };


    if (!fill) {
        romb->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    romb->InitFromData(vertices, indices);

    return romb;
}

Mesh* object2D::CreateStar(
     const std::string& name,
     glm::vec3 leftBottomCorner,
     float size,
     glm::vec3 color,
     bool fill)
    {
      Mesh* star = new Mesh(name);
        glm::vec3 corner = leftBottomCorner;

        std::vector<VertexFormat> vertices =
        {    
            VertexFormat(corner + glm::vec3(0 * size, 0 * size, 1) , color),
            VertexFormat(corner + glm::vec3(-0.6f * size, 0.2f * size, 1) , color), //0
            VertexFormat(corner + glm::vec3(0.13f * size, 0.2f * size ,1) , color),  //1
            VertexFormat(corner + glm::vec3(0.4f * size, -0.4f * size, 1) , color),  //2
            VertexFormat(corner + glm::vec3(-0.13f * size, 0.2f * size, 1) , color),  //3
            VertexFormat(corner + glm::vec3(0.6f * size, 0.2f * size, 1) , color),  //4
            VertexFormat(corner + glm::vec3(-0.4f * size, -0.4f * size, 1) , color),  //5
            VertexFormat(corner + glm::vec3(0 * size, 0.5f * size, 1) , color),  //6
            VertexFormat(corner + glm::vec3(0.24f * size, 0.04 * size, 1), color), //7
        };

        std::vector<unsigned int> indices = {
            0, 1, 2,
            0, 2, 3,
            0, 3, 4,
            0, 4, 5,
            0, 5, 6,
            0, 6, 7,
            0, 7, 8,
            0, 8, 1,
        };

        if (!fill) {
            star->SetDrawMode(GL_LINE_LOOP);
        }
        else {
            indices.push_back(0);
            indices.push_back(2);
        }

        star->InitFromData(vertices, indices);

        return star;  
    } 

Mesh* object2D::CreateEnemy(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float size,
    glm::vec3 color1,
    glm::vec3 color2,
    bool fill)
    {
        Mesh* enemy = new Mesh(name);
        glm::vec3 corner = leftBottomCorner;

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner + glm::vec3(0 * size, 0 * size, 2) , color1), //centru hexagon mare
            VertexFormat(corner + glm::vec3(-0.4f * size, 0.6f * size, 2) , color1), //A
            VertexFormat(corner + glm::vec3(0.4f * size, 0.6f * size ,2) , color1),  //B
            VertexFormat(corner + glm::vec3(0.8f * size, 0 * size, 2) , color1),  //D
            VertexFormat(corner + glm::vec3(0.4f * size, -0.6f * size, 2) , color1),  //F
            VertexFormat(corner + glm::vec3(-0.4f * size, -0.6f * size, 2) , color1),  //E
            VertexFormat(corner + glm::vec3(-0.8f * size, 0 * size, 2) , color1),  //C

            VertexFormat(corner + glm::vec3(0 * size, 0 * size, 4) , color2), //centru hexagon mic
            VertexFormat(corner + glm::vec3(-0.2f * size, 0.3f * size, 4) , color2),  //G
            VertexFormat(corner + glm::vec3(0.2f * size, 0.3f * size, 4), color2), //H
            VertexFormat(corner + glm::vec3(0.4f * size, 0 * size, 4) , color2),  //L
            VertexFormat(corner + glm::vec3(0.2f * size, -0.3f * size, 4), color2), //K
            VertexFormat(corner + glm::vec3(-0.2f * size, -0.3f * size, 4) , color2),  //J
            VertexFormat(corner + glm::vec3(-0.4f * size, 0 * size, 4), color2), //I
        };

        std::vector<unsigned int> indices = {
            // Hexagonul mare
            0, 1, 6,
            1, 2, 6,
            2, 3, 6,
            3, 4, 6,
            4, 5, 6,
            5, 0, 6,

            // Hexagonul mic
            7, 8, 13,
            8, 9, 13,
            9, 10, 13,
            10, 11, 13,
            11, 12, 13,
            12, 7, 13,
        };

        if (!fill) {
            enemy->SetDrawMode(GL_LINE_LOOP);
        }
        else {
            indices.push_back(0);
            indices.push_back(6);
            indices.push_back(7);
            indices.push_back(13);
        }

        enemy->InitFromData(vertices, indices);

        return enemy;
    }    
   
Mesh* object2D::CreateLife(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color), // 0
        VertexFormat(corner + glm::vec3(-1 * length, 1 * length, 1), color), // 1
        VertexFormat(corner + glm::vec3(-1 * length, -1 * length, 1), color), // 2
        VertexFormat(corner + glm::vec3(1 * length, -1 * length, 1), color), // 3
        VertexFormat(corner + glm::vec3(1 * length, 1 * length, 1), color) //4
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 
        0, 1, 2, 
        0, 2, 3, 
        0, 3, 4, 
        0, 4, 1 
    };

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