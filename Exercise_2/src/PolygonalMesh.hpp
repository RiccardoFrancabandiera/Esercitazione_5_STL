#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace Polygonal_Library {

struct PolygonalMesh
{
    // Cell 0D
    unsigned int Number0D = 0;
    vector<unsigned int> Id0D = {};
    vector<Vector2d> Coordinates0D = {};
    map<unsigned int, list<unsigned int>> Markers0D = {};

    // Cell 1D
    unsigned int Number1D = 0;
    vector<unsigned int> Id1D = {};
    vector<Vector2i> Vertices1D = {};
    map<unsigned int, list<unsigned int>> Markers1D = {};

    // Cell 2D
    unsigned int Number2D = 0;
    vector<unsigned int> Id2D = {};
    vector<VectorXi> Vertices2D = {};
    vector<VectorXi> Edges2D = {};
};

}
