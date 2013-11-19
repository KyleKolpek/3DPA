/*
 * This source file is part of libRocket, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://www.librocket.com
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "SDLRenderInterface.h"
#include <Rocket/Core.h>
#include "SOIL2/SOIL2.h"
#include "../../ShaderManager.h"
#include <iostream>

#define GL_CLAMP_TO_EDGE 0x812F

SDLRenderInterface::SDLRenderInterface()
{
}

void SDLRenderInterface::SetViewport(int width, int height)
{
    m_width = width;
    m_height = height;
}

void SDLRenderInterface::SetShaderManager(ShaderManager *sm)
{
    shaderManager = sm;
}


// Called by Rocket when it wants to render geometry that it does not wish to optimise.
void SDLRenderInterface::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, const Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation)
{
    
    // TODO: Check glGetAttribLocation calls for success

    GLuint program;
    GLuint vertexBuffer;
    GLuint vertexPosLoc   = 0;
    GLuint vertexColorLoc = 0;
    GLuint texCoordLoc    = 0;
    GLuint texSamplerLoc  = 0;
    GLuint translationLoc = 0;

    // Populate vertex buffer
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Rocket::Core::Vertex) * num_vertices,
                 vertices, GL_STATIC_DRAW);

    // Handle textures
	if (!texture)
	{
        program = shaderManager->getProgram(2, "rocketNoTex.vert",
                                               "rocketNoTex.frag");
        glUseProgram(program);
	}
	else
	{
        program = shaderManager->getProgram(2, "rocketTex.vert",
                                               "rocketTex.frag");
        glUseProgram(program);
        
        // Set up the texture
        texSamplerLoc = glGetUniformLocation(program, "texture");
        if(texSamplerLoc == -1)
        {
            std::cerr << "Error: cannot find texture location." << std::endl;
            return;
        }

        glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, (GLuint) texture);
        glUniform1i(texSamplerLoc, 0);
        
        // Set up the per vertex texture coords 
        texCoordLoc = glGetAttribLocation(program, "vertexTexCoord");
        if(texCoordLoc == -1)
        {
            std::cerr << "Error: cannot find texture coord location."
                      << std::endl;
            return;
        }
        glEnableVertexAttribArray(texCoordLoc);
        glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE,
                              sizeof(Rocket::Core::Vertex),
                              (void*) (sizeof(Rocket::Core::Vector2f) +
                              sizeof(Rocket::Core::Colourb)));
	}

    translationLoc = glGetUniformLocation(program, "translation");
    glUniform2f(translationLoc, translation.x, translation.y);

    // Draw the geometry
    vertexPosLoc = glGetAttribLocation(program, "vertexPosition");
    if(vertexPosLoc == -1)
    {
        std::cerr << "Error: cannot find vertex position location."
                  << std::endl;
        return;
    }

    vertexColorLoc = glGetAttribLocation(program, "vertexColor");
    if(vertexColorLoc == -1)
    {
        std::cerr << "Error: cannot find vertex color location."
                  << std::endl;
        return;
    }
    
    glEnableVertexAttribArray(vertexPosLoc);
    glEnableVertexAttribArray(vertexColorLoc);

    glVertexAttribPointer(vertexPosLoc, 2, GL_FLOAT, GL_FALSE,
                              sizeof(Rocket::Core::Vertex), 0);
    glVertexAttribPointer(vertexColorLoc, 4, GL_UNSIGNED_BYTE, GL_TRUE,
                              sizeof(Rocket::Core::Vertex),
                              (void*) sizeof(Rocket::Core::Vector2f));
    
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, indices);

    glDisableVertexAttribArray(vertexPosLoc);
    glDisableVertexAttribArray(vertexColorLoc);
    glDisableVertexAttribArray(texCoordLoc);
    glDeleteBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);

}

// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.		
Rocket::Core::CompiledGeometryHandle SDLRenderInterface::CompileGeometry(Rocket::Core::Vertex* ROCKET_UNUSED(vertices), int ROCKET_UNUSED(num_vertices), int* ROCKET_UNUSED(indices), int ROCKET_UNUSED(num_indices), const Rocket::Core::TextureHandle ROCKET_UNUSED(texture))
{
	return (Rocket::Core::CompiledGeometryHandle) NULL;
}

// Called by Rocket when it wants to render application-compiled geometry.		
void SDLRenderInterface::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle ROCKET_UNUSED(geometry), const Rocket::Core::Vector2f& ROCKET_UNUSED(translation))
{
}

// Called by Rocket when it wants to release application-compiled geometry.		
void SDLRenderInterface::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle ROCKET_UNUSED(geometry))
{
}

// Called by Rocket when it wants to enable or disable scissoring to clip content.		
void SDLRenderInterface::EnableScissorRegion(bool enable)
{
	if (enable)
		glEnable(GL_SCISSOR_TEST);
	else
		glDisable(GL_SCISSOR_TEST);
}

// Called by Rocket when it wants to change the scissor region.		
void SDLRenderInterface::SetScissorRegion(int x, int y, int width, int height)
{
	glScissor(x, m_height - (y + height), width, height);
}

// Called by Rocket when a texture is required by the library.		
bool SDLRenderInterface::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
{
    std::cout << "Texture source: " << source.CString() << std::endl;
    
    texture_handle = (Rocket::Core::TextureHandle) SOIL_load_OGL_texture(
        source.CString(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS       | SOIL_FLAG_INVERT_Y | 
        SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

    return (bool)texture_handle;
}

// Called by Rocket when a texture is required to be built from an internally-generated sequence of pixels.
bool SDLRenderInterface::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
{
	GLuint texture_id = 0;
	glGenTextures(1, &texture_id);
	if (texture_id == 0)
	{
		printf("Failed to generate textures\n");
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, source_dimensions.x, source_dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, source);

	texture_handle = (Rocket::Core::TextureHandle) texture_id;

	return (bool)texture_handle;
}

// Called by Rocket when a loaded texture is no longer required.		
void SDLRenderInterface::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
{
	glDeleteTextures(1, (GLuint*) &texture_handle);
}

