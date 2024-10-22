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
public:
    static CustomBurfi maximizeProfitBottomUp(float customTotalSize, const vector<float>& customPrices) {
        vector<int> maxProfit(customTotalSize + 1, 0);
        vector<int> lastPortion(customTotalSize + 1, -1); // to track the last portion size for each size

        for (float i = 1; i <= customTotalSize; ++i) {
            for (size_t j = 0; j < customPrices.size(); ++j) {
                int customPortionSize = (j + 1) * 100;
                if (customPortionSize <= i) {
                    int potentialProfit = customPrices[j] + maxProfit[i - customPortionSize];
                    if (potentialProfit > maxProfit[i]) {
                        maxProfit[i] = potentialProfit;
                        lastPortion[i] = customPortionSize;
                    }
                }
            }
        }

        // Reconstruct the path
        vector<float> path;
        int size = customTotalSize;
        while (size > 0) {
            int portion = lastPortion[size];
            if (portion != -1) {
                path.push_back(portion);
                size -= portion;
            }
        }

        CustomBurfi result;
        result.customProfit = maxProfit[customTotalSize];
        result.customPath = path;
        return result;
    }
};



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
    getline(customFile, customLine); // to skip the newline after reading customTotalSize

    vector<float> customPrices;

    while (getline(customFile, customLine)) {
        vector<float> customLinePrices = parsePricesFromLine(customLine);
        customPrices.insert(customPrices.end(), customLinePrices.begin(), customLinePrices.end());
    }

    CustomBurfi customResult = CustomBurfiCalculator::maximizeProfitBottomUp(customTotalSize, customPrices);

    cout << "CustomBurfi of size having the maximum profit " << customTotalSize << " square cm: " << customResult.customProfit << '\n';
    cout << "Maximize profit path:\n";

    if (!customResult.isCustomPathEmpty()) {
        customResult.printCustomPath();
    } else {
        cout << "No path available.\n";
    }
}

int main() {
    vector<string> customTestFiles = {"TestCase1.txt", "TestCase2.txt", "TestCase3.txt"};

    for (const auto& filename : customTestFiles) {
        processFile(filename);
    }

    return 0;
}
