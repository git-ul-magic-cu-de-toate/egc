#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    cx = corner.x + squareSide / 2;
    cy = corner.y + squareSide / 2;

    boxesRelease.resize(9);
    for (int i = 0; i < boxesRelease.size(); i++)
        boxesRelease[i] = false;

    Mesh* square = object2D::CreateSquare("square", corner, squareSide, glm::vec3(0, 1, 0), true);
    AddMeshToList(square);

    Mesh* life = object2D::CreateLife("life", corner, widthDiamond, lengthMiniRec, widthMiniRec, glm::vec3(1, 0, 0), true);
    AddMeshToList(life);

    Mesh* box = object2D::CreateSquare("box", corner, squareSide, glm::vec3(1, 1, 1), false);
    AddMeshToList(box);

    Mesh* rectangle = object2D::CreateRectangle("rectangle", corner, lenghtRectangle, widthRectangle, glm::vec3(1, 0, 0));
    AddMeshToList(rectangle);

    Mesh* blueHexagon = object2D::CreateHexagon("blueHexagon", corner, size1, size2, size3,  glm::vec3(0, 0, 1), glm::vec3(0, 1, 1), 0, 0);
    AddMeshToList(blueHexagon);

    Mesh* purpleHexagon = object2D::CreateHexagon("purpleHexagon", corner, size1, size2, size3, glm::vec3(2.0f, 0.5f, 1.0f), glm::vec3(0, 1, 1), 0, 0);
    AddMeshToList(purpleHexagon);

    Mesh* orangeHexagon = object2D::CreateHexagon("orangeHexagon", corner, size1, size2, size3, glm::vec3(1, 0.5, 0), glm::vec3(0, 1, 1), 0 ,0);
    AddMeshToList(orangeHexagon);

    Mesh* yellowHexagon = object2D::CreateHexagon("yellowHexagon", corner, size1, size2, size3, glm::vec3(1, 1, 0), glm::vec3(0, 1, 1), 0, 0);
    AddMeshToList(yellowHexagon);

    Mesh* purpleDiamond = object2D::CreateDiamond("purpleDiamond", corner, lengthDiamond, widthDiamond, lengthMiniRec, widthMiniRec, glm::vec3(2.0f, 0.5f ,1.0f));
    AddMeshToList(purpleDiamond);

    Mesh* orangeDiamond = object2D::CreateDiamond("orangeDiamond", corner, lengthDiamond, widthDiamond, lengthMiniRec, widthMiniRec, glm::vec3(1, 0.5, 0));
    AddMeshToList(orangeDiamond);

    Mesh* yellowDiamond = object2D::CreateDiamond("yellowDiamond", corner, lengthDiamond, widthDiamond, lengthMiniRec, widthMiniRec, glm::vec3(1, 1, 0));
    AddMeshToList(yellowDiamond);

    Mesh* blueDiamond = object2D::CreateDiamond("blueDiamond", corner, lengthDiamond, widthDiamond, lengthMiniRec, widthMiniRec, glm::vec3(0, 0, 1));
    AddMeshToList(blueDiamond);

    Mesh* star = object2D::CreateStar("star", corner, size1Star,size2Star, size3star, size4Star, size5Star, size6Star, size7Star,  glm::vec3(0.5, 0.5, 0.5));
    AddMeshToList(star);

    Mesh* random_star = object2D::CreateStar("random_star", corner, size1Star, size2Star, size3star, size4Star, size5Star, size6Star, size7Star, glm::vec3(0, 1, 1));
    AddMeshToList(random_star);

    Mesh* yellowStar = object2D::CreateStar("yellowStar", corner, size1Star, size2Star, size3star, size4Star, size5Star, size6Star, size7Star, glm::vec3(1, 1, 0));
    AddMeshToList(yellowStar);

    Mesh* orangeStar = object2D::CreateStar("orangeStar", corner, size1Star, size2Star, size3star, size4Star, size5Star, size6Star, size7Star, glm::vec3(1, 0.5, 0));
    AddMeshToList(orangeStar);

    Mesh* purpleStar = object2D::CreateStar("purpleStar", corner, size1Star, size2Star, size3star, size4Star, size5Star, size6Star, size7Star, glm::vec3(2.0f, 0.5f, 1.0f));
    AddMeshToList(purpleStar);

    Mesh* blueStar = object2D::CreateStar("blueStar", corner, size1Star, size2Star, size3star, size4Star, size5Star, size6Star, size7Star, glm::vec3(0, 0, 1));
    AddMeshToList(blueStar); 

    boxes.push_back(transform2D::Translate(100, 20));
    boxes.push_back(transform2D::Translate(250, 20));
    boxes.push_back(transform2D::Translate(400, 20));
    boxes.push_back(transform2D::Translate(100, 160));
    boxes.push_back(transform2D::Translate(250, 160));
    boxes.push_back(transform2D::Translate(400, 160));
    boxes.push_back(transform2D::Translate(100, 300));
    boxes.push_back(transform2D::Translate(250, 300));
    boxes.push_back(transform2D::Translate(400, 300));

    lifes.push_back(transform2D::Translate(1050, 650));
    lifes.push_back(transform2D::Translate(950, 650));
    lifes.push_back(transform2D::Translate(850, 650));

    squares.push_back(transform2D::Translate(10, 600));
    squares.push_back(transform2D::Translate(160, 600));
    squares.push_back(transform2D::Translate(310, 600));
    squares.push_back(transform2D::Translate(460, 600)); 
    
}

void Tema1::GenerateStars(float deltaTimeSeconds) {
    int random = rand() + deltaTimeSeconds;
    if (random % 500 < 5 && random % 500 > 3) {
        float x = static_cast<float>(rand() % window->GetResolution().x);
        float y = static_cast<float>(rand() % window->GetResolution().y);
        stars.push_back(glm::vec3(x, y, 0.0f));
    }
}

void Tema1::DrawStars() {
    for (int i = 0; i < stars.size(); ++i) {
         const glm::vec3& star = stars[i];
         glm::mat3 starMatrix = glm::mat3(1);
         starMatrix *= transform2D::Translate(star.x, star.y);
         starMatrix *= transform2D::Scale(0.8f, 0.8f);
         RenderMesh2D(meshes["random_star"], shaders["VertexColor"], starMatrix);
    }
}

void Tema1::GenerateEnemy(float deltaTimeSeconds) {
    timeSinceLastEnemy += deltaTimeSeconds;

    if (timeSinceLastEnemy >= timeBetweenEnemies) {
        int random = rand();
        if (random % 500 < 50 && random % 500 > 40) {
            float x = 1200;

            int randomYIndex = rand() % 3;
            int possibleYValues[] = {70, 210, 350 };
            float y = static_cast<float>(possibleYValues[randomYIndex]);

            char* colorHexagon[] = {"blueHexagon", "orangeHexagon", "yellowHexagon", "purpleHexagon" };
            char* colorNameHex[] = {"blue", "orange", "yellow", "purple" };
            int random = rand() % 4;
            char* randomColor = colorHexagon[random];
            char* colorName = colorNameHex[random];

            float radius = size1 * 2;

            enemy.push_back({ glm::vec3(x, y, 0.0f), randomColor, radius, colorName});
            enemyHealth.push_back(3);
            timeSinceLastEnemy = 0.0f;
        }
    }
}

void Tema1::DrawEnemy(float deltaTimeSeconds) {
    for (int i = 0; i < enemy.size(); ++i) {
        glm::vec3& enem = enemy[i].vec;
        glm::mat3 enemyMatrix = glm::mat3(1);
        enemyMatrix *= transform2D::Translate(enem.x, enem.y);
        enem.x -= deltaTimeSeconds * 100;

        RenderMesh2D(meshes[enemy[i].color], shaders["VertexColor"], enemyMatrix);
    }
}

void Tema1::GenerateProjectile(float deltaTimeSeconds, Projectile projectile) {
    timeSinceLastProjectile += deltaTimeSeconds;
    float intervalBetweenProjectiles = 2.f;

    if (timeSinceLastProjectile >= intervalBetweenProjectiles) {
        projectiles.push_back(projectile);
        timeSinceLastProjectile = 0.0f;
    }
}

void Tema1::DetectCollision() {
    float lineThreshold = 100;

    for (int i = 0; i < enemy.size(); ++i) {
        if (enemy[i].vec.x < lineThreshold) {
            enemy.erase(enemy.begin() + i);
            enemyHealth.erase(enemyHealth.begin() + i);

            lifes.erase(lifes.begin());
            
            if (lifes.size() == 0)
                window->Close();
        }
    }
}

void Tema1::PointStarsAndDiamonds() {
    // orange
    starMatrix = glm::mat3(1);
    starMatrix *= transform2D::Translate(30, 575);
    starMatrix *= transform2D::Scale(0.25f, 0.25f);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);

    // blue
    starMatrix = glm::mat3(1);
    starMatrix *= transform2D::Translate(180, 575);
    starMatrix *= transform2D::Scale(0.25f, 0.25f);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);

    starMatrix = glm::mat3(1);
    starMatrix *= transform2D::Translate(210, 575);
    starMatrix *= transform2D::Scale(0.25f, 0.25f);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);

    // yellow
    starMatrix = glm::mat3(1);
    starMatrix *= transform2D::Translate(330, 575);
    starMatrix *= transform2D::Scale(0.25f, 0.25f);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);

    starMatrix = glm::mat3(1);
    starMatrix *= transform2D::Translate(360, 575);
    starMatrix *= transform2D::Scale(0.25f, 0.25f);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);

    // purple
    starMatrix = glm::mat3(1);
    starMatrix *= transform2D::Translate(470, 575);
    starMatrix *= transform2D::Scale(0.25f, 0.25f);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);

    starMatrix = glm::mat3(1);
    starMatrix *= transform2D::Translate(500, 575);
    starMatrix *= transform2D::Scale(0.25f, 0.25f);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);

    starMatrix = glm::mat3(1);
    starMatrix *= transform2D::Translate(530, 575);
    starMatrix *= transform2D::Scale(0.25f, 0.25f);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);

    diamondMatrix = glm::mat3(1);
    diamondMatrix *= transform2D::Translate(20, 647);
    diamondMatrix *= transform2D::Scale(0.8f, 0.8f);
    RenderMesh2D(meshes["orangeDiamond"], shaders["VertexColor"], diamondMatrix);

    diamondMatrix = glm::mat3(1);
    diamondMatrix *= transform2D::Translate(170, 647);
    diamondMatrix *= transform2D::Scale(0.8f, 0.8f);
    RenderMesh2D(meshes["blueDiamond"], shaders["VertexColor"], diamondMatrix);

    diamondMatrix = glm::mat3(1);
    diamondMatrix *= transform2D::Translate(320, 647);
    diamondMatrix *= transform2D::Scale(0.8f, 0.8f);
    RenderMesh2D(meshes["yellowDiamond"], shaders["VertexColor"], diamondMatrix);

    diamondMatrix = glm::mat3(1);
    diamondMatrix *= transform2D::Translate(470, 647);
    diamondMatrix *= transform2D::Scale(0.8f, 0.8f);
    RenderMesh2D(meshes["purpleDiamond"], shaders["VertexColor"], diamondMatrix);
}

void Tema1::PutInBox() {
    for (int i = 0; i < putInBox.size(); i++) {
        glm::mat3 diamondMatrix = glm::mat3(1);
        float x = putInBox[i].x;
        float y = putInBox[i].y;

        if (putInBox[i].x >= 100 && putInBox[i].x <= 100 + squareSide && putInBox[i].y >= 20 && putInBox[i].y <= 20 + squareSide) {

            x_diamond = 100 + squareSide / 3;
            y_diamond = 20 + squareSide / 2;

        }

        else if (putInBox[i].x >= 250 && putInBox[i].x <= 250 + squareSide && putInBox[i].y >= 20 && putInBox[i].y <= 20 + squareSide) {

            x_diamond = 250 + squareSide / 3;
            y_diamond = 20 + squareSide / 2;

        }

        else if (putInBox[i].x >= 400 && putInBox[i].x <= 400 + squareSide && putInBox[i].y >= 20 && putInBox[i].y <= 20 + squareSide) {

            x_diamond = 400 + squareSide / 3;
            y_diamond = 20 + squareSide / 2;

        }

        else if (putInBox[i].x >= 100 && putInBox[i].x <= 100 + squareSide && putInBox[i].y >= 160 && putInBox[i].y <= 160 + squareSide) {

            x_diamond = 100 + squareSide / 3;
            y_diamond = 160 + squareSide / 2;

        }

        else if (putInBox[i].x >= 250 && putInBox[i].x <= 250 + squareSide && putInBox[i].y >= 160 && putInBox[i].y <= 160 + squareSide) {

            x_diamond = 250 + squareSide / 3;
            y_diamond = 160 + squareSide / 2;

        }

        else  if (putInBox[i].x >= 400 && putInBox[i].x <= 400 + squareSide && putInBox[i].y >= 160 && putInBox[i].y <= 160 + squareSide) {

            x_diamond = 400 + squareSide / 3;
            y_diamond = 160 + squareSide / 2;

        }

        else  if (putInBox[i].x >= 100 && putInBox[i].x <= 100 + squareSide && putInBox[i].y >= 300 && putInBox[i].y <= 300 + squareSide) {

            x_diamond = 100 + squareSide / 3;
            y_diamond = 300 + squareSide / 2;

        }

        else if (putInBox[i].x >= 250 && putInBox[i].x <= 250 + squareSide && putInBox[i].y >= 300 && putInBox[i].y <= 300 + squareSide) {

            x_diamond = 250 + squareSide / 3;
            y_diamond = 300 + squareSide / 2;

        }

        else if (putInBox[i].x >= 400 && putInBox[i].x <= 400 + squareSide && putInBox[i].y >= 300 && putInBox[i].y <= 300 + squareSide) {

            x_diamond = 400 + squareSide / 3;
            y_diamond = 300 + squareSide / 2;

        }
        putInBox[i].x = x_diamond;
        putInBox[i].y = y_diamond;

        diamondMatrix *= transform2D::Translate(x_diamond, y_diamond);
        diamondMatrix *= transform2D::Scale(0.8f, 0.8f);

        RenderMesh2D(meshes[putInBox[i].color], shaders["VertexColor"], diamondMatrix);
    }

}

void Tema1::DrawProjectile(float deltaTimeSeconds)
{
    for (int i = 0; i < projectiles.size(); i++) {
        glm::mat3 projMatrix = glm::mat3(1);
        float& rotationAngle = projectiles[i].rotationAngle;
        projMatrix *= transform2D::Translate(projectiles[i].vec.x, projectiles[i].vec.y);
        projMatrix *= transform2D::Scale(0.8f, 0.8f);
        angularStep = deltaTimeSeconds;
        projMatrix *= transform2D::Rotate(rotationAngle);
        projectiles[i].vec.x += deltaTimeSeconds * 650;
        rotationAngle += deltaTimeSeconds * 6;

        char* newColor = new char[strlen(projectiles[i].color) + strlen("Star") + 1];
        strcpy(newColor, projectiles[i].color);
        strcat(newColor, "Star");
        RenderMesh2D(meshes[newColor], shaders["VertexColor"], projMatrix);

    }
}

void Tema1::DisappearEnemy(float deltaTimeSeconds)
{
    for (int i = 0; i < disappearingEnemy.size(); i++) {
        if (disappearingEnemy[i].isAnimating) {
            DisappearingEnemy& obj = disappearingEnemy[i];
            obj.scaleX -= deltaTimeSeconds * 0.5f;
            obj.scaleY -= deltaTimeSeconds * 0.5f;

            if (obj.scaleX > 0 && obj.scaleY > 0) {
                glm::mat3 deadEnemy = glm::mat3(1);
                deadEnemy *= transform2D::Translate(obj.x, obj.y);
                deadEnemy *= transform2D::Scale(obj.scaleX, obj.scaleY);
                RenderMesh2D(meshes[obj.color], shaders["VertexColor"], deadEnemy);
            }
            else {
                disappearingEnemy[i].isAnimating = false;
                disappearingEnemy.erase(disappearingEnemy.begin() + i);
                --i;
            }
        }
    }
}

void Tema1::DisappearDiamond(float deltaTimeSeconds) {
    for (int i = 0; i < disappearingDiamond.size(); ++i) {
        if (disappearingDiamond[i].isAnimating) {
            DisappearingDiamond& obj = disappearingDiamond[i];
            obj.scaleX -= deltaTimeSeconds * 0.5f;
            obj.scaleY -= deltaTimeSeconds * 0.5f;

            if (obj.scaleX > 0 && obj.scaleY > 0) {
                glm::mat3 deadDiamond = glm::mat3(1);
                deadDiamond *= transform2D::Translate(obj.x, obj.y);
                deadDiamond *= transform2D::Scale(obj.scaleX, obj.scaleY);
                RenderMesh2D(meshes[obj.color], shaders["VertexColor"], deadDiamond);
            }
            else {
                disappearingDiamond[i].isAnimating = false;
                disappearingDiamond.erase(disappearingDiamond.begin() + i);
                --i;
            }
        }
    }
}

void Tema1::CollisionEnemyProjectile() {
    for (int i = 0; i < enemy.size(); i++) {
        for (int j = 0; j < projectiles.size(); j++) {
            float distance = glm::distance(enemy[i].vec, projectiles[j].vec);
            float sum = enemy[i].radius + projectiles[j].radius;
            
            if (strcmp(projectiles[j].color, enemy[i].nameColor) == 0 && distance < sum && projectiles[j].vec.y == enemy[i].vec.y) {
                enemyHealth[i]--;

                if (enemyHealth[i] == 0) {
                    DisappearingEnemy obj;
                    obj.x = enemy[i].vec.x;
                    obj.y = enemy[i].vec.y;
                    obj.scaleX = enemy[i].scaleX;
                    obj.scaleY = enemy[i].scaleY;
                    obj.isAnimating = true;
                    obj.color = enemy[i].color;
                    obj.nameColor = enemy[i].nameColor;
                    disappearingEnemy.push_back(obj);
                    enemy.erase(enemy.begin() + i);
                    enemyHealth.erase(enemyHealth.begin() + i);
                    i--;
                }

                projectiles.erase(projectiles.begin() + j);
                break;
            }
        }

    }

}

void Tema1::CollisionEnemyDiamond(float deltaTimeSeconds) {
    for (int i = 0; i < putInBox.size(); i++) {
        bool eraseElement = false;

        for (int j = 0; j < enemy.size(); j++) {

            float distance = glm::distance(glm::vec2(putInBox[i].x, putInBox[i].y), glm::vec2(enemy[j].vec.x, enemy[j].vec.y));
            float sum = enemy[j].radius + putInBox[i].radius;

            if (strcmp(putInBox[i].nameColor, enemy[j].nameColor) == 0 && putInBox[i].y == enemy[j].vec.y) {
                Projectile proj;
                proj.vec = glm::vec3(putInBox[i].x, putInBox[i].y, 0);
                proj.color = putInBox[i].nameColor;
                proj.rotationAngle = 0;
                proj.radius = size7Star;
                GenerateProjectile(deltaTimeSeconds, proj);
            }

            if (distance < sum && strcmp(putInBox[i].nameColor, enemy[j].nameColor) == 0 && putInBox[i].y == enemy[j].vec.y) {
                eraseElement = true;
                DisappearingDiamond obj;
                obj.x = putInBox[i].x;
                obj.y = putInBox[i].y;
                obj.scaleX = putInBox[i].scaleX;
                obj.scaleY = putInBox[i].scaleY;
                obj.isAnimating = true;
                obj.color = putInBox[i].color;
                obj.nameColor = putInBox[i].nameColor;
                disappearingDiamond.push_back(obj);
                break;
            }
        }

        if (eraseElement) {
            putInBox.erase(putInBox.begin() + i);
            i++;
        }
    }
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
    PointStarsAndDiamonds();
    GenerateStars( deltaTimeSeconds);
    DrawStars();

    GenerateEnemy(deltaTimeSeconds);
    DrawEnemy(deltaTimeSeconds);


    for (int i = 0; i < lifeStars; ++i) {
        glm::mat3 starMatrix = glm::mat3(1);
        starMatrix *= transform2D::Translate(x + i * 55, y);
        starMatrix *= transform2D::Scale(0.5f, 0.5f);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);
    }

    DetectCollision();

    rectangleMatrix = glm::mat3(1);
    rectangleMatrix *= transform2D::Translate(10, 20);
    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], rectangleMatrix);


    if (showDiamondOrange) {
        glm::mat3 diamondMatrix = glm::mat3(1);
        diamondMatrix *= transform2D::Translate(posMouseX, posMouseY);
        diamondMatrix *= transform2D::Scale(0.8f, 0.8f);
        RenderMesh2D(meshes["orangeDiamond"], shaders["VertexColor"], diamondMatrix);

    }

    if (showDiamondBlue) {
        glm::mat3 diamondMatrix = glm::mat3(1);
        diamondMatrix *= transform2D::Translate(posMouseX, posMouseY);
        diamondMatrix *= transform2D::Scale(0.8f, 0.8f);
        RenderMesh2D(meshes["blueDiamond"], shaders["VertexColor"], diamondMatrix);

    }

    if (showDiamondYellow) {
        glm::mat3 diamondMatrix = glm::mat3(1);
        diamondMatrix *= transform2D::Translate(posMouseX, posMouseY);
        diamondMatrix *= transform2D::Scale(0.8f, 0.8f);
        RenderMesh2D(meshes["yellowDiamond"], shaders["VertexColor"], diamondMatrix);

    }

    if (showDiamondPurple) {
        glm::mat3 diamondMatrix = glm::mat3(1);
        diamondMatrix *= transform2D::Translate(posMouseX, posMouseY);
        diamondMatrix *= transform2D::Scale(0.8f, 0.8f);
        RenderMesh2D(meshes["purpleDiamond"], shaders["VertexColor"], diamondMatrix);

    }

    PutInBox();

    CollisionEnemyDiamond(deltaTimeSeconds);

    DisappearDiamond(deltaTimeSeconds);
  
    CollisionEnemyProjectile();

    DisappearEnemy(deltaTimeSeconds);

    DrawProjectile(deltaTimeSeconds);

    // vieti
    for (int i = 0; i < lifes.size(); ++i) {
       RenderMesh2D(meshes["life"], shaders["VertexColor"], lifes[i]);
    }

   // patrate verzi
    for (int i = 0; i < boxes.size(); ++i) {
       RenderMesh2D(meshes["square"], shaders["VertexColor"], boxes[i]);
    }

   // patrate in care se pun romburile
    for (int i = 0; i < squares.size(); ++i) {
       RenderMesh2D(meshes["box"], shaders["VertexColor"], squares[i]);
    }
  
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{   
    posMouseX = static_cast<float>(mouseX);
    posMouseY = static_cast<float>(720 - mouseY);
    // Add mouse move event
}



void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    glm::ivec2 resolution = window->GetResolution();

    // left button
    if (button == 1) {
        int sceneY = 720 - mouseY;

        for (int i = 0; i < stars.size(); ++i) {
            glm::vec3& star = stars[i];
            float distance = glm::distance(glm::vec2(star.x, star.y), glm::vec2(mouseX, sceneY));

            if (distance < size7Star) {
                stars.erase(stars.begin() + i);
                lifeStars++;
                break;
            }
        }
            // 10, 600
           if (mouseX >= 10 && mouseX <= 10 + squareSide &&sceneY >= 600 &&sceneY <= 600 + squareSide) {
                showDiamondOrange = true;
                colorDiamond = "orangeDiamond";
                color = "orange";
                if(lifeStars >= 1)
                    lifeStars--;
                else showDiamondOrange = false;
                
           }

            // 160, 600
            if (mouseX >= 160 && mouseX <= 160 + squareSide && sceneY >= 600 && sceneY <= 600 + squareSide) {
                showDiamondBlue = true;
                colorDiamond = "blueDiamond";
                color = "blue";
                if (lifeStars >= 2)
                    lifeStars -= 2;
                else showDiamondBlue = false;
            }

            // 310, 600
            if (mouseX >= 310 && mouseX <= 310 + squareSide && sceneY >= 600 && sceneY <= 600 + squareSide) {
                showDiamondYellow = true;
                colorDiamond = "yellowDiamond";
                color = "yellow";
                if (lifeStars >= 2)
                    lifeStars -= 2;
                else showDiamondYellow = false;
                
            }
 
            // 460, 600
            if (mouseX >= 460 && mouseX <= 460 + squareSide && sceneY >= 600 && sceneY <= 600 + squareSide) {
                showDiamondPurple = true;
                colorDiamond = "purpleDiamond";
                color = "purple";
                if (lifeStars >= 3)
                    lifeStars -= 3;
                else showDiamondPurple = false;
            }
    }
    else if (button == 2) {
        for (int i = 0; i < boxes.size(); i++) {
            glm::mat3 squareMatrix = boxes[i];
            glm::vec2 position = glm::vec2(squareMatrix[2]);
            float x = position.x;
            float y = position.y;

            if (posMouseX >= x && posMouseX <= x + squareSide && posMouseY >= y && posMouseY <= y + squareSide) {
                boxesRelease[i] = true;

                for (int i = 0; i < putInBox.size(); i++) {
                    if (putInBox[i].x >= x && putInBox[i].x <= x + squareSide && putInBox[i].y >= y && putInBox[i].y <= y + squareSide) {
                        putInBox.erase(putInBox.begin() + i);
                        i++;
                    }

                }
            }
        }
    }
    //right button
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    int sceneY = 720 - mouseY;
    if (button == 1) {
        if (!(showDiamondBlue || showDiamondOrange || showDiamondPurple || showDiamondYellow))
            return;
        showDiamondOrange = false;
        showDiamondBlue = false;
        showDiamondPurple = false;
        showDiamondYellow = false;

        for (int i = 0; i < boxes.size(); i++) {
            glm::mat3 squareMatrix = boxes[i];
            glm::vec2 position = glm::vec2(squareMatrix[2]);
            float x = position.x;
            float y = position.y;

            if (posMouseX >= x && posMouseX <= x + squareSide && posMouseY >= y && posMouseY <= y + squareSide) {
                Diamond diamond;
                diamond.x = posMouseX;
                diamond.y = posMouseY;
                diamond.color = colorDiamond;
                diamond.radius = widthDiamond * 2;
                diamond.scaleX = 1;
                diamond.scaleY = 1;
                diamond.nameColor = color;
                putInBox.push_back(diamond);
               
            }
        }
    }
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
