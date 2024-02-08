#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/Tema1_transformari.h"
#include "lab_m1/Tema1/Tema1_obiecte.h"

using namespace std;
using namespace m1;

float currentTime = 0.0f;
float currentTimestars = 0.0f;
float appearDuration = 5.0f;
float appearDurationstars = 10.0f;
float currentTimeHexagon = 0.0f;
float appearDurationHexagon = 5.0f;
int lifes = 3;
int mouse_moveX, mouse_moveY;
float angularstep=0;
int stele_cost = 5;
std::vector<glm::mat3> starPositions;
std::vector<glm::vec4> HexagonLine;//(linia,timpul,pozitia de inceput,culoarea,viata)
std::vector<glm::vec4> Star1;
std::vector<glm::vec4> Star2;
std::vector<glm::vec4> Star3;
std::vector<glm::vec4> StarLine;
std::vector<glm::vec4> Scalar;
bool isDragging = false;
int mouse_romb;
float x_plant, y_plant;
struct Square {
    int exist;
    int color;
};
std::vector<Square> squareElements(9);
float outerRadius = 25;

Tema1::Tema1() {}

Tema1::~Tema1() {}

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 125;
    float length = 480;
    float width = 75;
    float innerRadius = 10;
    {
        Mesh* square1 = obiect2D::CreateSquare("square1", corner, squareSide, glm::vec3(0, 1, 0), true);
        AddMeshToList(square1);
        Mesh* square2 = obiect2D::CreateSquare("square2", corner, squareSide, glm::vec3(1, 1, 1), false);
        AddMeshToList(square2);
        Mesh* square3 = obiect2D::CreateSquare("square3", corner, squareSide - 25, glm::vec3(1, 0, 0), true);
        AddMeshToList(square3);
        Mesh* rectangle1 = obiect2D::CreateRectangle("rectangle1", corner, length, width, glm::vec3(1, 0, 0), true);
        AddMeshToList(rectangle1);
        Mesh* star1 = obiect2D::CreateStar("star1", corner, innerRadius, outerRadius, glm::vec3(0.5, 0.5, 0.5), true);
        AddMeshToList(star1);
        Mesh* star2 = obiect2D::CreateStar("star2", corner, innerRadius + 5, outerRadius + 15, glm::vec3(1, 0, 1), true);
        AddMeshToList(star2);
        Mesh* star3 = obiect2D::CreateStar("star3", corner, innerRadius, outerRadius, glm::vec3(1, 0.5, 0), true);
        AddMeshToList(star3);
        Mesh* star4 = obiect2D::CreateStar("star4", corner, innerRadius, outerRadius, glm::vec3(0, 0, 1), true);
        AddMeshToList(star4);
        Mesh* star5 = obiect2D::CreateStar("star5", corner, innerRadius, outerRadius, glm::vec3(1, 1, 0), true);
        AddMeshToList(star5);
        Mesh* star6 = obiect2D::CreateStar("star6", corner, innerRadius, outerRadius, glm::vec3(0.5, 0, 1), true);
        AddMeshToList(star6);
        Mesh* hexagon1 = obiect2D::CreateHexagon("hexagon1", corner, outerRadius, innerRadius, glm::vec3(1, 0.5, 0), glm::vec3(0, 1, 0));
        AddMeshToList(hexagon1);
        Mesh* hexagon2 = obiect2D::CreateHexagon("hexagon2", corner, outerRadius, innerRadius, glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
        AddMeshToList(hexagon2);
        Mesh* hexagon3 = obiect2D::CreateHexagon("hexagon3", corner, outerRadius, innerRadius, glm::vec3(1, 1, 0), glm::vec3(0, 1, 0));
        AddMeshToList(hexagon3);
        Mesh* hexagon4 = obiect2D::CreateHexagon("hexagon4", corner, outerRadius, innerRadius, glm::vec3(0.5, 0, 1), glm::vec3(0, 1, 0));
        AddMeshToList(hexagon4);
        Mesh* romb1 = obiect2D::CreateRomb("romb1", corner, 50, 100, 60, 20, glm::vec3(1, 0.5, 0));
        AddMeshToList(romb1);
        Mesh* romb2 = obiect2D::CreateRomb("romb2", corner, 50, 100, 60, 20, glm::vec3(0, 0, 1));
        AddMeshToList(romb2);
        Mesh* romb3 = obiect2D::CreateRomb("romb3", corner, 50, 100, 60, 20, glm::vec3(1, 1, 0));
        AddMeshToList(romb3);
        Mesh* romb4 = obiect2D::CreateRomb("romb4", corner, 50, 100, 60, 20, glm::vec3(0.5, 0, 1));
        AddMeshToList(romb4);
        for (int i = 0; i < 100; i++) {
            int x = rand() % (1280 + 1);
            int y = rand() % (720 + 1);
            int x1 = rand() % (1280 + 1);
            int y1 = rand() % (720 + 1);
            int x2 = rand() % (1280 + 1);
            int y2 = rand() % (720 + 1);
            Star1.push_back(glm::vec4(x, y, 1,1));
            Star2.push_back(glm::vec4(x1, y1, 1,1));
            Star3.push_back(glm::vec4(x2, y2, 1,1));
        }
    }
    for (int i = 0; i < 100; i++) {
        int x = rand() % (2 + 1);
        int y = rand() % (3 + 1);
        HexagonLine.push_back(glm::vec4(x,i+1,1280,y));
    }
    for (int i = 0; i < 100; i++) {
        StarLine.push_back(glm::vec4(235, 410, 585, 1));
    }
    for (int i = 0; i < 100; i++) {
        Scalar.push_back(glm::vec4(1, 1, 1, 1));
    }
}


void Tema1::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
    glDisable(GL_DEPTH_TEST);
}  

void Tema1::Update(float deltaTimeSeconds)
{
    {//locul de pus plante
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(125, 10);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(300, 10);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(475, 10);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(125, 185);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(300, 185);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(475, 185);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(125, 360);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(300, 360);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(475, 360);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        //bara de iesire
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(10, 10);
        RenderMesh2D(meshes["rectangle1"], shaders["VertexColor"], modelMatrix);

        //locatia plantelor de prins si pus in joc
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(75, 550);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(250, 550);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(425, 550);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(600, 550);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

        //plantele
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(135, 610);
        RenderMesh2D(meshes["romb1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(310, 610);
        RenderMesh2D(meshes["romb2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(485, 610);
        RenderMesh2D(meshes["romb3"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(660, 610);
        RenderMesh2D(meshes["romb4"], shaders["VertexColor"], modelMatrix);

        // Costul de stele
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(85, 525);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(260, 525);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(310, 525);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(435, 525);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(485, 525);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(610, 525);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(660, 525);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(710, 525);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);
    }

    if (lifes >= 1) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(775, 575);
        RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        if (lifes >= 2)
        {
            modelMatrix *= transformari2D::Translate(900, 575);
            RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            if (lifes == 3)
            {
                modelMatrix *= transformari2D::Translate(1025, 575);
                RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
                modelMatrix = glm::mat3(1);
            }
        }
    }
    if (lifes == 0) {
        exit(0);
    }
    //stele 10
    {
        if (stele_cost >= 1 && stele_cost <= 10) 
        {
            for (int i = 1; i <= stele_cost; i++)
            {
                int xCoordinate = 800 + (i - 1) * 50;
                modelMatrix = glm::mat3(1);
                modelMatrix *= transformari2D::Translate(xCoordinate, 550);
                RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);
            }
        }
    }

    currentTimeHexagon += deltaTimeSeconds;
    {
        for (size_t i = 0; i < HexagonLine.size(); ++i)
        {
            auto& hexagonPosition = HexagonLine[i];
            auto& starPosition = StarLine[i];
            auto& scalarmesh = Scalar[i];
            auto& stea1 = Star1[i];
            auto& stea2 = Star2[i];
            auto& stea3 = Star3[i];
            if (currentTimeHexagon >= appearDurationHexagon * hexagonPosition.y)
            {
                hexagonPosition.z -= deltaTimeSeconds * 100;
                modelMatrix = glm::mat3(1);
                if (hexagonPosition.x == 0)
                {
                    modelMatrix *= transformari2D::Translate(hexagonPosition.z, 72);
                    
                    if (squareElements[0].color - 1 == hexagonPosition.w && squareElements[0].exist==1)
                    {
                        modelStar = glm::mat3(1);
                        starPosition.x += deltaTimeSeconds * 100;
                        starPosition.w -= deltaTimeSeconds;
                        modelStar *= transformari2D::Translate(starPosition.x, 72);
                        modelStar *= transformari2D::Rotate(starPosition.w);
                        if (hexagonPosition.z - outerRadius <= starPosition.x + outerRadius)
                        {
                            if (scalarmesh.x >= 0 && scalarmesh.y >= 0)
                            {
                                hexagonPosition.z += deltaTimeSeconds * 100;
                                starPosition.x -= deltaTimeSeconds * 100;
                                scalarmesh.x -= deltaTimeSeconds;
                                scalarmesh.y -= deltaTimeSeconds;
                                modelStar *= transformari2D::Scale(scalarmesh.x, scalarmesh.x);
                                modelMatrix *= transformari2D::Scale(scalarmesh.y, scalarmesh.y);
                            }
                            else if(scalarmesh.x <= 0 && scalarmesh.y <= 0)
                            {
                                starPosition.x = 2000;
                                hexagonPosition.z = -85;
                            }
                        }
                        if (hexagonPosition.w == 0)
                        {
                            RenderMesh2D(meshes["star3"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 1)
                        {
                            RenderMesh2D(meshes["star4"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 2)
                        {
                            RenderMesh2D(meshes["star5"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 3)
                        {
                            RenderMesh2D(meshes["star6"], shaders["VertexColor"], modelStar);
                        }
                    }
                    if (squareElements[1].color - 1 == hexagonPosition.w && squareElements[1].exist == 1)
                    {
                        modelStar = glm::mat3(1);
                        starPosition.y += deltaTimeSeconds * 100;
                        starPosition.w -= deltaTimeSeconds;
                        modelStar *= transformari2D::Translate(starPosition.y, 72);
                        modelStar *= transformari2D::Rotate(starPosition.w);
                        if (hexagonPosition.z - outerRadius <= starPosition.y + outerRadius)
                        {
                            if (scalarmesh.x >= 0 && scalarmesh.y >= 0)
                            {
                                hexagonPosition.z += deltaTimeSeconds * 100;
                                starPosition.y -= deltaTimeSeconds * 100;
                                scalarmesh.x -= deltaTimeSeconds;
                                scalarmesh.y -= deltaTimeSeconds;
                                modelStar *= transformari2D::Scale(scalarmesh.x, scalarmesh.x);
                                modelMatrix *= transformari2D::Scale(scalarmesh.y, scalarmesh.y);
                            }
                            else if (scalarmesh.x <= 0 && scalarmesh.y <= 0)
                            {
                                starPosition.y = 2000;
                                hexagonPosition.z = -85;
                            }
                        }
                        if (hexagonPosition.w == 0)
                        {
                            RenderMesh2D(meshes["star3"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 1)
                        {
                            RenderMesh2D(meshes["star4"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 2)
                        {
                            RenderMesh2D(meshes["star5"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 3)
                        {
                            RenderMesh2D(meshes["star6"], shaders["VertexColor"], modelStar);
                        }
                    }
                    if (squareElements[2].color - 1 == hexagonPosition.w && squareElements[2].exist == 1)
                    {
                        modelStar = glm::mat3(1);
                        starPosition.z += deltaTimeSeconds * 100;
                        starPosition.w -= deltaTimeSeconds;
                        modelStar *= transformari2D::Translate(starPosition.z, 72);
                        modelStar *= transformari2D::Rotate(starPosition.w);
                        if (hexagonPosition.z - outerRadius <= starPosition.z + outerRadius)
                        {
                            if (scalarmesh.x >= 0 && scalarmesh.y >= 0)
                            {
                                hexagonPosition.z += deltaTimeSeconds * 100;
                                starPosition.z -= deltaTimeSeconds * 100;
                                scalarmesh.x -= deltaTimeSeconds;
                                scalarmesh.y -= deltaTimeSeconds;
                                modelStar *= transformari2D::Scale(scalarmesh.x, scalarmesh.x);
                                modelMatrix *= transformari2D::Scale(scalarmesh.y, scalarmesh.y);
                            }
                            else if (scalarmesh.x <= 0 && scalarmesh.y <= 0)
                            {
                                starPosition.z = 2000;
                                hexagonPosition.z = -85;
                            }
                        }
                        if (hexagonPosition.w == 0)
                        {
                            RenderMesh2D(meshes["star3"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 1)
                        {
                            RenderMesh2D(meshes["star4"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 2)
                        {
                            RenderMesh2D(meshes["star5"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 3)
                        {
                            RenderMesh2D(meshes["star6"], shaders["VertexColor"], modelStar);
                        }
                    }
                    if (hexagonPosition.z <= 250 && hexagonPosition.z >= 125)
                    {
                        squareElements[0].exist = 0;
                    }
                    if (hexagonPosition.z <= 425 && hexagonPosition.z >= 300)
                    {
                        squareElements[1].exist = 0;
                    }
                    if (hexagonPosition.z <= 600 && hexagonPosition.z >= 475)
                    {
                        squareElements[2].exist = 0;
                    }
                }
                else if (hexagonPosition.x == 1)
                {
                    modelMatrix *= transformari2D::Translate(hexagonPosition.z, 250);
                    if (squareElements[3].color - 1 == hexagonPosition.w && squareElements[3].exist == 1)
                    {
                        modelStar = glm::mat3(1);
                        starPosition.x += deltaTimeSeconds * 100;
                        starPosition.w -= deltaTimeSeconds;
                        modelStar *= transformari2D::Translate(starPosition.x,250);
                        modelStar *= transformari2D::Rotate(starPosition.w);
                        if (hexagonPosition.z - outerRadius <= starPosition.x + outerRadius)
                        {
                            if (scalarmesh.x >= 0 && scalarmesh.y >= 0)
                            {
                                hexagonPosition.z += deltaTimeSeconds * 100;
                                starPosition.x -= deltaTimeSeconds * 100;
                                scalarmesh.x -= deltaTimeSeconds;
                                scalarmesh.y -= deltaTimeSeconds;
                                modelStar *= transformari2D::Scale(scalarmesh.x, scalarmesh.x);
                                modelMatrix *= transformari2D::Scale(scalarmesh.y, scalarmesh.y);
                            }
                            else if (scalarmesh.x <= 0 && scalarmesh.y <= 0)
                            {
                                starPosition.x = 2000;
                                hexagonPosition.z = -85;
                            }
                        }
                        if (hexagonPosition.w == 0)
                        {
                            RenderMesh2D(meshes["star3"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 1)
                        {
                            RenderMesh2D(meshes["star4"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 2)
                        {
                            RenderMesh2D(meshes["star5"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 3)
                        {
                            RenderMesh2D(meshes["star6"], shaders["VertexColor"], modelStar);
                        }
                    }
                    if (squareElements[4].color - 1 == hexagonPosition.w && squareElements[4].exist == 1)
                    {
                        modelStar = glm::mat3(1);
                        starPosition.y += deltaTimeSeconds * 100;
                        starPosition.w -= deltaTimeSeconds;
                        modelStar *= transformari2D::Translate(starPosition.y, 250);
                        modelStar *= transformari2D::Rotate(starPosition.w);
                        if (hexagonPosition.z - outerRadius <= starPosition.y + outerRadius)
                        {
                            if (scalarmesh.x >= 0 && scalarmesh.y >= 0)
                            {
                                hexagonPosition.z += deltaTimeSeconds * 100;
                                starPosition.y -= deltaTimeSeconds * 100;
                                scalarmesh.x -= deltaTimeSeconds;
                                scalarmesh.y -= deltaTimeSeconds;
                                modelStar *= transformari2D::Scale(scalarmesh.x, scalarmesh.x);
                                modelMatrix *= transformari2D::Scale(scalarmesh.y, scalarmesh.y);
                            }
                            else if (scalarmesh.x <= 0 && scalarmesh.y <= 0)
                            {
                                starPosition.y = 2000;
                                hexagonPosition.z = -85;
                            }
                        }
                        if (hexagonPosition.w == 0)
                        {
                            RenderMesh2D(meshes["star3"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 1)
                        {
                            RenderMesh2D(meshes["star4"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 2)
                        {
                            RenderMesh2D(meshes["star5"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 3)
                        {
                            RenderMesh2D(meshes["star6"], shaders["VertexColor"], modelStar);
                        }
                    }
                    if (squareElements[5].color - 1 == hexagonPosition.w && squareElements[5].exist == 1)
                    {
                        modelStar = glm::mat3(1);
                        starPosition.z += deltaTimeSeconds * 100;
                        starPosition.w -= deltaTimeSeconds;
                        modelStar *= transformari2D::Translate(starPosition.z, 250);
                        modelStar *= transformari2D::Rotate(starPosition.w);
                        if (hexagonPosition.z - outerRadius <= starPosition.z + outerRadius)
                        {
                            if (scalarmesh.x >= 0 && scalarmesh.y >= 0)
                            {
                                hexagonPosition.z += deltaTimeSeconds * 100;
                                starPosition.z -= deltaTimeSeconds * 100;
                                scalarmesh.x -= deltaTimeSeconds;
                                scalarmesh.y -= deltaTimeSeconds;
                                modelStar *= transformari2D::Scale(scalarmesh.x, scalarmesh.x);
                                modelMatrix *= transformari2D::Scale(scalarmesh.y, scalarmesh.y);
                            }
                            else if (scalarmesh.x <= 0 && scalarmesh.y <= 0)
                            {
                                starPosition.z = 2000;
                                hexagonPosition.z = -85;
                            }
                        }
                        if (hexagonPosition.w == 0)
                        {
                            RenderMesh2D(meshes["star3"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 1)
                        {
                            RenderMesh2D(meshes["star4"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 2)
                        {
                            RenderMesh2D(meshes["star5"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 3)
                        {
                            RenderMesh2D(meshes["star6"], shaders["VertexColor"], modelStar);
                        }
                    }
                    if (hexagonPosition.z <= 250 && hexagonPosition.z >= 125)
                    {
                        squareElements[3].exist = 0;
                    }
                    if (hexagonPosition.z <= 425 && hexagonPosition.z >= 300)
                    {
                        squareElements[4].exist = 0;
                    }
                    if (hexagonPosition.z <= 600 && hexagonPosition.z >= 475)
                    {
                        squareElements[5].exist = 0;
                    }
                }
                else if (hexagonPosition.x == 2)
                {
                    modelMatrix *= transformari2D::Translate(hexagonPosition.z, 430);
                    if (squareElements[6].color - 1 == hexagonPosition.w && squareElements[6].exist == 1)
                    {
                        modelStar = glm::mat3(1);
                        starPosition.x += deltaTimeSeconds * 100;
                        starPosition.w -= deltaTimeSeconds;
                        modelStar *= transformari2D::Translate(starPosition.x, 430);
                        modelStar *= transformari2D::Rotate(starPosition.w);
                        if (hexagonPosition.z - outerRadius <= starPosition.x + outerRadius)
                        {
                            if (scalarmesh.x >= 0 && scalarmesh.y >= 0)
                            {
                                hexagonPosition.z += deltaTimeSeconds * 100;
                                starPosition.x -= deltaTimeSeconds * 100;
                                scalarmesh.x -= deltaTimeSeconds;
                                scalarmesh.y -= deltaTimeSeconds;
                                modelStar *= transformari2D::Scale(scalarmesh.x, scalarmesh.x);
                                modelMatrix *= transformari2D::Scale(scalarmesh.y, scalarmesh.y);
                            }
                            else if (scalarmesh.x <= 0 && scalarmesh.y <= 0)
                            {
                                starPosition.x = 2000;
                                hexagonPosition.z = -85;
                            }
                        }
                        if (hexagonPosition.w == 0)
                        {
                            RenderMesh2D(meshes["star3"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 1)
                        {
                            RenderMesh2D(meshes["star4"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 2)
                        {
                            RenderMesh2D(meshes["star5"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 3)
                        {
                            RenderMesh2D(meshes["star6"], shaders["VertexColor"], modelStar);
                        }
                    }
                    if (squareElements[7].color - 1 == hexagonPosition.w && squareElements[7].exist == 1)
                    {
                        modelStar = glm::mat3(1);
                        starPosition.y += deltaTimeSeconds * 100;
                        starPosition.w -= deltaTimeSeconds;
                        modelStar *= transformari2D::Translate(starPosition.y, 430);
                        modelStar *= transformari2D::Rotate(starPosition.w);
                        if (hexagonPosition.z - outerRadius <= starPosition.y + outerRadius)
                        {
                            if (scalarmesh.x >= 0 && scalarmesh.y >= 0)
                            {
                                hexagonPosition.z += deltaTimeSeconds * 100;
                                starPosition.y -= deltaTimeSeconds * 100;
                                scalarmesh.x -= deltaTimeSeconds;
                                scalarmesh.y -= deltaTimeSeconds;
                                modelStar *= transformari2D::Scale(scalarmesh.x, scalarmesh.x);
                                modelMatrix *= transformari2D::Scale(scalarmesh.y, scalarmesh.y);
                            }
                            else if (scalarmesh.x <= 0 && scalarmesh.y <= 0)
                            {
                                starPosition.y = 2000;
                                hexagonPosition.z = -85;
                            }
                        }
                        if (hexagonPosition.w == 0)
                        {
                            RenderMesh2D(meshes["star3"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 1)
                        {
                            RenderMesh2D(meshes["star4"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 2)
                        {
                            RenderMesh2D(meshes["star5"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 3)
                        {
                            RenderMesh2D(meshes["star6"], shaders["VertexColor"], modelStar);
                        }
                    }
                    if (squareElements[8].color - 1 == hexagonPosition.w && squareElements[8].exist == 1)
                    {
                        modelStar = glm::mat3(1);
                        starPosition.z += deltaTimeSeconds * 100;
                        starPosition.w -= deltaTimeSeconds;
                        modelStar *= transformari2D::Translate(starPosition.z, 430);
                        modelStar *= transformari2D::Rotate(starPosition.w);
                        if (hexagonPosition.z - outerRadius <= starPosition.z + outerRadius)
                        {
                            if (scalarmesh.x >= 0 && scalarmesh.y >= 0)
                            {
                                hexagonPosition.z += deltaTimeSeconds * 100;
                                starPosition.z -= deltaTimeSeconds * 100;
                                scalarmesh.x -= deltaTimeSeconds;
                                scalarmesh.y -= deltaTimeSeconds;
                                modelStar *= transformari2D::Scale(scalarmesh.x, scalarmesh.x);
                                modelMatrix *= transformari2D::Scale(scalarmesh.y, scalarmesh.y);
                            }
                            else if (scalarmesh.x <= 0 && scalarmesh.y <= 0)
                            {
                                starPosition.z = 2000;
                                hexagonPosition.z = -85;
                            }
                        }
                        if (hexagonPosition.w == 0)
                        {
                            RenderMesh2D(meshes["star3"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 1)
                        {
                            RenderMesh2D(meshes["star4"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 2)
                        {
                            RenderMesh2D(meshes["star5"], shaders["VertexColor"], modelStar);
                        }
                        else if (hexagonPosition.w == 3)
                        {
                            RenderMesh2D(meshes["star6"], shaders["VertexColor"], modelStar);
                        }
                    }
                    if (hexagonPosition.z <= 250 && hexagonPosition.z >= 125)
                    {
                        squareElements[6].exist = 0;
                    }
                    if (hexagonPosition.z <= 425 && hexagonPosition.z >= 300)
                    {
                        squareElements[7].exist = 0;
                    }
                    if (hexagonPosition.z <= 600 && hexagonPosition.z >= 475)
                    {
                        squareElements[8].exist = 0;
                    }
                }
                //
                if (hexagonPosition.w == 0)
                {
                    RenderMesh2D(meshes["hexagon1"], shaders["VertexColor"], modelMatrix);
                }
                else if (hexagonPosition.w == 1)
                {
                    RenderMesh2D(meshes["hexagon2"], shaders["VertexColor"], modelMatrix);
                }
                else if (hexagonPosition.w == 2)
                {
                    RenderMesh2D(meshes["hexagon3"], shaders["VertexColor"], modelMatrix);
                }
                else if (hexagonPosition.w == 3)
                {
                    RenderMesh2D(meshes["hexagon4"], shaders["VertexColor"], modelMatrix);
                }
                //
                if (hexagonPosition.z <= 85 && hexagonPosition.z >= 0)
                {
                    lifes--;
                    hexagonPosition.z = -85;
                }
                if (stea1.z == 1)
                {
                    stea1.w = 0;
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transformari2D::Translate(stea1.x, stea1.y);
                    RenderMesh2D(meshes["star2"], shaders["VertexColor"], modelMatrix);
                }
                if (stea2.z == 1)
                {
                    stea2.w = 0;
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transformari2D::Translate(stea2.x, stea2.y);
                    RenderMesh2D(meshes["star2"], shaders["VertexColor"], modelMatrix);
                }
                if (stea3.z == 1)
                {
                    stea3.w = 0;
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transformari2D::Translate(stea3.x, stea3.y);
                    RenderMesh2D(meshes["star2"], shaders["VertexColor"], modelMatrix);
                }
            }

        }

    }
    for (int i = 0; i < 9; i++)
    {
        if (squareElements[i].color != 0 && squareElements[i].exist==1)
                {
            modelMatrix = glm::mat3(1);
            if (i == 0 || i == 3 || i == 6)
                x_plant = 175;
            else if (i == 1 || i == 4 || i == 7)
                x_plant = 350;
            else if(i == 2 || i == 5 || i == 8)
                x_plant = 525;
            if (i<3)
                y_plant = 75;
            else if (i>2 && i<6)
                y_plant = 250;
            else if(i>5)
                y_plant = 425;
            modelMatrix *= transformari2D::Translate(x_plant, y_plant);
                    if (squareElements[i].color == 1)
                    {
                        RenderMesh2D(meshes["romb1"], shaders["VertexColor"], modelMatrix);
                    }
                    if (squareElements[i].color == 2)
                    {
                        RenderMesh2D(meshes["romb2"], shaders["VertexColor"], modelMatrix);
                    }
                    if (squareElements[i].color == 3)
                    {
                        RenderMesh2D(meshes["romb3"], shaders["VertexColor"], modelMatrix);
                    }
                    if (squareElements[i].color == 4)
                    {
                        RenderMesh2D(meshes["romb4"], shaders["VertexColor"], modelMatrix);
                    }
                }
    }
    if (isDragging == true && mouse_romb == 1)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(mouse_moveX, mouse_moveY);
        RenderMesh2D(meshes["romb1"], shaders["VertexColor"], modelMatrix);
    }
    if (isDragging == true && mouse_romb == 2)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(mouse_moveX, mouse_moveY);
        RenderMesh2D(meshes["romb2"], shaders["VertexColor"], modelMatrix);
    }
    if (isDragging == true && mouse_romb == 3)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(mouse_moveX, mouse_moveY);  
        RenderMesh2D(meshes["romb3"], shaders["VertexColor"], modelMatrix);
    }
    if (isDragging == true && mouse_romb == 4)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformari2D::Translate(mouse_moveX, mouse_moveY);   
        RenderMesh2D(meshes["romb4"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::FrameEnd() {}

void Tema1::OnInputUpdate(float deltaTime, int mods) {}

void Tema1::OnKeyPress(int key, int mods) {}

void Tema1::OnKeyRelease(int key, int mods) {}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    mouse_moveX = mouseX;
    mouse_moveY = 720-mouseY;
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (button == 1) 
    {
        for (int i = 0; i < 100; i++)
        {
            auto& stea1 = Star1[i];
            auto& stea2 = Star2[i];
            auto& stea3 = Star3[i];
            if (stea1.w == 0 && stea2.w == 0 && stea3.w == 0)
            {
                double distance1 = sqrt(pow(mouseX - stea1.x, 2) + pow(720 - mouseY - stea1.y, 2));
                if (distance1 <= outerRadius + 15)
                {
                    stea1.z = 0;
                    if(stele_cost<10)
                        stele_cost++;
                }
                double distance2 = sqrt(pow(mouseX - stea2.x, 2) + pow(720 - mouseY - stea2.y, 2));
                if (distance2 <= outerRadius + 15)
                {
                    stea2.z = 0;
                    if (stele_cost < 10)
                        stele_cost++;
                }
                double distance3 = sqrt(pow(mouseX - stea3.x, 2) + pow(720 - mouseY - stea3.y, 2));
                if (distance3 <= outerRadius + 15)
                {
                    stea3.z = 0;
                    if (stele_cost < 10)
                        stele_cost++;
                }
            }
        }
        if ((mouseX >= 75 && mouseX <= 200) && (720 - mouseY >= 550 && 720 - mouseY <= 675) && stele_cost>0)
        {
            mouse_romb = 1;
            isDragging = true;
            stele_cost--;
        }
        else if ((mouseX >= 250 && mouseX <= 375) && (720 - mouseY >= 550 && 720 - mouseY <= 675) && stele_cost > 1)
        {
            mouse_romb = 2;
            isDragging = true;
            stele_cost-=2;
        }
        else if ((mouseX >= 425 && mouseX <= 550) && (720 - mouseY >= 550 && 720 - mouseY <= 675) && stele_cost > 1)
        {
            mouse_romb = 3;
            isDragging = true;
            stele_cost-=2;
        }
        else if ((mouseX >= 600 && mouseX <= 725) && (720 - mouseY >= 550 && 720 - mouseY <= 675) && stele_cost > 2)
        {
            mouse_romb = 4;
            isDragging = true;
            stele_cost-=3;
        }
    }
    if (button == 2 && ((mouseX >= 125 && mouseX <= 250) && (720 - mouseY >= 10 && 720 - mouseY <= 135)))//rand jos buton 1 
    {
        if (squareElements[0].exist == 1)
        {
            squareElements[0].color = 0;
            squareElements[0].exist = 0;
        }
    }
    else if (button == 2 && ((mouseX >= 300 && mouseX <= 425) && (720 - mouseY >= 10 && 720 - mouseY <= 135)))//rand jos buton 2 
    {
        if (squareElements[1].exist == 1)
        {
            squareElements[1].color = 0;
            squareElements[1].exist = 0;
        }

    }
    else if (button == 2 && ((mouseX >= 475 && mouseX <= 600) && (720 - mouseY >= 10 && 720 - mouseY <= 135)))//rand jos buton 3 
    {
        if (squareElements[2].exist == 1)
        {
            squareElements[2].color = 0;
            squareElements[2].exist = 0;
        }

    }
    else if (button == 2 && ((mouseX >= 125 && mouseX <= 250) && (720 - mouseY >= 185 && 720 - mouseY <= 310)))//rand mijloc buton 1
    {
        if (squareElements[3].exist == 1)
        {
            squareElements[3].color = 0;
            squareElements[3].exist = 0;
        }

    }
    else if (button == 2 && ((mouseX >= 300 && mouseX <= 425) && (720 - mouseY >= 185 && 720 - mouseY <= 310)))//rand mijloc buton 2 
    {
        if (squareElements[4].exist == 1)
        {
            squareElements[4].color = 0;
            squareElements[4].exist = 0;
        }

    }
    else if (button == 2 && ((mouseX >= 475 && mouseX <= 600) && (720 - mouseY >= 185 && 720 - mouseY <= 310)))//rand mijloc buton 3 
    {
        if (squareElements[5].exist == 1)
        {
            squareElements[5].color = 0;
            squareElements[5].exist = 0;
        }

    }
    else if (button == 2 && ((mouseX >= 125 && mouseX <= 250) && (720 - mouseY >= 360 && 720 - mouseY <= 485)))//rand sus buton 1 
    {
        if (squareElements[6].exist == 1)
        {
            squareElements[6].color = 0;
            squareElements[6].exist = 0;
        }

    }
    else if (button == 2 && ((mouseX >= 300 && mouseX <= 425) && (720 - mouseY >= 360 && 720 - mouseY <= 485)))//rand sus buton 2 
    {
        if (squareElements[7].exist == 1)
        {
            squareElements[7].color = 0;
            squareElements[7].exist = 0;
        }

    }
    else if (button == 2 && ((mouseX >= 475 && mouseX <= 600) && (720 - mouseY >= 360 && 720 - mouseY <= 485)))//rand sus buton 3 
    {
        if (squareElements[8].exist == 1)
        {
            squareElements[8].color = 0;
            squareElements[8].exist = 0;
        }

    }
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    if (button==1 && ((mouseX >= 125 && mouseX <= 250) && (720 - mouseY >= 10 && 720 - mouseY <= 135)) && isDragging==true)//rand jos buton 1 
    {
        if(squareElements[0].exist !=1 )
        { 
            squareElements[0].color = mouse_romb;
            squareElements[0].exist = 1;
            isDragging = false;
            mouse_romb = 0;
        }
    }
    else if (button == 1 && ((mouseX >= 300 && mouseX <= 425) && (720 - mouseY >= 10 && 720 - mouseY <= 135)) && isDragging == true)//rand jos buton 2 
    {
        if (squareElements[1].exist != 1)
        {
            squareElements[1].color = mouse_romb;
            squareElements[1].exist = 1;
            isDragging = false;
            mouse_romb = 0;
        }

    }
    else if (button == 1 && ((mouseX >= 475 && mouseX <= 600) && (720 - mouseY >= 10 && 720 - mouseY <= 135)) && isDragging == true)//rand jos buton 3 
    {
        if (squareElements[2].exist != 1)
        {
            squareElements[2].color = mouse_romb;
            squareElements[2].exist = 1;
            isDragging = false;
            mouse_romb = 0;
        }

    }
    else if (button == 1 && ((mouseX >= 125 && mouseX <= 250) && (720 - mouseY >= 185 && 720 - mouseY <= 310)) && isDragging == true)//rand mijloc buton 1
    {
        if (squareElements[3].exist != 1)
        {
            squareElements[3].color = mouse_romb;
            squareElements[3].exist = 1;
            isDragging = false;
            mouse_romb = 0;
        }

    }
    else if (button == 1 && ((mouseX >= 300 && mouseX <= 425) && (720 - mouseY >= 185 && 720 - mouseY <= 310)) && isDragging == true)//rand mijloc buton 2 
    {
        if (squareElements[4].exist != 1)
        {
            squareElements[4].color = mouse_romb;
            squareElements[4].exist = 1;
            isDragging = false;
            mouse_romb = 0;
        }

    }
    else if (button == 1 && ((mouseX >= 475 && mouseX <= 600) && (720 - mouseY >= 185 && 720 - mouseY <= 310)) && isDragging == true)//rand mijloc buton 3 
    {
        if (squareElements[5].exist != 1)
        {
            squareElements[5].color = mouse_romb;
            squareElements[5].exist = 1;
            isDragging = false;
            mouse_romb = 0;
        }

    }
    else if (button == 1 && ((mouseX >= 125 && mouseX <= 250) && (720 - mouseY >= 360 && 720 - mouseY <= 485)) && isDragging == true)//rand sus buton 1 
    {
        if (squareElements[6].exist != 1)
        {
            squareElements[6].color = mouse_romb;
            squareElements[6].exist = 1;
            isDragging = false;
            mouse_romb = 0;
        }

    }
    else if (button == 1 && ((mouseX >= 300 && mouseX <= 425) && (720 - mouseY >= 360 && 720 - mouseY <= 485)) && isDragging == true)//rand sus buton 2 
    {
        if (squareElements[7].exist != 1)
        {
            squareElements[7].color = mouse_romb;
            squareElements[7].exist = 1;
            isDragging = false;
            mouse_romb = 0;
        }

    }
    else if (button == 1 && ((mouseX >= 475 && mouseX <= 600) && (720 - mouseY >= 360 && 720 - mouseY <= 485)) && isDragging == true)//rand sus buton 3 
    {
        if (squareElements[8].exist != 1)
        {
            squareElements[8].color = mouse_romb;
            squareElements[8].exist = 1;
            isDragging = false;
            mouse_romb = 0;
        }

    }
    else if (button == 1)
    {
        isDragging = false;
        mouse_romb = 0;
    }
}
void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}
void Tema1::OnWindowResize(int width, int height) {}