#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

map<string, int> path_times;

bool isWhitespaceOrEmpty(const string& line) {
    for (char ch : line) {
        if (!std::isspace(static_cast<unsigned char>(ch))) {
            return false;
        }
    }
    return true;
}
// Function to calculate the total travel time for a given path
int calculatePathTime(const string& path) {
    stringstream ss(path);
    string node;
    vector<string> nodes;

    // Split the path into nodes
    while (getline(ss, node, '-')) {
        nodes.push_back(node);
    }

    int totalTime = 0;
    for (size_t i = 0; i < nodes.size() - 1; ++i) {
        string key = nodes[i] + "-" + nodes[i + 1];
        auto it = path_times.find(key);
        if (it != path_times.end()) {
            totalTime += it->second;
        } else {
            cerr << "No distance found for path segment: " << key << endl;
            return -1;
        }
    }

    return totalTime;
}

int main() {
    ifstream file("testcase1.txt"); // Replace with your input file name
    if (!file) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    bool readingPathTimes = true;
    vector<string> pathsToCalculate;
    int total = 0;
    int validPathsCount = 0;

    while (getline(file, line)) {
        if (isWhitespaceOrEmpty(line)) {
            readingPathTimes = false;
            continue;
        }

        stringstream ss(line);
        if (readingPathTimes) 
        {
            string nodes;
            int time;
            if (ss >> nodes >> time) 
            {
                path_times[nodes] = time;
                string reverse_nodes = string(1, nodes[2]) + "-" + string(1, nodes[0]);
                path_times[reverse_nodes] = time;
            }
        } 
        else {
            string path;
            if (ss >> path) 
            {
               if (!isdigit(path[0]) && !isWhitespaceOrEmpty(path))
                pathsToCalculate.push_back(path);
            }
        }
    }

    for (const auto& path : pathsToCalculate) 
    {
        int time = calculatePathTime(path);
        if (time != -1) {
            cout << "Travel time for path " << path << ": " << time << " minutes" << endl;
            total += time;
            validPathsCount++;
        }
    }

    file.close();

    double average = validPathsCount > 0 ? static_cast<double>(total) / validPathsCount : 0.0;
    cout << "Average time for the given paths: " << average << " minutes" << endl;

    return 0;
}