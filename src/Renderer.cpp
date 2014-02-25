#include <iostream>
#include "Renderer.h"
#include "stdgl.h"

#include "Viewport.h"
#include "Model.h"

using namespace std;

Renderer::Renderer():
    viewports(),
    models()
{
}

Renderer::~Renderer()
{
}

void Renderer::addViewport(Viewport *vp)
{
    viewports.push_back(vp);
}

void Renderer::addModel(Model *model)
{
    models.push_back(model);
}

void Renderer::render()
{
    for(vector<Viewport*>::iterator vit = viewports.begin();
        vit != viewports.end();
        vit++)
    {
        for(vector<Model*>::iterator mit = models.begin();
            mit != models.end();
            mit++)
        {
            GLuint program = (*mit)->modelData.shaderProgram;
            glUseProgram(program);

            // Calculate MV matrix and get projection matrix
            glm::mat4 MV   = (*vit)->getCurrentCamera().getViewMatrix() * 
                             (*mit)->getModelMatrix();
            glm::mat4 proj = (*vit)->getCurrentCamera().getProjectionMatrix();

            // Set uniforms
            GLint mvLoc   = glGetUniformLocation(program, "modelView");
            GLint nmvLoc  = glGetUniformLocation(program, "normalModelView");
            GLint projLoc = glGetUniformLocation(program, "projection");
            if(mvLoc != -1)
            {
                glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &MV[0][0]);
            }
            if(nmvLoc != -1)
            {
                glUniformMatrix4fv(nmvLoc, 1, GL_FALSE,
                    &glm::transpose(glm::inverse(MV))[0][0]);
            }
            if(projLoc != -1)
            {
                glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);
            }

            glBindBuffer(GL_ARRAY_BUFFER, (*mit)->modelData.vertexBuffer);

            // Set up vertex attributes.
            for(const VertexAttribute& vait : (*mit)->modelData.vertexAttribs)
            {
                glEnableVertexAttribArray(vait.index);
                glVertexAttribPointer(vait.index,  vait.size,
                                      vait.type,   vait.normalized,
                                      vait.stride, vait.pointer);
                glVertexAttribDivisor(vait.index, vait.divisor);
            }
            
            // Draw
            glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0,
                                  (*mit)->modelData.vertexCount,
                                  (*mit)->instanceCount);

            // Unset attributes that may interfere elsewhere.
            for(const VertexAttribute& vait : (*mit)->modelData.vertexAttribs)
            {
                glDisableVertexAttribArray(vait.index);
                glVertexAttribDivisor(vait.index, 0);
            }
            // END DRAW
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glUseProgram(0);
        }
    }
}
