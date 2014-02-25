#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

class Viewport;
class Model;

class Renderer
{
public:
    Renderer();
    ~Renderer();
    void addViewport(Viewport *vp);
    void addModel(Model *model);
    void render();
protected:
    std::vector<Viewport *> viewports;
    std::vector<Model *> models;
};

#endif
