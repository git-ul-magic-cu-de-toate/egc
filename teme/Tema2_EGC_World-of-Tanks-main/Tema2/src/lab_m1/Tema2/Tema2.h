#pragma once

#include <vector>
#include "lab_m1/Tema2/lab_camera.h"
#include "components/simple_scene.h"
#include "lab_camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#define Z_FAR		(200.f)
#define Z_NEAR		(.01f)

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        Tema2();
        ~Tema2();

        void Init() override;

        Mesh *CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices);

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        
        
        struct coordonate {
            float x;
            float y;
            float z;
        };

        bool gameActive = true; // Jocul este activ
        float gameTime = 0.0f; // Timpul total scurs în joc
        const float gameDuration = 60.0f; // Durata jocului în secunde (1 minut)

        // Parametrii camerei
        const float cameraDistance = 5.0f;  // Distanța față de tanc
        const float cameraHeight = 2.0f;    // Înălțimea camerei față de tanc
        const float cameraAngle = glm::radians(30.0f); // Unghiul de înclinare
   
        implemented::Camera* camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;
        bool projectionType;

        GLfloat right;
        GLfloat left;
        GLfloat bottom;
        GLfloat top;
        GLfloat fov;
    };
}   // namespace m1
