#include <iostream>
#include "Renderer.h"
#include "stdgl.h"

#include "Viewport.h"
#include "Cube.h"

using namespace std;

Renderer::Renderer():
    viewports(),
    models()
{
}

Renderer::~Renderer()
{
}

void Renderer::addViewport(Viewport *v)
{
    viewports.push_back(v);
}

void Renderer::addModel(Cube *c)
{
    models.push_back(c);
}

void Renderer::render()
{
    for(vector<Viewport*>::iterator vit = viewports.begin();
        vit != viewports.end();
        vit++)
    {
        for(vector<Cube*>::iterator mit = models.begin();
            mit != models.end();
            mit++)
        {
            (*mit)->prepareDraw();
            
            // Calculate MV matrix and get projection matrix
            glm::mat4 MV   = (*vit)->getCurrentCamera().getViewMatrix() * 
                             //mit->modelMatrix;
                             glm::mat4();
            glm::mat4 proj = (*vit)->getCurrentCamera().getProjectionMatrix();

            // Set uniforms
            GLint mvLoc   = glGetUniformLocation((*mit)->program, "modelView");
            GLint nmvLoc  = glGetUniformLocation((*mit)->program, "normalModelView");
            GLint projLoc = glGetUniformLocation((*mit)->program, "projection");

            if(mvLoc != -1)
            {
                glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &MV[0][0]);
            }
            else
            {
                cerr << "Error: Cannot find modelView location" << endl;
                return;
            }

            if(nmvLoc != -1)
            {
                glUniformMatrix4fv(nmvLoc, 1, GL_FALSE,
                    &glm::transpose(glm::inverse(MV))[0][0]);
            }
            else
            {
                cerr << "Error: Cannot find normalModelView location" << endl;
                return;
            }
            
            if(projLoc != -1)
            {
                glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);
            }
            else
            {
                cerr << "Error: Cannot find projection location" << endl;
                return;
            }
            (*mit)->draw();
        }
    }
}
