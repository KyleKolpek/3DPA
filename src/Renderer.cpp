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
            glUseProgram((*mit)->modelData.shaderProgram);

            // Calculate MV matrix and get projection matrix
            glm::mat4 MV   = (*vit)->getCurrentCamera().getViewMatrix() * 
                             (*mit)->modelMatrix;
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
            for(vector<VertexAttribute>::iterator vit =
                    (*mit)->modelData.vertexAttribs.begin();
                vit != (*mit)->modelData.vertexAttribs.end();
                vit++)
            {
                glEnableVertexAttribArray((*vit).index);
                glVertexAttribPointer((*vit).index,  (*vit).size,
                                      (*vit).type,   (*vit).normalized,
                                      (*vit).stride, (*vid).pointer);
                glVertexAttribDivisor((*vit).index, (*vit).divisor);
            }
            
            // Draw
            glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0,
                                  (*mit)->modelData.vertexCount,
                                  (*mit)->instanceCount);

            // Unset attributes that may interfere elsewhere.
            for(vector<VertexAttribute>::iterator vit =
                    (*mit)->modelData.vertexAttribs.begin();
                vit != (*mit)->modelData.vertexAttribs.end();
                vit++)
            {
                glDisableVertexAttribArray((*vit).index);
                glVertexAttribDivisor((*vit).index, 0);
            }
            // END DRAW
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glUseProgram(0);
        }
    }
}
