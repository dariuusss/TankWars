#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "lab3.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateField(const std::string &name, glm::vec3 color, float res_x,float res_y, bool fill = true);
    Mesh* CreateTank(const std::string& name, glm::vec3 color_upper_tr, glm::vec3 color_lower_tr, float res_x,
        float res_y, bool fill = true);
    Mesh* CreateTurela(const std::string& name, float res_x, float res_y, bool fill = true);
    Mesh* CreateProiectil(const std::string& name, float res_x, float res_y, bool fill = true);
    void generate_field_vertices(std::vector<VertexFormat> &vertices, glm::vec3 color, float res_x, float res_y);
    double crazy_sine(double arg);
    void fill_field_indices(std::vector<unsigned int> &indices, int size);
    void generate_tank_circle(std::vector<VertexFormat> &vertices, std::vector<unsigned int> &indices, VertexFormat center, double r);
    Mesh* CreateFullLifeBar(const std::string& name, int hp, float res_x, float res_y, bool fill = true);
    Mesh* CreateEmptyLifeBar(const std::string& name, int hp, float res_x, float res_y, bool fill = false);
    Mesh* CreateTrajectoryPreview(const std::string& name, float x, float y, glm::vec3 v, int nr_points, float deltaTimeSeconds, double g);
    int check_ground_collision(float res_x,struct proiectil p,float x, float y, Mesh* teren,float g);    
}
