#include <iostream>
#include <ctime>
#include <cstdlib>
#include "CubeGenerator.h"
#include "CubeManager.h"
#include "Rocket/Controls.h"

using namespace std;

CubeGenerator::CubeGenerator():
    position(0.0, 0.0, 0.0),
    cubeManager(NULL)
{
    srand(time(NULL));
}

CubeGenerator::~CubeGenerator()
{
}

void CubeGenerator::moveTo(const glm::vec3 &position)
{
    this->position = position;
}

void CubeGenerator::addCube()
{
    Cube c ={static_cast<int>(glm::floor(position.x)),
             static_cast<int>(glm::floor(position.y)),
             static_cast<int>(glm::ceil(position.z)),
             colorGetter.getRed(),
             colorGetter.getGreen(),
             colorGetter.getBlue(),
             /*float(rand())/float(RAND_MAX),
             float(rand())/float(RAND_MAX),
             float(rand())/float(RAND_MAX),*/
             1.0f,
             1};

    cubeManager->insert(c);
}

void CubeGenerator::removeCube()
{
    cubeManager->erase(glm::floor(position.x),
                       glm::floor(position.y),
                       glm::ceil(position.z));
}

glm::vec3 CubeGenerator::getPosition()
{
    return position;
}

void CubeGenerator::setCubeManager(CubeManager *cubeManager)
{
    this->cubeManager = cubeManager;
}

void CubeGenerator::attachListener(Rocket::Core::Element *element)
{
        static_cast<Rocket::Controls::ElementFormControlInput *>
                    (element->GetElementById("red"))->
                    AddEventListener("change", &colorGetter);
        static_cast<Rocket::Controls::ElementFormControlInput *>
                    (element->GetElementById("green"))->
                    AddEventListener("change", &colorGetter);
        static_cast<Rocket::Controls::ElementFormControlInput *>
                    (element->GetElementById("blue"))->
                    AddEventListener("change", &colorGetter);
}
