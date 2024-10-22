#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> 

using namespace std;

class Graph {
public:
    int vertices;
    vector<vector<int>> adj;

    Graph(int V) : vertices(V), adj(V) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    pair<int, vector<int>> shortestCycle() {
        int shortest = adj.size();
        vector<int> cycle;

        for (int i = 0; i < vertices; ++i) {
            vector<int> distance(vertices, -1);
            vector<int> parent(vertices, -1);
            distance[i] = 0;

            dfs(i, i, distance, parent, shortest, cycle);
        }

        if (shortest == adj.size()) {
            return make_pair(-1, vector<int>());
        }
        else {
            return make_pair(shortest, cycle);
        }
    }

private:
    void dfs(int start, int current, vector<int>& distance, vector<int>& parent, int& shortest, vector<int>& cycle) {
        for (int i = 0; i < adj[current].size(); ++i) {
            int neighbor = adj[current][i];

            if (distance[neighbor] == -1) {
                distance[neighbor] = distance[current] + 1;
                parent[neighbor] = current;
                dfs(start, neighbor, distance, parent, shortest, cycle);
            }
            else if (neighbor != parent[current] && neighbor == start) {
                
                int cycleLength = distance[current] - distance[neighbor] + 1;

                if (cycleLength < shortest) {
                    shortest = cycleLength;

                    
                    cycle.clear();
                    int node = current;
                    while (node != start) {
                        cycle.push_back(node);
                        node = parent[node];
                    }
                    cycle.push_back(start);
                }
            }
        }
    }
};

int main() {
    ifstream inputFile("testcase3.txt");

    if (!inputFile.is_open()) {
        cout << "Error opening the file!" << endl;
        return 1;
    }

    string verticesLine;
    getline(inputFile, verticesLine);

    stringstream verticesStream(verticesLine);
    int vertices;
    verticesStream >> vertices;

    cout << "Vertices: " << vertices << endl;
    
    Graph graph(vertices);


    int conn = 0; 

    while (inputFile) { 
        string line; 
        getline(inputFile, line); 
        if (line.empty()) break; 
        stringstream ss(line); 
        int u, v; 
        ss >> u >> v; 
        graph.addEdge(u, v); 
        cout << u << " " << v << endl;
        conn++;
    }

    int expectedOutput;
    inputFile >> expectedOutput;

    pair<int, vector<int>> result = graph.shortestCycle();

    int j = result.second.size() - 1;
    if (result.first == expectedOutput) {
        cout << "Test Passed" << endl;
        if (result.first != -1) {
            cout << "Resulting Cycle: ";
            for (int i = result.second.size() - 1; i >= 0; --i) {
                cout << result.second[i];
                if (i > 0) cout << " -> ";
            }
            cout << " -> " << result.second[j];
        }
        else {
            cout << "NO CYCLE DETECTED." << endl;
        }
        cout << endl;
    }
    else {
        cout << "Test Failed" << endl;
    }

    cout << "Number of Connections: " << conn << endl; 

    inputFile.close();

    return 0;
}
