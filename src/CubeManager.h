#ifndef CUBEMANAGER_H
#define CUBEMANAGER_H

#include <map>
#include <cstdint>
#include "Cube.h"
#include "MortonNumber.h"

class CubeManager
{
public:
    CubeManager();
    ~CubeManager();

    Cube& at(int x, int y, int z);
    void clear();
    void erase(int x, int y, int z);
    bool insert(const Cube &cube);
    const std::map<MortonNumber, Cube>& getCubeMap();
    bool wasUpdated;

private:
    MortonNumber makeKey(int x, int y, int z);
    std::map<MortonNumber, Cube> cubeMap;
};

#endif
