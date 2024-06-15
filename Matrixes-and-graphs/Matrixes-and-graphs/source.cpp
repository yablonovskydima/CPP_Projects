#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include <set>
#include <utility>
#include <limits>

using namespace std;


vector<vector<int>> readMatrixFromFile(const string& filename)
{
    ifstream file(filename);
    vector<vector<int>> matrix;

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            vector<int> row;
            istringstream iss(line);
            int val;
            while (iss >> val)
            {
                row.push_back(val);
            }
            matrix.push_back(row);
        }
        file.close();
    }
    else
    {
        cerr << "Unable to open file " << filename << endl;
    }

    return matrix;
}

void displayMatrix(const vector<vector<int>> matrix)
{
    for (const auto& row : matrix)
    {
        for (int val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> toIncidence(vector<vector<int>> adjacencyMatrix)
{
    vector<vector<int>> incidenceMatrix;

    int numVertices = adjacencyMatrix.size();
    int numEdges = 0;
    for (const auto& row : adjacencyMatrix)
    {
        for (int val : row)
        {
            if (val == 1)
            {
                numEdges++;
            }
        }
    }
    numEdges /= 2;

    incidenceMatrix.resize(numVertices);
    for (int i = 0; i < numVertices; ++i)
    {
        incidenceMatrix[i].resize(numEdges);
    }

    int edgeIndex = 0;
    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j < numVertices; ++j)
        {
            if (adjacencyMatrix[i][j] == 1)
            {
                incidenceMatrix[i][edgeIndex] = 1;
                incidenceMatrix[j][edgeIndex] = 1;
                edgeIndex++;
                if (edgeIndex >= numEdges)
                    break;
            }
        }
        if (edgeIndex >= numEdges)
            break;
    }

    return incidenceMatrix;
}

vector<vector<int>> toAdjacency(vector<vector<int>> incidenceMatrix) {
    vector<vector<int>> adjacencyMatrix;

    int numVertices = incidenceMatrix.size();
    int numEdges = incidenceMatrix[0].size();

    adjacencyMatrix.resize(numVertices);
    for (int i = 0; i < numVertices; ++i)
    {
        adjacencyMatrix[i].resize(numVertices);
    }

    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = i + 1; j < numVertices; ++j)
        {
            for (int k = 0; k < numEdges; ++k)
            {
                if (incidenceMatrix[i][k] == 1 && incidenceMatrix[j][k] == 1)
                {
                    adjacencyMatrix[i][j] = 1;
                    adjacencyMatrix[j][i] = 1;
                    break;
                }
            }
        }
    }

    return adjacencyMatrix;
}

vector<pair<int, int>> edgeListFromAdjacency(vector<vector<int>> adjacencyMatrix)
{
    vector<pair<int, int>> edgeList;

    int numVertices = adjacencyMatrix.size();

    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = i + 1; j < numVertices; ++j)
        {
            if (adjacencyMatrix[i][j] == 1)
            {
                edgeList.push_back(make_pair(i, j));
            }
        }
    }

    return edgeList;
}

void printEdgeList(const vector<pair<int, int>> edgeList)
{
    for (const auto& edge : edgeList)
    {
        cout << "{" << edge.first << ", " << edge.second << "}\n";
    }
}

vector<pair<int, int>> algorithPrima(vector<vector<int>> adjacencyMatrix) {
    int numVertices = adjacencyMatrix.size();


    vector<pair<int, int>> mst;
    vector<bool> visited(numVertices, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    visited[0] = true;
    for (int j = 0; j < numVertices; ++j)
    {
        if (adjacencyMatrix[0][j] > 0) {
            pq.push(make_pair(adjacencyMatrix[0][j], j));
        }
    }

    while (!pq.empty())
    {
        auto edge = pq.top();
        pq.pop();
        int u = edge.second;
        if (visited[u]) continue;
        visited[u] = true;
        mst.push_back(make_pair(0, u));
        for (int v = 0; v < numVertices; ++v)
        {
            if (adjacencyMatrix[u][v] > 0 && !visited[v])
            {
                pq.push(make_pair(adjacencyMatrix[u][v], v));
            }
        }
    }

    return mst;
}

void printTree(vector<pair<int, int>> mst)
{
    for (const auto& edge : mst)
    {
        cout << "{" << edge.first << ", " << edge.second << "}\n";
    }
}

int main()
{
    cout << "Incidence matrix: " << endl;
    vector<vector<int>> matrixI = readMatrixFromFile("i_matrix.txt");
    displayMatrix(matrixI);

    cout << endl;
    cout << "Adjacency matrix: " << endl;
    vector<vector<int>> matrixA = readMatrixFromFile("c_matrix.txt");
    displayMatrix(matrixA);

    cout << endl << "From icidency to adjacency" << endl;
    vector<vector<int>> a = toAdjacency(matrixI);
    displayMatrix(a);


    cout << endl << "From adjacency to icidency" << endl;
    vector<vector<int>> i = toIncidence(matrixA);
    displayMatrix(i);


    vector<pair<int, int>> edgeList = edgeListFromAdjacency(a);
    printEdgeList(edgeList);
    cout << endl;

    cout << endl << "Base tree from adjacency matrix: " << endl;
    vector<pair<int, int>> baseTree = algorithPrima(matrixA);
    printTree(baseTree);

    return 0;
}
