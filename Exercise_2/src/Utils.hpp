#pragma once

#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace Polygonal_Library {

// Importing mesh, checking if files opening are successful
bool ImportMesh(const string &filepath, PolygonalMesh& mesh, double& scaling);

// Importing nodes'(0D) infos
bool ImportCell0Ds(const string &filename, PolygonalMesh& mesh);

// Importing vertices'(1D) infos
bool ImportCell1Ds(const string &filename, PolygonalMesh& mesh);

// Importing polygons'(2D) infos
bool ImportCell2Ds(const string &filename, PolygonalMesh& mesh);

// Testing if length != 0
bool LengthTest(PolygonalMesh& mesh, double& scaling);

// Testing if Area(polygon) != 0
bool AreaTest(PolygonalMesh& mesh, double& scaling);

}
