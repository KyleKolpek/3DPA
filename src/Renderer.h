#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

class Viewport;
class Cube;

class Renderer
{
public:
    Renderer();
    ~Renderer();
    void addViewport(Viewport *v);
    void addModel(Cube *c);
    void render();
protected:
    std::vector<Viewport *> viewports;
    std::vector<Cube *> models;
};

#endif
