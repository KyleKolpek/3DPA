#ifndef CUBEMANAGER_H
#define CUBEMANAGER_H

#include <map>
#include <cstdint>
#include "Cube.h"
#include "Drawable.h"
#include "MortonNumber.h"

class CubeManager: public Drawable
{
public:
    CubeManager();
    ~CubeManager();

    Cube& at(int x, int y, int z);
    void clear();
    void erase(int x, int y, int z);
    bool insert(const Cube &cube);
    void populateModelData();
    void draw(GLuint program);
    GLuint loadShader();

private:
    struct CubePosColor
    {
        float position[3];
        float color[3];
    };
    MortonNumber makeKey(int x, int y, int z);
    std::map<MortonNumber, Cube> cubeMap;
    static float vertexData[];
    static int vertexCount;
    GLuint vertexBuffer;
    GLuint instanceBuffer;
    bool needsUpdated;
};

#endif
