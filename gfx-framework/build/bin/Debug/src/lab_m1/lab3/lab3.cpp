#include "lab_m1/lab3/lab3.h"

#include <vector>
#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"


using namespace std;
using namespace m1;
#define PI 3.141592


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


int hits_opponent(struct proiectil p, float res_x, float res_y, float x_crt_1, float y_crt_1, float x_crt_2, float y_crt_2) {

    float d, x, y;
    d = 0.05 * res_x;
    x = p.x_proiectil;
    y = p.y_proiectil;

    if (p.id == 1)
        return (x - x_crt_2) * (x - x_crt_2) + (y - y_crt_2) * (y - y_crt_2) <= d * d;
    if (p.id == 2)
        return (x - x_crt_1) * (x - x_crt_1) + (y - y_crt_1) * (y - y_crt_1) <= d * d;
}


Lab3::Lab3()
{
}


Lab3::~Lab3()
{
}


void Lab3::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    culoare_teren = glm::vec3(0, 1, 0);
    culoare_tank_sus_1 = glm::vec3(0.5, 0.7, 0.15);
    culoare_tank_sus_2 = glm::vec3(1, 1, 0);
    culoare_tank_jos_1 = glm::vec3(0, 0, 0);
    culoare_tank_jos_2 = glm::vec3(0.65f, 0.32f, 0.17f);
    res_x = (float)resolution.x;
    res_y = (float)resolution.y;
    glm::vec3 corner_1 = glm::vec3(0.010, 0.010, 0);
    glm::vec3 corner_2 = glm::vec3(0.010, 0.010, 0);
    life_points_tank_1 = 5;
    life_points_tank_2 = 5;
    Mesh* teren = object2D::CreateField("teren", culoare_teren, (float)resolution.x, (float)resolution.y);
    Mesh* tank1 = object2D::CreateTank("tank1", culoare_tank_sus_1, culoare_tank_jos_1, (float)resolution.x, (float)resolution.y);
    Mesh* tank2 = object2D::CreateTank("tank2", culoare_tank_sus_2, culoare_tank_jos_2, (float)resolution.x, (float)resolution.y);
    Mesh* turela1 = object2D::CreateTurela("turela1", (float)resolution.x, (float)resolution.y);
    Mesh* turela2 = object2D::CreateTurela("turela2", (float)resolution.x, (float)resolution.y);
    Mesh* proiectil = object2D::CreateProiectil("proiectil", (float)resolution.x, (float)resolution.y);
    
    AddMeshToList(teren);
    AddMeshToList(tank1);
    AddMeshToList(tank2);
    AddMeshToList(turela1);
    AddMeshToList(turela2);
    AddMeshToList(proiectil);
    

    x_crt_tank_1 = 0.2; // il pun unde vreau
    x_crt_tank_2 = 0.95 * res_x; // il pun unde vreau
    rotation_turela_angle_1 = 0;
    rotation_turela_angle_2 = 0;
    rotation_angle_1 = 0;
    rotation_angle_2 = 0;
    g = 200;
    v1 = glm::vec3(0, 0, 0);
    v2 = glm::vec3(0, 0, 0);
    x_proiectil = y_proiectil = 0;
    proiectile = {};
}


void Lab3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.53f, 0.81f, 0.92f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab3::Update(float deltaTimeSeconds)
{

    modelMatrix = glm::mat3(1);
    double t1, Ax1, Ay1, Bx1, By1;
    int i1, j1, size1;
    i1 = 1;
    j1 = 3;
    size1 = meshes["teren"]->vertices.size();
    Ax1 = meshes["teren"]->vertices[i1].position[0];
    Bx1 = meshes["teren"]->vertices[j1].position[0];


    while (j1 < size1 && !(Ax1 <= x_crt_tank_1 && x_crt_tank_1 <= Bx1)) {
        i1 = i1 + 2;
        j1 = j1 + 2;
        Ax1 = meshes["teren"]->vertices[i1].position[0];
        Bx1 = meshes["teren"]->vertices[j1].position[0];
    }



    Ay1 = meshes["teren"]->vertices[i1].position[1];
    By1 = meshes["teren"]->vertices[j1].position[1];


    t1 = (x_crt_tank_1 - Ax1) / (Bx1 - Ax1);
    y_crt_tank_1 = Ay1 + t1 * (By1 - Ay1);
    rotation_angle_1 = atan2(By1 - Ay1, Bx1 - Ax1);
    glm::mat3 tank_matrix_1 = glm::mat3(1) * transform2D::Translate(x_crt_tank_1, y_crt_tank_1) * transform2D::Rotate(-rotation_angle_1) * transform2D::Scale(2.2, 2.2);
    glm::mat3 turela_matrix_1 = tank_matrix_1 * transform2D::Translate(0, res_y / 50) * transform2D::Rotate(rotation_turela_angle_1) * transform2D::Translate(0, -res_y / 50);

    //----------------------------------------------------------------------------------------------------------------------------------------------

    double t2, Ax2, Ay2, Bx2, By2, angle;
    int i2, j2, size2;
    i2 = 1;
    j2 = 3;
    size2 = meshes["teren"]->vertices.size();
    Ax2 = meshes["teren"]->vertices[i2].position[0];
    Bx2 = meshes["teren"]->vertices[j2].position[0];


    while (j2 < size2 && !(Ax2 <= x_crt_tank_2 && x_crt_tank_2 <= Bx2)) {
        i2 = i2 + 2;
        j2 = j2 + 2;
        Ax2 = meshes["teren"]->vertices[i2].position[0];
        Bx2 = meshes["teren"]->vertices[j2].position[0];
    }



    Ay2 = meshes["teren"]->vertices[i2].position[1];
    By2 = meshes["teren"]->vertices[j2].position[1];


    t2 = (x_crt_tank_2 - Ax2) / (Bx2 - Ax2);
    y_crt_tank_2 = Ay2 + t2 * (By2 - Ay2);
    rotation_angle_2 = atan2(By2 - Ay2, Bx2 - Ax2);

    glm::mat3 tank_matrix_2 = glm::mat3(1) * transform2D::Translate(x_crt_tank_2, y_crt_tank_2) * transform2D::Rotate(-rotation_angle_2) * transform2D::Scale(2.2, 2.2);
    glm::mat3 turela_matrix_2 = tank_matrix_2 * transform2D::Translate(0, res_y / 50) * transform2D::Rotate(rotation_turela_angle_2) * transform2D::Translate(0, -res_y / 50);


    // -----------------------------------------------------------------------------------------------------------------------------------------------


    v1 = glm::vec3(240 * cos(-rotation_turela_angle_1 + rotation_angle_1 + PI / 2), 240 * sin(-rotation_turela_angle_1 + rotation_angle_1 + PI / 2), 0);
    v2 = glm::vec3(240 * cos(-rotation_turela_angle_2 + rotation_angle_2 + PI / 2), 240 * sin(-rotation_turela_angle_2 + rotation_angle_2 + PI / 2), 0);


    for (int y = 0; y < proiectile.size(); y++) {
        proiectile[y].x_proiectil += 2 * proiectile[y].v[0] * deltaTimeSeconds;
        proiectile[y].y_proiectil += 2 * proiectile[y].v[1] * deltaTimeSeconds;
        proiectile[y].v[1] -= g * deltaTimeSeconds;
        int hits = hits_opponent(proiectile[y], res_x, res_y, x_crt_tank_1, y_crt_tank_1, x_crt_tank_2, y_crt_tank_2);
        if (hits) {
            if (proiectile[y].id == 1)
                life_points_tank_2--;
            else
                life_points_tank_1--;
            proiectile.erase(proiectile.begin() + y);
            y--;
        } else {
            int collision = object2D::check_ground_collision(res_x, proiectile[y], proiectile[y].x_proiectil, proiectile[y].y_proiectil, meshes["teren"],g);
            if (collision) {
                proiectile.erase(proiectile.begin() + y);
                y--;
            }

        }
       
    }


    //for (int y = 0; y < proiectile.size(); y++)
     //   proiectile[y].v[1] -= g * deltaTimeSeconds;

    for (int i = 0; i < proiectile.size(); i++) {
        glm::mat3 model = glm::mat3(1);
        float x, y;
        x = proiectile[i].x_proiectil;
        y = proiectile[i].y_proiectil;


        if(proiectile[i].id == 2)
            model = transform2D::Rotate(-rotation_angle_2) * transform2D::Translate(0, res_y / 50) * transform2D::Scale(2.2, 2.2) * transform2D::Translate(0, -res_y / 50)
       * transform2D::Translate(0, res_y / 50) * transform2D::Rotate(rotation_turela_angle_2) * transform2D::Translate(0, -res_y / 50);
    else
            model = transform2D::Rotate(-rotation_angle_1) * transform2D::Scale(2.2, 2.2) *
        transform2D::Translate(0, res_y / 50) * transform2D::Rotate(rotation_turela_angle_1) * transform2D::Translate(0, -res_y / 50);
        model = transform2D::Translate(x, y) * model;
        RenderMesh2D(meshes["proiectil"], shaders["VertexColor"], model);
    }


    RenderMesh2D(meshes["teren"], shaders["VertexColor"], modelMatrix);

    if (life_points_tank_1 > 0) {
        Mesh* full_lifebar_1 = object2D::CreateFullLifeBar("lifebar1", life_points_tank_1, res_x, res_y);
        Mesh* empty_lifebar_1 = object2D::CreateEmptyLifeBar("deathbar1", life_points_tank_1, res_x, res_y);
        AddMeshToList(full_lifebar_1);
        AddMeshToList(empty_lifebar_1);
        if(meshes["lifebar1"])
            RenderMesh2D(meshes["lifebar1"], shaders["VertexColor"], tank_matrix_1);
        if(meshes["deathbar1"])
            RenderMesh2D(meshes["deathbar1"], shaders["VertexColor"], tank_matrix_1);
        meshes.erase("lifebar1");
        meshes.erase("deathbar1");
        free(full_lifebar_1);
        free(empty_lifebar_1);


        RenderMesh2D(meshes["tank1"], shaders["VertexColor"], tank_matrix_1);
        Mesh* trajectory_1 = object2D::CreateTrajectoryPreview("trajectory1", x_crt_tank_1, y_crt_tank_1, v1, 10000, deltaTimeSeconds, g);
        AddMeshToList(trajectory_1);
        RenderMesh2D(meshes["turela1"], shaders["VertexColor"], turela_matrix_1);
        glm::mat3 traj_matrix = glm::mat3(1);
        RenderMesh2D(meshes["trajectory1"], shaders["VertexColor"], traj_matrix);
        meshes.erase("trajectory1");
        free(trajectory_1);
       
    }

    if (life_points_tank_2 > 0) {
        Mesh* full_lifebar_2 = object2D::CreateFullLifeBar("lifebar2", life_points_tank_2, res_x, res_y);
        Mesh* empty_lifebar_2 = object2D::CreateEmptyLifeBar("deathbar2", life_points_tank_2, res_x, res_y);
        AddMeshToList(full_lifebar_2);
        AddMeshToList(empty_lifebar_2);
        if (meshes["lifebar2"])
            RenderMesh2D(meshes["lifebar2"], shaders["VertexColor"], tank_matrix_2);
        if (meshes["deathbar2"])
            RenderMesh2D(meshes["deathbar2"], shaders["VertexColor"], tank_matrix_2);
        meshes.erase("lifebar2");
        meshes.erase("deathbar2");
        free(full_lifebar_2);
        free(empty_lifebar_2);


        RenderMesh2D(meshes["tank2"], shaders["VertexColor"], tank_matrix_2);
        Mesh* trajectory_2 = object2D::CreateTrajectoryPreview("trajectory2", x_crt_tank_2, y_crt_tank_2, v2, 10000, deltaTimeSeconds, g);
        AddMeshToList(trajectory_2);
        RenderMesh2D(meshes["turela2"], shaders["VertexColor"], turela_matrix_2);
        glm::mat3 traj_matrix = glm::mat3(1);
        RenderMesh2D(meshes["trajectory2"], shaders["VertexColor"], traj_matrix);
        meshes.erase("trajectory2");
        free(trajectory_2);
    }

}


void Lab3::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab3::OnInputUpdate(float deltaTime, int mods)
{

    float speed = 200;

    if (window->KeyHold(GLFW_KEY_D) && x_crt_tank_1 + res_x / 300 <= res_x)
        x_crt_tank_1 += speed * deltaTime;
    if (window->KeyHold(GLFW_KEY_RIGHT) && x_crt_tank_2 + res_x / 300 <= res_x)
        x_crt_tank_2 += speed * deltaTime;
    if (window->KeyHold(GLFW_KEY_A) && x_crt_tank_1 - res_x / 300 >= 0)
        x_crt_tank_1 -= speed * deltaTime;
    if (window->KeyHold(GLFW_KEY_LEFT) && x_crt_tank_2 - res_x / 300 >= 0)
        x_crt_tank_2 -= speed * deltaTime;
    if (window->KeyHold(GLFW_KEY_W) && rotation_turela_angle_1 + PI / 180 >= -PI / 2 && rotation_turela_angle_1 + PI / 180 <= PI / 2)
        rotation_turela_angle_1 += PI / 180;
    if (window->KeyHold(GLFW_KEY_UP) && rotation_turela_angle_2 + PI / 180 >= -PI / 2 && rotation_turela_angle_2 + PI / 180 <= PI / 2)
        rotation_turela_angle_2 += PI / 180;
    if (window->KeyHold(GLFW_KEY_S) && rotation_turela_angle_1 - PI / 180 >= -PI / 2 && rotation_turela_angle_1 - PI / 180 <= PI / 2)
        rotation_turela_angle_1 -= PI / 180;
    if (window->KeyHold(GLFW_KEY_DOWN) && rotation_turela_angle_2 - PI / 180 >= -PI / 2 && rotation_turela_angle_2 - PI / 180 <= PI / 2)
        rotation_turela_angle_2 -= PI / 180;

}


void Lab3::OnKeyPress(int key, int mods)
{

    struct proiectil p_crt;

    if (key == GLFW_KEY_SPACE) {
        p_crt.x_proiectil = x_crt_tank_1;
        p_crt.y_proiectil = y_crt_tank_1;
        p_crt.v = v1;
        p_crt.id = 1;
        proiectile.push_back(p_crt);

    }
    else if (key == GLFW_KEY_ENTER) {
        p_crt.x_proiectil = x_crt_tank_2;
        p_crt.y_proiectil = y_crt_tank_2;
        p_crt.v = v2;
        p_crt.id = 2;
        proiectile.push_back(p_crt);
    }
}


void Lab3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab3::OnWindowResize(int width, int height)
{
}


