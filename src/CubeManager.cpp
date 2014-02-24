#include "CubeManager.h"
#include <iostream>

using namespace std;

CubeManager::CubeManager():
    wasUpdated(false)
{
}

CubeManager::~CubeManager()
{
}

bool CubeManager::insert(const Cube& cube)
{
    wasUpdated = true;
    return cubeMap.insert(
               make_pair(makeKey(cube.x, cube.y, cube.z), cube)).second;
}

void CubeManager::erase(int x, int y, int z)
{
    wasUpdated = true;
    cubeMap.erase(makeKey(x, y, z));
}

void CubeManager::clear()
{
    wasUpdated = true;
    cubeMap.clear();
}

Cube& CubeManager::at(int x, int y, int z)
{
    return cubeMap.at(makeKey(x,y,z));
}

const map<MortonNumber, Cube>& getCubeMap()
{
    return cubeMap;
}

// Assumes we are fitting three 21 bit integers into a >63 bit type
// 2^21 = 2097152
MortonNumber CubeManager::makeKey(int x, int y, int z)
{
    return MortonNumber(x,y,z);
}
