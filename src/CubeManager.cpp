#include "CubeManager.h"
#include "Model.h"
#include "ModelData.h"

CubeManager::CubeManager()
{
}

CubeManager::~CubeManager()
{
}

bool CubeManager::insert(Cube& cube)
{
    return cubeMap.insert(
               std::make_pair(makeKey(cube.x, cube.y, cube.z), cube)).second;
}

void CubeManager::erase(int x, int y, int z)
{
    cubeMap.erase(makeKey(x, y, z));
}

void CubeManager::clear()
{
    cubeMap.clear();
}

Cube& CubeManager::at(int x, int y, int z)
{
    return cubeMap.at(makeKey(x,y,z));
}

void CubeManager::populateModelData()
{
   //float *vertexData = new float[];
   // for each cube

}

// Assumes we are fitting three 21 bit integers into a >63 bit type
// 2^21 = 2097152
MortonNumber CubeManager::makeKey(int x, int y, int z)
{
    return MortonNumber(x,y,z);
}
