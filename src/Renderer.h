#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

class Viewport;
class CubeManager;

class Renderer
{
public:
    Renderer();
    ~Renderer();
    void addViewport(Viewport *v);
    void addModel(CubeManager *c);
    void render();
protected:
    std::vector<Viewport *> viewports;
    std::vector<CubeManager *> models;
};

#endif
