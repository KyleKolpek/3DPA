#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

class Viewport;
class Drawable;

class Renderer
{
public:
    Renderer();
    ~Renderer();
    void addViewport(Viewport *v);
    void addModel(Drawable *d);
    void render();
protected:
    std::vector<Viewport *> viewports;
    std::vector<Drawable *> models;
};

#endif
