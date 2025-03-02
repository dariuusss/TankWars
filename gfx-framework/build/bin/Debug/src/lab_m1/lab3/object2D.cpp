#include "object2D.h"
#include "lab3.h"
#include <vector>
#include <cmath>
#include "core/engine.h"
#include "utils/gl_utils.h"

int object2D::check_ground_collision(float res_x,struct proiectil p, float x, float y, Mesh* teren,float g) {

    if (p.v[1] <= 0) {
        
        int i = 1, j = 3, size = teren->vertices.size();
        int indice = -1;
        while (j < size) {
            double x1, x2;
            x1 = teren->vertices[i].position[0];
            x2 = teren->vertices[j].position[0];
            if (x1 <= x && x <= x2) {
                indice = i;
                break;
            }
            i += 2;
            j += 2;
        }

        

        //refa asta
        if (indice != -1) {
            
            float y_map = teren->vertices[indice].position[1];
            float d = res_x / 90000;
            if (y - y_map <= d)
                return 1;
            return 0;
            
        } 
        return 0;
        
        
    }
        
    return 0;
}


void object2D::generate_field_vertices(std::vector<VertexFormat> &vertices, glm::vec3 color,float res_x, float res_y) {

    
    for (double x = 0; x <= res_x; x = x + 0.01 * res_x) {
        vertices.push_back(VertexFormat(glm::vec3(x, 0, 0),color));
        vertices.push_back(VertexFormat(glm::vec3(x,crazy_sine(x), 0), color));
    }

   
} // e ok

double object2D::crazy_sine(double arg) {
    return 10 * (sin(2 * arg) + 7 * sin(arg / 2) + 3 * sin(3 / 4 * arg) + arg / 30);
} // e ok

void object2D::fill_field_indices(std::vector<unsigned int> &indices,int size) {
    for (unsigned int i = 0; i < size - 2; i++) {
        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }
} // e ok


Mesh* object2D::CreateField(const std::string &name, glm::vec3 color, float res_x, float res_y,bool fill) { // e ok
    

    std::vector<VertexFormat> vertices =
    {
        
    };

    object2D::generate_field_vertices(vertices,color,res_x,res_y);

    Mesh* teren = new Mesh(name);
    std::vector<unsigned int> indices = {};
    object2D::fill_field_indices(indices, vertices.size());

    if (!fill) {
        teren->SetDrawMode(GL_TRIANGLES);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
       //indices.push_back(0);
        //indices.push_back(2);
    }

    teren->InitFromData(vertices, indices);
    return teren;
}



Mesh* object2D::CreateTank(const std::string& name, glm::vec3 color_upper_tr, glm::vec3 color_lower_tr,float res_x,
    float res_y,bool fill)
{
  
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(- 3 * res_y / 100, res_y / 100 ,0),color_upper_tr), // 0
        VertexFormat(glm::vec3(3 * res_y / 100, res_y / 100 ,0),color_upper_tr), // 1
        VertexFormat(glm::vec3(1.5 * res_y / 100, 2 * res_y / 100 ,0),color_upper_tr), // 2
        VertexFormat(glm::vec3(-1.5 * res_y / 100, 2 * res_y / 100 ,0),color_upper_tr), // 3
        VertexFormat(glm::vec3(-res_y / 100,0,0),color_lower_tr), // 4
        VertexFormat(glm::vec3(res_y / 100,0,0),color_lower_tr), // 5
        VertexFormat(glm::vec3(- 2.25 * res_y / 100, res_y / 100 ,0),color_lower_tr), // 6
        VertexFormat(glm::vec3(2.25 * res_y / 100, res_y / 100 ,0),color_lower_tr) // 7
       
    
    };

    VertexFormat center = VertexFormat(glm::vec3(0,res_y / 50,0), color_upper_tr);
    
    Mesh* tank = new Mesh(name);
    std::vector<unsigned int> indices = {0,3,2,1,0,2,6,7,5,6,4,5};

    generate_tank_circle(vertices, indices, center, res_y / 100);
    

    if (!fill) {
        tank->SetDrawMode(GL_TRIANGLES);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
       //indices.push_back(0);
        //indices.push_back(2);
    }

    tank->InitFromData(vertices, indices);
    return tank;
}


void object2D::generate_tank_circle(std::vector<VertexFormat>& vertices, std::vector<unsigned int>& indices, VertexFormat center, double r) {


    vertices.push_back(center); //centrul va avea indicele 8
    double x, y;
    for (double angle = 0; angle < 3.1415; angle = angle + 3.1415 / 180) {
        x = r * cos(angle);
        y = 0.8 * r * sin(angle);
        vertices.push_back(VertexFormat(center.position + glm::vec3(x, y, 0), center.color));
    }

    int size = vertices.size();
    for (int i = 9; i + 1 < size; i++) {
        indices.push_back(i);
        indices.push_back(8);
        indices.push_back(i + 1);
    }

    //pana aici am construit cercul
}



Mesh* object2D::CreateTurela(const std::string& name, float res_x, float res_y, bool fill)
{

    std::vector<VertexFormat> vertices = {};
    Mesh* turela = new Mesh(name);
    std::vector<unsigned int> indices = {};

    VertexFormat center = VertexFormat(glm::vec3(0, res_y / 50, 0), glm::vec3(0, 0, 0));

    vertices.push_back(VertexFormat(center.position + glm::vec3(-1.1, 0.8 * res_y / 100, 0), glm::vec3(0, 0, 0))); // teava neagra
    vertices.push_back(VertexFormat(center.position + glm::vec3(1.1, 0.8 * res_y / 100, 0), glm::vec3(0, 0, 0))); // teava neagra
    vertices.push_back(VertexFormat(center.position + glm::vec3(-1.1, 1.8 * res_y / 100, 0), glm::vec3(0, 0, 0))); // teava neagra
    vertices.push_back(VertexFormat(center.position + glm::vec3(1.1, 1.8 * res_y / 100, 0), glm::vec3(0, 0, 0))); // teava neagra

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(3);
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);


    if (!fill) {
        turela->SetDrawMode(GL_TRIANGLES);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
       //indices.push_back(0);
        //indices.push_back(2);
    }

    turela->InitFromData(vertices, indices);
    return turela;
}

Mesh* object2D::CreateProiectil(const std::string& name, float res_x, float res_y, bool fill)
{

    std::vector<VertexFormat> vertices = {};
    Mesh* proiectil = new Mesh(name);
    std::vector<unsigned int> indices = {};

    VertexFormat projectile_center = VertexFormat(glm::vec3(1.1, 1.8 * res_y / 100 + res_y / 50, 0), glm::vec3(0, 0, 0));
    vertices.push_back(projectile_center);

    float x, y;

    for (double angle = 0; angle < 2 * 3.1415; angle = angle + 3.1415 / 1000) {
        x = 1.1 * cos(angle);
        y = 1.1 * sin(angle);
        vertices.push_back(VertexFormat(projectile_center.position + glm::vec3(x, y, 0), projectile_center.color));
    }

    int size = vertices.size();
    for (int i = 1; i + 1 < size; i++) {
        indices.push_back(i);
        indices.push_back(0);
        indices.push_back(i + 1);
    }

    

    if (!fill) {
        proiectil->SetDrawMode(GL_TRIANGLES);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
       //indices.push_back(0);
        //indices.push_back(2);
    }

    proiectil->InitFromData(vertices, indices);
    return proiectil;
}


Mesh* object2D::CreateFullLifeBar(const std::string& name,int hp, float res_x, float res_y, bool fill)
{
    
    std::vector<VertexFormat> vertices = {

    VertexFormat(glm::vec3(-1.3 * res_y / 100, 4 * res_y / 100, 0), glm::vec3(1,1,1)),
    VertexFormat(glm::vec3(-1.3 * res_y / 100, 4.5 * res_y / 100, 0), glm::vec3(1,1,1)),
    VertexFormat(glm::vec3(-1.3 * res_y / 100 + 0.52 * res_y / 100 * hp, 4 * res_y / 100, 0), glm::vec3(1,1,1)),
    VertexFormat(glm::vec3(-1.3 * res_y / 100 + 0.52 * res_y / 100 * hp, 4.5 * res_y / 100, 0), glm::vec3(1,1,1)),
    };

    

    Mesh* lifebar = new Mesh(name);
    std::vector<unsigned int> indices = {0,1,2,1,2,3};



    if (!fill) {
        lifebar->SetDrawMode(GL_TRIANGLES);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
       //indices.push_back(0);
        //indices.push_back(2);
    }

    lifebar->InitFromData(vertices, indices);
    return lifebar;
}




Mesh* object2D::CreateEmptyLifeBar(const std::string& name, int hp, float res_x, float res_y, bool fill)
{

    std::vector<VertexFormat> vertices = {

    VertexFormat(glm::vec3(-1.3 * res_y / 100 + 0.52 * res_y / 100 * hp, 4 * res_y / 100, 0), glm::vec3(1,1,1)),
    VertexFormat(glm::vec3(-1.3 * res_y / 100 + 0.52 * res_y / 100 * hp, 4.5 * res_y / 100, 0), glm::vec3(1,1,1)),
    VertexFormat(glm::vec3(-1.3 * res_y / 100 + 5 * 0.52 * res_y / 100, 4 * res_y / 100, 0), glm::vec3(1,1,1)),
    VertexFormat(glm::vec3(-1.3 * res_y / 100 + 5 * 0.52 * res_y / 100, 4.5 * res_y / 100, 0), glm::vec3(1,1,1)),
    };

    Mesh* lifebar = new Mesh(name);
    std::vector<unsigned int> indices = { 0,1,1,3,3,2,2,0};



    if (!fill) {
        lifebar->SetDrawMode(GL_LINES);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
       //indices.push_back(0);
        //indices.push_back(2);
    }

    lifebar->InitFromData(vertices, indices);
    return lifebar;
}




Mesh* object2D::CreateTrajectoryPreview(const std::string& name, float x , float y, glm::vec3 v, int nr_points, float deltaTimeSeconds, double g)
{

    std::vector<VertexFormat> vertices = {

    };

    for (int i = 0; i < nr_points; i++) {
        x += 2 * v[0] * deltaTimeSeconds;
        y += 2 * v[1] * deltaTimeSeconds;
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), glm::vec3(0,0,0)));
        v[1] -= g * deltaTimeSeconds;
    }


    Mesh* trajectory = new Mesh(name);
    std::vector<unsigned int> indices = { };
    int size = vertices.size();
    for (int i = 0; i < size; i++)
        indices.push_back(i);
    trajectory->SetDrawMode(GL_LINE_STRIP);
    trajectory->InitFromData(vertices, indices);
    return trajectory;
}






