#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <limits>

using namespace std;
namespace Polygonal_Library {

bool ImportMesh(const string& filepath, PolygonalMesh& mesh, double& scaling)
{

    if(!ImportCell0Ds(filepath + "/Cell0Ds.csv", mesh))
    {
        cerr << "Error importing 0D cells" << endl;
        return false;
    }
    else
    {
        // Testing if markers have been stored correctly
        cout << "Markers Test 0D" << endl;
        cout << "Cell0D Markers: " << endl;
        for(auto iterator = mesh.Markers0D.begin(); iterator != mesh.Markers0D.end(); iterator++)
        {
            cout << "Key: " << iterator -> first << "  " << "Values: ";
            for(const unsigned int id : iterator -> second)
            {
                cout << " " << id;
            }
            cout << endl;
        }
        cout << endl;
    }

    if(!ImportCell1Ds(filepath + "/Cell1Ds.csv", mesh))
    {
        cerr << "Error importing 1D cells" << endl;
        return false;
    }
    else
    {
        // Testing if markers have been stored correctly
        cout << "Markers Test 1D" << endl;
        cout << "Cell1D Markers: " << endl;
        for(auto iterator = mesh.Markers1D.begin(); iterator != mesh.Markers1D.end(); iterator++)
        {
            cout << "Key: " << iterator -> first << "  " << "Values: ";
            for(const unsigned int id : iterator -> second)
            {
                cout << " " << id;
            }
            cout << endl;
        }
        cout << endl;
    }

    // Testing if there are 0 length sides
    cout << "Length Test" << endl;
    if(!LengthTest(mesh, scaling))
    {
        return false;
    }
    cout << "Length Test passed" << endl;

    if(!ImportCell2Ds(filepath + "/Cell2Ds.csv", mesh))
    {
        cerr << "Error importing 2D cells" << endl;
        return false;
    }

    cout << "Area Test" << endl;
    if(!AreaTest(mesh, scaling))
    {
        return false;
    }
    cout << "Area Test passed" << endl;
}

bool ImportCell0Ds(const string &filename, PolygonalMesh& mesh)
{

    ifstream file;
    file.open(filename);

    // Checking correct file opening
    if(file.fail())
    {
        return false;
    }
    // Saving datas as type string in a list
    list<string> listLines;
    string line;
    while (getline(file, line))
    {
        listLines.push_back(line);
    }

    // Used to get rid of the first line (first string of the list)
    listLines.pop_front();

    mesh.Number0D = listLines.size();

    if (mesh.Number0D == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    // Knowing the number of cells, I can set up the memory needed for the Id and the Coordinates
    mesh.Id0D.reserve(mesh.Number0D);
    mesh.Coordinates0D.reserve(mesh.Number0D);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2d coord;
        char a;

        converter >> id >> a >> marker >> a >> coord(0) >> a >> coord(1);

        mesh.Id0D.push_back(id);
        mesh.Coordinates0D.push_back(coord);

        // If my marker == 0, my 0D cell is not on the edge of the mesh, so I don't save in memory marker and id; if I am on the edge, I save marker and id
        if( marker != 0)
        {
            auto ret = mesh.Markers0D.insert({marker, {id}});
            // If the key is already there, add the id value
            if(!ret.second)
            {
                (ret.first)->second.push_back(id);
            }
        }

    }
    file.close();

    return true;
}

bool ImportCell1Ds(const string &filename, PolygonalMesh& mesh)
{

    ifstream file;
    file.open(filename);

    // Checking correct file opening
    if(file.fail())
    {
        return false;
    }
    list<string> listLines;
    string line;
    while (getline(file, line))
    {
        listLines.push_back(line);
    }
    // Used to get rid of the first line (first string of the list)
    listLines.pop_front();

    mesh.Number1D = listLines.size();

    if (mesh.Number1D == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    // Knowing the number of cells, I can set up the memory needed for the Id and the Coordinates
    mesh.Id1D.reserve(mesh.Number1D);
    mesh.Vertices1D.reserve(mesh.Number1D);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2i vertices;
        char b;

        converter >>  id >> b >> marker >> b >> vertices(0) >> b >> vertices(1);

        mesh.Id1D.push_back(id);
        mesh.Vertices1D.push_back(vertices);

        // If my marker == 0, my 0D cell is not on the edge of the mesh, so I don't save in memory marker and id; if I am on the edge, I save marker and id
        if( marker != 0)
        {
            auto ret = mesh.Markers1D.insert({marker, {id}});
            // If the key is already there, add the id value
            if(!ret.second)
            {
                (ret.first)->second.push_back(id);
            }
        }
    }

    file.close();

    return true;
}

bool ImportCell2Ds(const string &filename, PolygonalMesh& mesh)
{

    ifstream file;
    file.open(filename);

    if(file.fail())
    {
        return false;
    }
    list<string> listLines;
    string line;
    while (getline(file, line))
    {
        listLines.push_back(line);
    }

    listLines.pop_front();

    mesh.Number2D = listLines.size();

    if (mesh.Number2D == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }

    mesh.Id2D.reserve(mesh.Number2D);
    mesh.Vertices2D.reserve(mesh.Number2D);
    mesh.Edges2D.reserve(mesh.Number2D);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int sizeVertices;
        unsigned int sizeEdges;
        VectorXi vertices;
        VectorXi edges;
        string str;

        getline(converter , str, ';');
        istringstream(str) >> id;

        // All markers are = 0 so they are useless
        getline(converter, str, ';');

        getline(converter, str , ';');
        istringstream(str) >> sizeVertices;
        vertices.resize(sizeVertices);


        for(unsigned int i = 0; i < sizeVertices; i++)
        {
            getline(converter, str, ';');
            istringstream(str) >> vertices[i];
        }

        getline(converter, str, ';');
        istringstream(str) >> sizeEdges;
        edges.resize(sizeEdges);

        for(unsigned int i = 0; i < sizeEdges; i++)
        {
            getline(converter, str, ';');
            istringstream(str) >> edges[i];
        }

        mesh.Id2D.push_back(id);
        mesh.Vertices2D.push_back(vertices);
        mesh.Edges2D.push_back(edges);
    }
    file.close();

    return true;
}
bool LengthTest(PolygonalMesh& mesh, double &scaling)
{
    double tollLength = numeric_limits<double>::epsilon()*scaling;

    for(const auto& points : mesh.Vertices1D)
    {
        Vector2d coord_1 = mesh.Coordinates0D[points(0)];
        Vector2d coord_2 = mesh.Coordinates0D[points(1)];
        if(abs(coord_1(0)-coord_2(0)) < tollLength && abs(coord_1(1)-coord_2(1)) < tollLength)
        {
            cerr << "Error occurring: 0 length sides " << endl;
            return false;
        }
    }
    return true;
}
bool AreaTest(PolygonalMesh& mesh, double &scaling)
{
    double tollArea = numeric_limits<double>::epsilon()*scaling;

    for(const auto& edges : mesh.Edges2D)
    {
        // Considering the line passing through two points of the polygon
        Vector2i side1 = mesh.Vertices1D[edges(0)];
        Vector2d point1 = mesh.Coordinates0D[side1(0)];
        Vector2d point2 = mesh.Coordinates0D[side1(1)];
        // y = mx + q
        double m = (point2[1] - point1[1]) / (point2[0] - point1[0]);
        double q = point2[0] - m*point1[0];

        // Are the other points on the same line of the first two?
        bool onTheSameLine = true;
        for (size_t i = 2; i < edges.size(); ++i) {
            Vector2i sidei = mesh.Vertices1D[edges(i)];
            Vector2d pointi = mesh.Coordinates0D[sidei(0)];

            double y = m*pointi[0] + q ;


            if (pointi[1] - y != tollArea)
            {
                onTheSameLine = false;
                break;
            }
        }

        if (onTheSameLine)
        {
            cout << "Error occurring: there are 0 polygons" << endl;
        }

    }
    return true;
}

}
