#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>

using namespace std;


void travelInWidth(vector<vector<int>> graph, int start)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    stack<int> stk;
    stk.push(start);

    cout << "Width traversal:" << endl;
    while (!stk.empty()) {
        int current = stk.top();
        stk.pop();
        if (!visited[current])
        {
            cout << current << " ";
            visited[current] = true;
            for (int neighbor = 0; neighbor < n; ++neighbor)
            {
                if (graph[current][neighbor] && !visited[neighbor])
                {
                    stk.push(neighbor);
                }
            }
        }
    }
    cout << endl;
}


void travelInDepth(vector<vector<int>> graph, int start)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> que;
    que.push(start);

    cout << "Depth traversal:" << endl;
    while (!que.empty())
    {
        int current = que.front();
        que.pop();
        if (!visited[current])
        {
            cout << current << " ";
            visited[current] = true;
            for (int neighbor = 0; neighbor < n; ++neighbor)
            {
                if (graph[current][neighbor] && !visited[neighbor])
                {
                    que.push(neighbor);
                }
            }
        }
    }
    cout << endl;
}

int widthCount(vector<vector<int>>& graph, int start, int point)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<pair<int, int>> que;
    que.push({ start, 0 });
    int count = 0;

    while (!que.empty()) {
        int current = que.front().first;
        int distance = que.front().second;
        que.pop();
        if (!visited[current])
        {
            visited[current] = true;
            if (distance <= point)
            {
                count++;
                for (int neighbor = 0; neighbor < n; ++neighbor)
                {
                    if (graph[current][neighbor] && !visited[neighbor])
                    {
                        que.push({ neighbor, distance + 1 });
                    }
                }
            }
        }
    }
    return count;
}

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

int totalWeight(vector<vector<int>>& graph)
{
    int n = graph.size();
    int total = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i; j < n; ++j)
        {
            if (graph[i][j]) {
                total += graph[i][j];
            }
        }
    }
    return total;
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


int main()
{
    vector<vector<int>> matrix = readMatrixFromFile("c_matrix.txt");
    cout << "Adjacency matrix: " << endl;
    displayMatrix(matrix);
    cout << endl;

    travelInWidth(matrix, 0);
    cout << endl;
    travelInDepth(matrix, 0);

    int count = widthCount(matrix, 0, 3);
    cout << endl << "Number of vertices from 0 to 3 = " << count << endl;
    int weight = totalWeight(matrix);
    cout << "Weigth of the matrix: " << weight << endl;

    return 0;
}
