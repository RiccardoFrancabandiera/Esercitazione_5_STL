#include <iostream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"

using namespace std;
using namespace Polygonal_Library;

int main()
{
    // Defining name for mesh structure
    PolygonalMesh mesh;

    // Filepath for mesh files
    string filepath = "PolygonalMesh";

    // Defining the scaling used for the epsilon, for tollerance purpose
    double scaling = 10;

    if(!ImportMesh(filepath, mesh, scaling))
    {
        cerr << "Error importing mesh" << endl;
        return 1;
    }

    return 0;
}
