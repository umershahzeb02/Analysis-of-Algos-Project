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
        vector<CustomBurfi> dp(customTotalSize + 1);

        for (float i = 1; i <= customTotalSize; ++i) {
            for (size_t j = 0; j < customPrices.size(); ++j) {
                int customPortionSize = (j + 1) * 100;
                if (customPortionSize <= i) {
                    CustomBurfi potentialResult = dp[i - customPortionSize];
                    int potentialProfit = customPrices[j] + potentialResult.customProfit;

                    if (potentialProfit > dp[i].customProfit) {
                        dp[i].customProfit = potentialProfit;
                        dp[i].customPath = potentialResult.customPath;
                        dp[i].customPath.push_back(customPortionSize);
                    }
                }
            }
        }

        return dp[customTotalSize];
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
