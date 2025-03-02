#pragma once

#include "components/simple_scene.h"


struct proiectil {
    float x_proiectil, y_proiectil;
    glm::vec3 v;
    int id;
};


namespace m1
{
    class Lab3 : public gfxc::SimpleScene
    {
     public:
        Lab3();
        ~Lab3();

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
        glm::mat3 modelMatrix;
        double x_crt_tank_1, y_crt_tank_1;
        double x_crt_tank_2, y_crt_tank_2;
        glm::vec3 culoare_teren;
        glm::vec3 culoare_tank_sus_1;
        glm::vec3 culoare_tank_jos_1;
        glm::vec3 culoare_tank_sus_2;
        glm::vec3 culoare_tank_jos_2;
        double res_x,res_y,rotation_angle_1,rotation_turela_angle_1;
        double rotation_angle_2, rotation_turela_angle_2;
        double g;
        glm::vec3 v1;
        glm::vec3 v2;
        float x_proiectil, y_proiectil;
        std::vector <struct proiectil> proiectile;
        int life_points_tank_1, life_points_tank_2;
        int vf[200]; 
       
        // TODO(student): If you need any other class variables, define them here.

    };
}   // namespace m1
