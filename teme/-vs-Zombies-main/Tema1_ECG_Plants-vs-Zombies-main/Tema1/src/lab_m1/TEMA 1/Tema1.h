#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;


    protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;

        glm::vec2 starPosition; // Poziția curentă a steluței
        float starRotation; // Unghiul de rotație curent al steluței
        float starRotationSpeed; // Viteza de rotație a steluței (grade pe secundă)
        glm::vec2 starVelocity; // Viteza de deplasare a steluței
        
        std::vector<glm::vec3> colors = {
                glm::vec3(0.8f, 0.1f, 0.1f), // Rosu
                glm::vec3(0.5f, 0.3f, 0.8f), // Mov
                glm::vec3(0.0f, 0.0f, 1.0f), // Albastru
                glm::vec3(1.0f, 0.5f, 0.0f)  // Portocaliu
        };
 
        struct Enemy {
            glm::vec2 position; // Poziția inamicului
            float speed; // Viteza de mișcare
            float scale_x = 1.0f;
            float scale_y = 1.0f; // Scalarea pentru inamic
            bool isScaling; // Dacă inamicul trebuie să fie scalat
            glm::vec3 color; // Culoarea inamicului
            int colorindex; // Indexul culorii inamicului
        };
    
        std::vector<Enemy> enemies;

        struct Romb {
            glm::vec2 position; 
            float speed; // Viteza de mișcare
            float scale_x = 1.0f;
            float scale_y = 1.0f; // Scalarea pentru romb
            bool isScaling; 
            glm::vec3 color; 
            int colorindex; 
        };
        
        std::vector<Romb> romb;

        struct Projectile {
            glm::vec2 position;
            glm::vec2 direction;
            glm::vec3 color;
            float speed;
            float rotationAngle = 0.0f; 
        };

        struct Star {
            glm::vec2 position;
            float rotationAngle = 0.0f;
            float speed = 100.0f; // Viteza de deplasare
        };

        int windowSizeX{}, windowSizeY{};
        glm::vec2 initialMousePosition;
        glm::vec2 currentMousePosition; 

    };
}   // namespace m1