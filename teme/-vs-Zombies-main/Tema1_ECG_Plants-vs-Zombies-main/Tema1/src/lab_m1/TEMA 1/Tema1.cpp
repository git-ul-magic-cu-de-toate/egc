#include "lab_m1\TEMA 1\Tema1.h"

#include <vector>
#include <iostream>
#include <Core/Engine.h>
#include "lab_m1\TEMA 1\Transform2D.h"
#include "lab_m1\TEMA 1\object2D.h"
#include <random>

using namespace std;
using namespace m1;


Tema1::Tema1()
{

}


Tema1::~Tema1()
{
}

float totalRotation;
float starX;
bool isRPressed = false;
float scale_romb_x = 1.0f;
float scale_romb_y = 1.0f;

bool isHPressed = false;
float scale_hexa_x = 1.0f;
float scale_hexa_y = 1.0f;

int star = 0; //nr de stelute pt coliziune
bool starActive = true;

bool isRombScaling = false; 

std::vector<glm::vec2> starPositions;

float spawnCooldown = 0.0f; // Timpul pana la urmatoarea aparitie a unui inamic
std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(1.0f, 5.0f); // Aparitia inamicilor intre 1 si 5 secunde
std::uniform_int_distribution<int> lineDistribution(0, 2); // Alegerea liniei (0, 1, 2)

void Tema1::Init() {

    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    windowSizeX = resolution.x;
    windowSizeY = resolution.y;

    scaleX = 1;
    scaleY = 1;

    angularStep = 0;

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;
    float rombSide = 60; 

    float centerX = squareSide * 1.5;
    float centerY = squareSide * 1.5;

    float rombX = centerX - rombSide / 2;
    float rombY = centerY - rombSide / 2;

    Mesh* square_greenMesh = object2D::CreateSquare("square_green", corner, squareSide, glm::vec3(0.0f, 1.0f, 0.0f), true);
    AddMeshToList(square_greenMesh);

    Mesh* square_not_fullMesh = object2D::CreateSquare("square_not_full", corner, squareSide, glm::vec3(0.0f, 1.0f, 0.0f), false);
    AddMeshToList(square_not_fullMesh);

    Mesh* square_redMesh = object2D::CreateSquare("square_red", corner, squareSide * 0.7, glm::vec3(1.0f, 0.0f, 0.0f), true);
    AddMeshToList(square_redMesh);

    Mesh* rectangular_redMesh = object2D::CreateRectangle("rectangular_red", corner, squareSide, squareSide * 3.2, glm::vec3(1.0f, 0.0f, 0.0f), true);
    AddMeshToList(rectangular_redMesh);

    for (int i = 0; i < 4; i++) {
        std::string rombName = "romb" + std::to_string(i + 1);
        Mesh* rombMesh = object2D::CreateRomb(rombName, corner, 60.0f, colors[i], true);
        AddMeshToList(rombMesh);
    }

    for (int i = 0; i < 4; i++) {
        std::string enemyName = "enemy" + std::to_string(i + 1);
        Mesh* enemyMesh = object2D::CreateEnemy(enemyName, corner, 50.0f, colors[i], glm::vec3(1.0f, 1.0f, 0.0f), true);
        AddMeshToList(enemyMesh);
    }

    Mesh* starMesh = object2D::CreateStar("star", corner, 25.0f, glm::vec3(1.0f, 1.0f, 0.0f), true);
    AddMeshToList(starMesh);

    Mesh* starMesh_red = object2D::CreateStar("star_red", corner, 25.0f, glm::vec3(0.8f, 0.1f, 0.1f), true);
    AddMeshToList(starMesh_red);

    Mesh* starMesh_mov = object2D::CreateStar("star_mov", corner, 25.0f, glm::vec3(0.5f, 0.3f, 0.8f), true);
    AddMeshToList(starMesh_mov);
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();
    float squareSide = 100;
    float smallSquareSide = 70;
    float spacing = 10;
    float topY = 650 - squareSide;
    float rombSide = 60.0f;

    // SCENA DE JOC
    // Dreptunghiul rosu
    glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 20);
    RenderMesh2D(meshes["rectangular_red"], shaders["VertexColor"], modelMatrix);

    // 9 patratele 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float x = (j + 1) * (squareSide + spacing) + spacing;
            float y = i * (squareSide + spacing) + 20;

            glm::mat3 modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(x, y);
            RenderMesh2D(meshes["square_green"], shaders["VertexColor"], modelMatrix);
        }
    }

    // Desenam rombul pt coliziune stea +  hexagon
    glm::mat3 modelMatrixRomb = glm::mat3(1);
    modelMatrixRomb *= transform2D::Translate(161, 720 - 532);
    RenderMesh2D(meshes["romb" + std::to_string(1)], shaders["VertexColor"], modelMatrixRomb);

    // Desenam rombul pt coliziune romb + hexagon
    modelMatrixRomb *= transform2D::Translate(220, 720 - 620);
    RenderMesh2D(meshes["romb" + std::to_string(2)], shaders["VertexColor"], modelMatrixRomb);

    spawnCooldown -= deltaTimeSeconds;
    if (spawnCooldown <= 0.0f) {
        // Alegem o linie in mod aleatoriu
        int line = lineDistribution(generator); 
        
        // Calculam Y in functie de linia aleasa
        float initialY = (line + 0.5) * (squareSide + spacing) + 20; 
        int colorIndex = rand() % 4;

        // Adaugam inamicul cu culoarea selectata
        enemies.push_back({ glm::vec2(1280, initialY), 100.0f, 1.0f, 1.0f, false, colors[colorIndex], colorIndex }); // Adaugă inamicul
        spawnCooldown = distribution(generator); 
    }

    for (Enemy& enemy : enemies) {
        //Detectie ca un inamic a traversat toata linia 
        enemy.position.x -= enemy.speed * deltaTimeSeconds;

        if (enemy.position.x <= 100 + 60 / 2) {
            enemy.isScaling = true;
        }

        if (enemy.isScaling) {
            enemy.scale_x -= 5.0f * deltaTimeSeconds;
            enemy.scale_y -= 5.0f * deltaTimeSeconds;

            if (enemy.scale_x < 0 && enemy.scale_y < 0) {
                // Elimina inamicul daca a fost scalat complet
                enemy = enemies.back();
                enemies.pop_back();
                continue;
            }
        }

        glm::mat3 modelMatrixEnemy = glm::mat3(1);
        modelMatrixEnemy *= transform2D::Translate(enemy.position.x, enemy.position.y);
        if (enemy.isScaling) {
            modelMatrixEnemy *= transform2D::Scale(enemy.scale_x, enemy.scale_y);
        }
        for (int i = 0; i < 4; i++) {
            RenderMesh2D(meshes["enemy" + std::to_string(enemy.colorindex + 1)], shaders["VertexColor"], modelMatrixEnemy);
        }

        // Detectare coliziune cu steluta
        if (enemy.colorindex == 0 && enemy.position.y == 185) {
            glm::mat3 starModelMatrix = glm::mat3(1);
            starModelMatrix *= transform2D::Translate(197, 720 - 532);
        }

        if (enemy.colorindex == 0 && enemy.position.y == 185) { // steluta se misca pe ox ++ steluta are y = 200
            // Steluta care se invarte
            glm::mat3 starModelMatrix = glm::mat3(1);

            totalRotation += 5 * deltaTimeSeconds;
            starX += 100 * deltaTimeSeconds;
            starModelMatrix *= transform2D::Translate(197 + starX, 720 - 532);
            starModelMatrix *= transform2D::Rotate(totalRotation);
            RenderMesh2D(meshes["star_red"], shaders["VertexColor"], starModelMatrix);

            if (enemy.position.x <= starX + 60 * 4) {
                enemy.scale_x -= 10.0f * deltaTimeSeconds;
                enemy.scale_y -= 10.0f * deltaTimeSeconds;

                if (enemy.scale_x < 0 && enemy.scale_y < 0) {
                    // Elimina inamicul daca a fost scalat complet
                    enemy = enemies.back();
                    enemies.pop_back();
                    continue;
                }
            }
        }
        
        // Detectare coliziune cu rombul
        if (enemy.colorindex == 1 && enemy.position.y == 295) {
            glm::mat3 starModelMatrix = glm::mat3(1);
            starModelMatrix *= transform2D::Translate(295, 720 - 430);
        }
        if (enemy.colorindex == 1 && enemy.position.y == 295) {
            // Steluta care se invarte
            glm::mat3 starModelMatrix = glm::mat3(1);

            totalRotation += 5 * deltaTimeSeconds;
            starX += 100 * deltaTimeSeconds;
            starModelMatrix *= transform2D::Translate(295 + starX, 720 - 430);
            starModelMatrix *= transform2D::Rotate(totalRotation);
            RenderMesh2D(meshes["star_mov"], shaders["VertexColor"], starModelMatrix);

            if (enemy.position.x <= starX + 60 * 5) {
                enemy.scale_x -= 10.0f * deltaTimeSeconds;
                enemy.scale_y -= 10.0f * deltaTimeSeconds;

                if (enemy.scale_x < 0 && enemy.scale_y < 0) {
                    // Elimina inamicul daca a fost scalat complet
                    enemy = enemies.back();
                    enemies.pop_back();
                    continue;
                }
            }
        }
    }

    //Vietile
    float redSquareStartX = 200 + 3 * (squareSide + spacing);

    for (int i = 0; i < 3; i++) {
        float x = redSquareStartX + i * (squareSide + spacing);

        glm::mat3 modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x, topY + spacing);
        RenderMesh2D(meshes["square_red"], shaders["VertexColor"], modelMatrix);
    }

    // Stelute lansatoare
    float starSize = 10;

    for (int i = 0; i < 4; i++) {
        float x = 60 + i * (squareSide + spacing * 2);
        if (i == 0) {
            float starX = x;

            glm::mat3 modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(starX, topY - starSize - spacing);
            RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
        }
        else if (i == 1 || i == 2) {
            for (int j = 0; j < 2; j++) {
                float starX = x + j * (starSize + spacing * 2);

                glm::mat3 modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(starX, topY - starSize - spacing);
                RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
            }
        }
        else if (i == 3) {
            for (int j = 0; j < 3; j++) {
                float starX = x + j * (starSize + spacing * 2);

                glm::mat3 modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(starX, topY - starSize - spacing);
                RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
            }
        }
    }

    // Stelute vieti
    for (int i = 0; i < 5; i++) {
        float starX = redSquareStartX + (i + 3) * (starSize + spacing * 2);

        glm::mat3 modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(starX, topY - starSize - spacing);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    }

    // Lansatoare romb + cele 4 patrate contur
    for (int i = 0; i < 4; i++) {
        float xSquare = 30 + i * (squareSide + spacing * 2.5);
        float xRomb = xSquare + (squareSide * 1.5 - rombSide) / 2;
        float yRomb = topY + spacing + (squareSide * 1.5 - rombSide) / 2;

        // Desenam patratul non-full
        glm::mat3 modelMatrixSquare = glm::mat3(1);
        modelMatrixSquare *= transform2D::Translate(xSquare, topY + spacing);
        RenderMesh2D(meshes["square_not_full"], shaders["VertexColor"], modelMatrixSquare);

        // Desenam rombul
        glm::mat3 modelMatrixRomb = glm::mat3(1);
        modelMatrixRomb *= transform2D::Translate(xRomb, yRomb);
        RenderMesh2D(meshes["romb" + std::to_string(i + 1)], shaders["VertexColor"], modelMatrixRomb);
    }
    
    // Animatie disparitie romb
    if (isRPressed) {
        modelMatrix *= transform2D::Translate(300, 400);
        modelMatrix *= transform2D::Scale(1.0f, 1.0f);

        scale_romb_x -= 0.005f;
        scale_romb_y -= 0.005f;

        if (scale_romb_x > 0 && scale_romb_y > 0) {
            // Desenam rombul
            modelMatrix *= transform2D::Scale(scale_romb_x, scale_romb_y);
            RenderMesh2D(meshes["romb" + std::to_string(1)], shaders["VertexColor"], modelMatrix);
        }
    }
    else
    {
        isRPressed = false;
    }

    //Animatie disparitie inamic
    if (isHPressed) {
        modelMatrix *= transform2D::Translate(400, 400);
        modelMatrix *= transform2D::Scale(1.0f, 1.0f);

        scale_hexa_x -= 0.005f;
        scale_hexa_y -= 0.005f;

        if (scale_hexa_x > 0 && scale_hexa_y > 0) {
            // Desenam hexagonul
            modelMatrix *= transform2D::Scale(scale_hexa_x, scale_hexa_y);
            RenderMesh2D(meshes["enemy"], shaders["VertexColor"], modelMatrix);
        }
    }
    else {

        isHPressed = false;
    }
    
    
    // Animatie aparitie aleatoare stele
    spawnCooldown -= deltaTimeSeconds;
    if (spawnCooldown <= 0.0f) {
        int star_random = rand() % 5;

        float minX = 0.0f;
        float maxX = static_cast<float>(resolution.x);
        float minY = 0.0f;
        float maxY = static_cast<float>(resolution.y);

        for (int i = 0; i < star_random; i++) {
            float randomX = static_cast<float>(std::rand()) / RAND_MAX * (maxX - minX) + minX;
            float randomY = static_cast<float>(std::rand()) / RAND_MAX * (maxY - minY) + minY;

            glm::mat3 modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(randomX, randomY);
            RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
            starPositions.push_back(glm::vec2(randomX, randomY));
        }
        spawnCooldown = distribution(generator);
    }

    // Randarea stelelor existente
    for (const auto& starPos : starPositions) {
        glm::mat3 modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(starPos.x, starPos.y);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}

void Tema1::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_R) {
        isRPressed = true;
    }

    if (key == GLFW_KEY_H) {
        isHPressed = true;
    }
}

void Tema1::OnKeyRelease(int key, int mods)
{

}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{

}
void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}