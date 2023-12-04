#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Parse a single draw and return a map representing the count of each color.
map<string, int> parseDraw(const string& draw) {
    istringstream ss(draw);
    string token;
    map<string, int> counter;

    while (getline(ss, token, ',')) {
        istringstream pairStream(token);
        int count;
        string color;

        pairStream >> count >> color;
        counter[color] += count;
    }

    return counter;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    // Thresholds for part 1
    map<string, int> thres{{"red", 12}, {"green", 13}, {"blue", 14}};
    int tot_1 = 0, tot_2 = 0;
    string line;

    // Process each line in the file
    while (getline(file, line)) {
        istringstream iss(line);
        string part;
        int game_id;

        // Extract game ID
        iss >> part >> game_id;
        string drawsData = line.substr(line.find(':') + 2);

        istringstream drawStream(drawsData);
        string draw;
        vector<map<string, int>> draws;

        // Parse each draw
        while (getline(drawStream, draw, ';')) {
            draws.push_back(parseDraw(draw));
        }

        // Part 1: Check if all draws are within the threshold
        if (all_of(draws.begin(), draws.end(), [&](const map<string, int>& d) {
            return all_of(d.begin(), d.end(), [&](const auto& pair) {
                return pair.second <= thres[pair.first];
            });
        })) {
            tot_1 += game_id;
        }

        // Part 2: Calculate the power of the minimum set of cubes
        map<string, int> minCubes = {{"red", 0}, {"green", 0}, {"blue", 0}};
        for (const auto& draw : draws) {
            for (const auto& pair : draw) {
                minCubes[pair.first] = max(minCubes[pair.first], pair.second);
            }
        }
        int power = accumulate(minCubes.begin(), minCubes.end(), 1,
                               [](int acc, const auto& pair) {
                                   return acc * pair.second;
                               });
        tot_2 += power;
    }

    cout << "Total IDs of possible games (Part 1): " << tot_1 << endl;
    cout << "Total power of minimum sets (Part 2): " << tot_2 << endl;

    return 0;
}
