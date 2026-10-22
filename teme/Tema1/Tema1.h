#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();
        struct Projectile {
            glm::vec3 vec;
            char* color;
            float rotationAngle;
            float radius;// Adaugă proprietatea color pentru a stoca culoarea inamicului
            int health = 0;
        };

        void Init() override;



    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void DrawStars();
        void GenerateStars(float deltaTimeSeconds);
        void DetectCollision();
        void DrawEnemy(float deltaTimeSeconds);
        void GenerateEnemy(float deltaTimeSeconds);
        void GenerateProjectile(float deltaTimeSeconds, Projectile projectile);
        void PointStarsAndDiamonds();
        void PutInBox();
        void DrawProjectile(float deltaTimeSeconds);
        void DisappearEnemy(float deltaTimeSeconds);
        void DisappearDiamond(float deltaTimeSeconds);
        void CollisionEnemyProjectile();
        void CollisionEnemyDiamond(float deltaTimeSeconds);


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
        struct Enemy {
            glm::vec3 vec;
            char* color;
            float radius;// Adaugă proprietatea color pentru a stoca culoarea inamicului
            char* nameColor;
            bool isDead = false;
            float scaleX = 0.8f;
            float scaleY = 0.8f;
        };

        struct Diamond {
            float x, y;
            char* color;
            float radius;
            char* nameColor;
            float scaleX = 0.8f;
            float scaleY = 0.8f;
        };

        struct DisappearingDiamond {
            float x, y;
            float scaleX, scaleY;
            bool isAnimating;
            char* color;
            char* nameColor;
        };

        struct DisappearingEnemy {
            float x, y;
            float scaleX, scaleY;
            bool isAnimating;
            char* color;
            char* nameColor;
        };

        std::vector<DisappearingDiamond > disappearingDiamond;
        std::vector<DisappearingEnemy> disappearingEnemy;
        std::vector<Enemy> enemy;
        std::vector<Projectile> projectiles;
        std::vector<Diamond> putInBox;
        glm::mat3 arrayModelMatrix[9];
        std::vector<glm::mat3> lifes;
        std::vector<glm::mat3> boxes;
        std::vector<glm::mat3> squares;
        std::vector<int> enemyHealth;
        glm::mat3 rectangleMatrix;
        glm::mat3 hexMatrix;
        glm::mat3 diamondMatrix;
        glm::mat3 starMatrix;
        glm::mat3 randomStarMatrix;
        glm::mat3 modelMatrix;
        glm::mat3 hexForDis;
        glm::mat3 diamondForThis;
        std::vector<glm::vec3> stars;
        std::vector<bool>  boxesOccupied;
        std::vector<bool> boxesRelease;
        std::vector<bool> boxesPutDiamond;

        float translateX, translateY;
        float scaleX, scaleY, scaleX1, scaleY1;
        glm::vec3 corner = glm::vec3(0, 0, 0);
        float squareSide = 100;
        int selectedStarIndex = -1;
        float widthRectangle = 380;
        float lenghtRectangle = 75;
        float widthDiamond = 50;
        float lengthDiamond = 20;
        float widthMiniRec = 10;
        float lengthMiniRec = 40;
        float size1 = 40;
        float size2 = 30;
        float size3 = 20;
        float size4 = 13;
        float size1Star = 20;
        float size2Star = 15;
        float size3star = 22.5;
        float size4Star = 40;
        float size5Star = 55;
        float size6Star = 35;
        float size7Star = 62.5;
        float angularStep = 0;
        glm::ivec2 currentMousePosition;
        bool directionX = 0;
        bool directionY = 0;
        float tx1 = 0;
        float ty1 = 0;
        int scaleBoolean = 0;
        int x = 830;
        int x1 = 830;
        int y = 550;
       
        bool showLifeStar = false;
        bool leftMouseButtonPressed = false;
        glm::vec2 diamondPosition = glm::vec2(470, 647);
        int lifeStars = 5;
        bool showDiamondPurple = false;
        bool showDiamondBlue = false;
        bool showDiamondYellow = false;
        bool showDiamondOrange = false;
        float posMouseX;
        float posMouseY;
        char* colorDiamond;
        char* color;
        float x_diamond;
        float y_diamond;
        float timeSinceLastEnemy = 0.0f;
        const float timeBetweenEnemies = 5.0f;
        float timeSinceLastStars = 0.0f;
        float timeBetweenStars = 5.0f;
        float random = 0.f;
        float timeSinceLastProjectile = 0.0f;
        float intervalBetweenProjectiles = 3.0f;
       
    };
}   // namespace m1
