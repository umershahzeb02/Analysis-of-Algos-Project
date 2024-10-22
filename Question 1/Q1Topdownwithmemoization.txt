#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
using namespace std;

class CustomBurfi {
public:
    int customProfit;
    vector<float> customPath;

    CustomBurfi() : customProfit(0), customPath() {}

    
    void printCustomPath() const {
        size_t customDimensionIndex = 0;
        while (customDimensionIndex < customPath.size()) {
            cout << customPath[customDimensionIndex] << " square cm + ";
            customDimensionIndex++;
        }
        cout << "\b\b " << '\n';
    }
    
    bool isCustomPathEmpty() const {
        return customPath.empty();
    }
};

class CustomBurfiCalculator {
private:
    static unordered_map<float, CustomBurfi> memo; // Cache for memoization

public:
    static CustomBurfi maximizeProfitRecursive(float customTotalSize, const vector<float>& customPrices) {
        if (memo.find(customTotalSize) != memo.end()) {
            return memo[customTotalSize]; // Return cached result if available
        }

        if (customTotalSize == 0) {
            return CustomBurfi();
        }

        CustomBurfi customMaxResult;

        size_t i = 0;
        while (i < customPrices.size()) {
            int customPortionSize = (i + 1) * 100;
            if (customPortionSize <= customTotalSize) {
                CustomBurfi customResult = maximizeProfitRecursive(customTotalSize - customPortionSize, customPrices);
                int customCurrentProfit = customPrices[i] + customResult.customProfit;

                if (customCurrentProfit > customMaxResult.customProfit) {
                    customMaxResult.customProfit = customCurrentProfit;
                    customMaxResult.customPath = customResult.customPath;
                    customMaxResult.customPath.push_back(customPortionSize);
                }
            }

            i++;
        }

        memo[customTotalSize] = customMaxResult; // Store the result in cache
        return customMaxResult;
    }
};

// Initialize the static member
unordered_map<float, CustomBurfi> CustomBurfiCalculator::memo;


vector<float> parsePricesFromLine(const string& customLine) {
    vector<float> customPrices;
    stringstream customSs(customLine);
    string customToken;

    while (getline(customSs, customToken, ',')) {
        size_t customPos = customToken.find('{');
        if (customPos != string::npos) {
            float customPrice = stof(customToken.substr(customPos + 1));
            customPrices.push_back(customPrice);
        }
    }

    return customPrices;
}

void processFile(const string& customFilename) {
    ifstream customFile(customFilename);
    if (!customFile.is_open()) {
        cerr << "The file cannot be opened: " << customFilename << '\n';
        return;
    }

    int customTotalSize;
    customFile >> customTotalSize;

    string customLine;
    getline(customFile, customLine);

    vector<float> customPrices;

    while (getline(customFile, customLine)) {
        vector<float> customLinePrices = parsePricesFromLine(customLine);
        customPrices.insert(customPrices.end(), customLinePrices.begin(), customLinePrices.end());
    }

    CustomBurfi customResult = CustomBurfiCalculator::maximizeProfitRecursive(customTotalSize, customPrices);

    cout << "CustomBurfi of size having the maximum profit " << customTotalSize << " square cm: " << customResult.customProfit << '\n';
    cout << "Maximize profit path:\n";

    // Use the new functions
    if (!customResult.isCustomPathEmpty()) {
        customResult.printCustomPath();
    } else {
        cout << "No path available.\n";
    }
}

int main() {
    vector<string> customTestFiles = {"TestCase1.txt", "TestCase2.txt", "TestCase3.txt"};

    size_t customFileIndex = 0;
    while (customFileIndex < customTestFiles.size()) {
        processFile(customTestFiles[customFileIndex]);
        customFileIndex++;
    }

    return 0;
}
