#include "lab_m1/Tema2/Tema2.h"
#include "lab_camera.h"

#include <vector>
#include <string>
#include <iostream>


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace m1;


/*
 *  To find out more about FrameStart, Update, FrameEnd
 *  and the order in which they are called, see world.cpp.
 */

struct Tank {
    Mesh* body;
    Mesh* leftTrack;
    Mesh* rightTrack;
    Mesh* barrel;
    Mesh* turret;
    Mesh* projectile;

    glm::vec3 position;
    float rotationAngle;
    float turretRotationAngle;
    float barrelRotation;
    float turretRotation;

    float movementSpeed;
    glm::vec3 movementDirection;
    float changeDirectionTimer;

    float directionChangeTimer;
    glm::vec3 randomDirection;

    float randomMovementDuration; 
    float randomMovementTimer;    
    int randomMovementType;      
    float desiredRotation; 
    float currentRotation; 
};

Tank tank;
Tank tank_inamic;
Tank tank_inamic2;
Tank tank_inamic3;

float shootCooldown = 0.0f;
float mouseSensitivity = 0.1f;

struct Projectile {
    glm::vec3 position;
    glm::vec3 direction;
    float lifetime;
    bool isActive;
};

std::vector<Projectile> projectiles;


struct Building {
    glm::vec3 position;
    glm::vec3 size;
};

std::vector<Building> buildings;

Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}

void Tema2::Init()
{
    {
        Mesh* mesh = new Mesh("tank");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "Tank.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("senila_stanga");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "senila_stanga.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("senila_dreapta");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "senila_dreapta.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("tun");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "tun.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("cap");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "cap.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
   
    {
        Mesh* mesh = new Mesh("cap1");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "cap1.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("corp");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "corp.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("proiectil");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "proiectil.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("cladire");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        tank.body = meshes["corp"];
        tank.leftTrack = meshes["senila_stanga"];
        tank.rightTrack = meshes["senila_dreapta"];
        tank.barrel = meshes["tun"];
        tank.turret = meshes["cap1"];
        tank.projectile = meshes["proiectil"];

        tank.position = glm::vec3(0, 0, 0);
        tank.rotationAngle = 0.0f;
    }

    {
        float randomX = static_cast<float>(rand() % 100) / 10.0f - 5.0f;
        float randomZ = static_cast<float>(rand() % 100) / 10.0f - 5.0f;

        tank_inamic.body = meshes["corp"];
        tank_inamic.leftTrack = meshes["senila_stanga"];
        tank_inamic.rightTrack = meshes["senila_dreapta"];
        tank_inamic.barrel = meshes["tun"];
        tank_inamic.turret = meshes["cap"];
        tank_inamic.projectile = meshes["proiectil"];

        tank_inamic.position = glm::vec3(randomX, 0.0f, randomZ);
        tank_inamic.rotationAngle = 0.0f;
        tank_inamic.movementSpeed = 2.0f;
        tank_inamic.changeDirectionTimer = 0.0f;
        tank_inamic.movementDirection = glm::vec3(rand() % 3 - 1, 0, rand() % 3 - 1);

        tank_inamic.randomMovementDuration = 0.0f;
        tank_inamic.randomMovementTimer = 0.0f;
        tank_inamic.randomMovementType = -1; // nedefinit

        tank_inamic.desiredRotation = rand() % 360;
        tank_inamic.currentRotation = 0.0f;
    }

    {
        float randomX = static_cast<float>(rand() % 100) / 10.0f - 5.0f;
        float randomZ = static_cast<float>(rand() % 100) / 10.0f - 5.0f;

        tank_inamic2.body = meshes["corp"];
        tank_inamic2.leftTrack = meshes["senila_stanga"];
        tank_inamic2.rightTrack = meshes["senila_dreapta"];
        tank_inamic2.barrel = meshes["tun"];
        tank_inamic2.turret = meshes["cap"];
        tank_inamic2.projectile = meshes["proiectil"];

        tank_inamic2.position = glm::vec3(randomX, 0.0f, randomZ);
        tank_inamic2.rotationAngle = 0.0f;
        tank_inamic2.movementSpeed = 0.5f;
        tank_inamic2.changeDirectionTimer = 0.0f;
        tank_inamic2.movementDirection = glm::vec3(rand() % 3 - 1, 0, rand() % 3 - 1);

    }

    {
        tank_inamic3.body = meshes["corp"];
        tank_inamic3.leftTrack = meshes["senila_stanga"];
        tank_inamic3.rightTrack = meshes["senila_dreapta"];
        tank_inamic3.barrel = meshes["tun"];
        tank_inamic3.turret = meshes["cap"];
        tank_inamic3.projectile = meshes["proiectil"];

        tank_inamic3.position = glm::vec3(-10, 0, -10);
        tank_inamic3.rotationAngle = 0.0f;
    }


    for (int i = 0; i < 3; ++i) {
        Building building;
        building.position = glm::vec3(rand() % 50 - 30, 0, rand() % 50 - 30);
        building.size = glm::vec3(1 + rand() % 5, 1 + rand() % 10, 1 + rand() % 5);
        
        buildings.push_back(building);
    }

    // Shader for drawing face polygon with the color of the dark blue
    {
        Shader* shader = new Shader("Shader_dark_blue");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader_dark_blue.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Shader for drawing face polygon with the color of the light blue
    {
        Shader* shader = new Shader("Shader_light_blue");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader_light_blue.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    //Shader for drawing face polygon with the color of the grey
    {
        Shader* shader = new Shader("Shader_grey");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader_grey.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    // Shader for drawing face polygon with the color of the dark green
    {
        Shader* shader = new Shader("Shader_dark_green");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader_dark_green.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Shader for drawing face polygon with the color of the light green
    {
        Shader* shader = new Shader("Shader_light_green");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader_light_green.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

}


Mesh* Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    // Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create the VBO and bind it
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Create the IBO and bind it
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data.

    // TODO(student): If you look closely in the Init() and Update()
    // functions, you will see that we have three objects which we load
    // and use in three different ways:
    // - LoadMesh   + LabShader (this lab's shader)
    // - CreateMesh + VertexNormal (this shader is already implemented)
    // - CreateMesh + LabShader (this lab's shader)
    // To get an idea about how they're different from one another, do the
    // following experiments. What happens if you switch the color pipe and
    // normal pipe in this function (but not in the shader)? Now, what happens
    // if you do the same thing in the shader (but not in this function)?
    // Finally, what happens if you do the same thing in both places? Why?

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    CheckOpenGLError();

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;
    return meshes[name];
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
    glClearColor(0.6, 0.3, 0.3, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gameTime += deltaTimeSeconds;

    if (gameTime >= gameDuration && gameActive) {
        std::cout << "Jocul s-a terminat!" << std::endl;
        gameActive = false; // Oprirea jocului
    }
    
    /*
    // Corpul tancului
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        RenderMesh(meshes["corp"], shaders["Shader_dark_blue"], modelMatrix);
    }

    // Turela tancului
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        RenderMesh(meshes["cap"], shaders["Shader_light_blue"], modelMatrix);
    }

    // Tunul tancului
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        RenderMesh(meshes["tun"], shaders["Shader_dark_blue"], modelMatrix);
    }

    // Șenilele tancului
    {
        // Șenila stângă
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        RenderMesh(meshes["senila_stanga"], shaders["Shader_grey"], modelMatrix);

        // Șenila dreaptă
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        RenderMesh(meshes["senila_dreapta"], shaders["Shader_grey"], modelMatrix);
    }
    */
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, tank.position);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(tank.rotationAngle), glm::vec3(0, 1, 0));

        RenderMesh(tank.body, shaders["Shader_dark_blue"], modelMatrix);
        RenderMesh(tank.leftTrack, shaders["Shader_grey"], modelMatrix);
        RenderMesh(tank.rightTrack, shaders["Shader_grey"], modelMatrix);

        //RenderMesh(tank.barrel, shaders["Shader_grey"], modelMatrix);
        //RenderMesh(tank.turret, shaders["Shader_light_blue"], modelMatrix);

        glm::mat4 turretModelMatrix = glm::mat4(1);
        turretModelMatrix = glm::translate(turretModelMatrix, tank.position);
        turretModelMatrix = glm::rotate(turretModelMatrix, glm::radians(tank.turretRotationAngle), glm::vec3(0, 1, 0));
        RenderMesh(tank.turret, shaders["Shader_light_blue"], turretModelMatrix);


        glm::mat4 barrelModelMatrix = glm::mat4(1);
        barrelModelMatrix = glm::translate(barrelModelMatrix, tank.position); 
        barrelModelMatrix = glm::rotate(barrelModelMatrix, glm::radians(tank.turretRotationAngle), glm::vec3(0, 1, 0));
        RenderMesh(tank.barrel, shaders["Shader_grey"], barrelModelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, tank_inamic.position);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(tank_inamic.rotationAngle), glm::vec3(0, 1, 0));

        glm::vec3 barrelDirection = glm::normalize(glm::vec3(modelMatrix * glm::vec4(0, 0, 1, 0)));
        float rotationSpeed = 2.0f;

        // Actualizează timerul pentru mișcare
        tank_inamic.randomMovementTimer += deltaTimeSeconds;
        if (tank_inamic.randomMovementTimer >= tank_inamic.randomMovementDuration) {
            // Alege o nouă mișcare aleatorie
            tank_inamic.randomMovementType = rand() % 3;
            tank_inamic.randomMovementDuration = static_cast<float>(rand() % 5 + 1);
            tank_inamic.randomMovementTimer = 0.0f;
        }

        // Execută mișcarea aleasă
        if (tank_inamic.randomMovementType == 0) {
            tank_inamic.position += barrelDirection * tank_inamic.movementSpeed * deltaTimeSeconds;
        }
        else if (tank_inamic.randomMovementType == 1) {
            tank_inamic.position -= barrelDirection * tank_inamic.movementSpeed * deltaTimeSeconds;
        }
        else if (tank_inamic.randomMovementType == 2) {
                if (tank_inamic.currentRotation < tank_inamic.desiredRotation) {
                    float rotationStep = rotationSpeed * deltaTimeSeconds;
                    tank_inamic.rotationAngle += rotationStep;
                    tank_inamic.currentRotation += rotationStep;
                }
                else {
                    // Resetare dupa rotatie
                    tank_inamic.currentRotation = 0.0f;
                    tank_inamic.randomMovementType = -1;
                }
        }

        RenderMesh(tank_inamic.body, shaders["Shader_dark_green"], modelMatrix);
        RenderMesh(tank_inamic.leftTrack, shaders["Shader_grey"], modelMatrix);
        RenderMesh(tank_inamic.rightTrack, shaders["Shader_grey"], modelMatrix);
        RenderMesh(tank_inamic.barrel, shaders["Shader_grey"], modelMatrix);
        RenderMesh(tank_inamic.turret, shaders["Shader_light_green"], modelMatrix);
    }


    {
        float angleIncrement = tank_inamic2.movementSpeed * deltaTimeSeconds; 
        tank_inamic2.rotationAngle += angleIncrement; 

        float newX = 20.0f * sin(tank_inamic2.rotationAngle);
        float newZ = -20.0f * cos(tank_inamic2.rotationAngle);
        tank_inamic2.position = glm::vec3(newX, 0, newZ);
        
        float tangentAngle = tank_inamic2.rotationAngle + glm::half_pi<float>() + glm::pi<float>();
        tank_inamic2.turretRotationAngle = tangentAngle;

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, tank_inamic2.position);
        //modelMatrix = glm::rotate(modelMatrix, glm::radians(tank_inamic2.rotationAngle), glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(tank_inamic2.turretRotationAngle), glm::vec3(0, 1, 0));
       
        RenderMesh(tank_inamic2.body, shaders["Shader_dark_green"], modelMatrix);
        RenderMesh(tank_inamic2.leftTrack, shaders["Shader_grey"], modelMatrix);
        RenderMesh(tank_inamic2.rightTrack, shaders["Shader_grey"], modelMatrix);
        RenderMesh(tank_inamic2.barrel, shaders["Shader_grey"], modelMatrix);
        RenderMesh(tank_inamic2.turret, shaders["Shader_light_green"], modelMatrix);
    }

    {
        float angleIncrement = tank_inamic2.movementSpeed * deltaTimeSeconds;
        tank_inamic2.rotationAngle += angleIncrement;

        float newX = 20.0f * sin(tank_inamic2.rotationAngle);
        float newZ = -20.0f * cos(tank_inamic2.rotationAngle);
        tank_inamic2.position = glm::vec3(newX, 0, newZ);

        float tangentAngle = tank_inamic2.rotationAngle + glm::half_pi<float>() + glm::pi<float>();
        tank_inamic2.turretRotationAngle = tangentAngle;

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, tank_inamic2.position);
        //modelMatrix = glm::rotate(modelMatrix, glm::radians(tank_inamic2.rotationAngle), glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(tank_inamic2.turretRotationAngle), glm::vec3(0, 1, 0));

        RenderMesh(tank_inamic2.body, shaders["Shader_dark_green"], modelMatrix);
        RenderMesh(tank_inamic2.leftTrack, shaders["Shader_grey"], modelMatrix);
        RenderMesh(tank_inamic2.rightTrack, shaders["Shader_grey"], modelMatrix);
        RenderMesh(tank_inamic2.barrel, shaders["Shader_grey"], modelMatrix);
        RenderMesh(tank_inamic2.turret, shaders["Shader_ligeht_green"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, tank_inamic3.position);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(tank_inamic3.rotationAngle), glm::vec3(0, 1, 0));

        RenderMesh(tank_inamic3.body, shaders["Shader_dark_green"], modelMatrix);
        RenderMesh(tank_inamic3.leftTrack, shaders["Shader_grey"], modelMatrix);
        RenderMesh(tank_inamic3.rightTrack, shaders["Shader_grey"], modelMatrix);
        RenderMesh(tank_inamic3.barrel, shaders["Shader_grey"], modelMatrix);
        RenderMesh(tank_inamic3.turret, shaders["Shader_light_green"], modelMatrix);

    }

    if (shootCooldown > 0) {
        shootCooldown -= deltaTimeSeconds;
    }

    float projectileSpeed = 10.0f;

    for (auto& projectile : projectiles) {
        if (projectile.isActive) {
            projectile.position += projectile.direction * projectileSpeed * deltaTimeSeconds;
            projectile.lifetime -= deltaTimeSeconds;

            if (projectile.lifetime <= 0) {
                projectile.isActive = false;
            }
            else {
                // Randare proiectil nou
                glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), projectile.position);
                RenderMesh(tank.projectile, shaders["Shader_dark_blue"], modelMatrix);
            }

        }
    }

    // Eliminare proiectile inactive
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](const Projectile& p) { return !p.isActive; }), projectiles.end());
    
    
    for (const auto& building : buildings) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, building.position);
        modelMatrix = glm::scale(modelMatrix, building.size);
        RenderMesh(meshes["cladire"], shaders["VertexNormal"], modelMatrix);
    }
}


void Tema2::FrameEnd()
{
    DrawCoordinateSystem();
}


void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // TODO(student): Get shader location for uniform mat4 "Model"
    int location = glGetUniformLocation(shader->GetProgramID(), "Model");

    // TODO(student): Set shader uniform "Model" to modelMatrix
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // TODO(student): Get shader location for uniform mat4 "View"
    int viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");

    // TODO(student): Set shader uniform "View" to viewMatrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // TODO(student): Get shader location for uniform mat4 "Projection"
    int projLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");

    // TODO(student): Set shader uniform "Projection" to projectionMatrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see input_controller.h.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    if (gameActive && !window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        const float movementSpeed = 5.0f;
        const float rotationSpeed = 25.0f;

        // Calculate rotation matrix
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(tank.rotationAngle), glm::vec3(0, 1, 0));

        // Compute forward and right directions based on the tank's current rotation
        glm::vec3 forwardDir = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(0, 0, 1, 0)));
        glm::vec3 rightDir = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(1, 0, 0, 0)));

        if (window->KeyHold(GLFW_KEY_W)) {
            // Move forward
            tank.position -= forwardDir * movementSpeed * deltaTime;
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            // Move backward
            tank.position += forwardDir * movementSpeed * deltaTime;
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            // Rotate left
            tank.rotationAngle += rotationSpeed * deltaTime;
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            // Rotate right
            tank.rotationAngle -= rotationSpeed * deltaTime;
        }
    }
}



void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    if (gameActive && window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
        float turretRotationSpeed = .05f;
        tank.turretRotationAngle += deltaX * turretRotationSpeed;
    }

}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (gameActive && IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && shootCooldown <= 0) {
        // Calculate turret's rotation matrix and direction
        glm::mat4 turretRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(tank.turretRotationAngle), glm::vec3(0, 1, 0));
        glm::vec3 turretDirection = glm::normalize(glm::vec3(turretRotationMatrix * glm::vec4(0, 0, -1, 0)));

        // Create a new projectile
        Projectile newProjectile;
        newProjectile.position = tank.position + glm::vec3(0, 1.6, 0);
        newProjectile.direction = turretDirection;
        newProjectile.lifetime = 1.5f;
        newProjectile.isActive = true;

        // Add the new projectile to the vector
        projectiles.push_back(newProjectile);

        // Reset shoot cooldown
        shootCooldown = 1.0f;
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}