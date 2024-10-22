#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

bool isWhitespaceOrEmpty(const string &line)
{
    for (int i = 0; i < line.length(); ++i)
    {
        char ch = line[i];
        if (ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r')
        {
            return false;
        }
    }
    return true;
}

bool checkDiagonal(const vector<vector<char>> &text, int startX, int startY, const vector<vector<char>> &pattern)
{
    for (int i = 0; i < pattern.size(); ++i)
    {
        for (int j = 0; j < pattern[i].size(); ++j)
        {
            if (text[startX + i][startY + j] != pattern[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

int findDiagonalOccurrences(const vector<vector<char>> &text, const vector<vector<char>> &pattern)
{
    int occurrences = 0;
    int n = text.size();
    int m = pattern.size();

    for (int x = 0; x <= n - m; ++x)
    {
        for (int y = 0; y <= n - m; ++y)
        {
            if (checkDiagonal(text, x, y, pattern))
            {
                occurrences++;
                x += m - 1;
                y += m - 1;
            }
        }
    }

    return occurrences;
}

int main()
{
    ifstream file("1.txt");

    if (!file.is_open())
    {
        cout << "Unable to open the file." << endl;
        return 1;
    }

    string firstLine;
    int size = 0;

    if (getline(file, firstLine))
    {
        char temp;
        stringstream ss(firstLine);
        ss >> temp >> temp >> size >> temp;
    }

    char ch;
    string line;
    char **charArray = new char *[size];
    for (int i = 0; i < size; ++i)
    {
        charArray[i] = new char[size];
    }
    int row = 0;
    int col = 0;
    string lineB;
    int pattsize;
    char **pattArray;

    while (file.get(ch))
    {
        if (ch == '\n' && (line.empty() || isWhitespaceOrEmpty(line)))
        {
            if (getline(file, lineB))
            {
                pattsize = static_cast<int>(sqrt(lineB.length()) + 0.5);

                pattArray = new char *[pattsize];

                for (int i = 0; i < pattsize; ++i)
                {
                    pattArray[i] = new char[pattsize];
                    for (int j = 0; j < pattsize; ++j)
                    {
                        int index = i * pattsize + j;
                        if (index < lineB.length())
                        {
                            pattArray[i][j] = lineB[index];
                        }
                        else
                        {
                            pattArray[i][j] = ' ';
                        }
                    }
                }
            }
            break;
        }

        if (ch != '\n')
        {
            if (ch != ',')
            {
                line += ch;
            }
        }
        else
        {
            for (col = 0; col < line.length(); col++)
            {
                charArray[row][col] = line[col];
            }
            row++;
            line.clear();
        }
    }

    file.close();
    vector<vector<char>> text;
    for (int i = 0; i < size; ++i)
    {
        vector<char> row;
        for (int j = 0; j < size; ++j)
        {
            row.push_back(charArray[i][j]);
        }
        text.push_back(row);
    }
    for (int i = 0; i < static_cast<int>(text.size()); ++i)
    {
        for (int j = 0; j < static_cast<int>(text[i].size()); ++j)
        {
            cout << text[i][j] << ' ';
        }
        cout << endl;
    }

    cout << "----------" << endl;

    vector<vector<char>> pattern;

    for (int i = 0; i < pattsize; i++)
    {
        vector<char> col;
        for (int j = 0; j < pattsize; j++)
        {
            col.push_back(pattArray[i][j]);
        }
        pattern.push_back(col);
    }

    for (int i = 0; i < static_cast<int>(pattern.size()); ++i)
    {
        for (int j = 0; j < static_cast<int>(pattern[i].size()); ++j)
        {
            cout << pattern[i][j] << ' ';
        }
        cout << endl;
    }

    cout << "----------" << endl;
    int occurrences = findDiagonalOccurrences(text, pattern);
    if (occurrences >= 2)
    {
        cout << "Diagonal occurrences of the pattern: " << occurrences << endl;
    }
    else
    {
        cout << "The diagonal pattern is considered non-existent." << endl;
    }
    return 0;
}
