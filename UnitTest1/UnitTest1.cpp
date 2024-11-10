#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <limits>
#include "../PDC_LAB11/source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestFloydWarshall)
        {
            int n = 4;
            vector<vector<int>> dist = {
                {0, 3, INF, 7},
                {8, 0, 2, INF},
                {5, INF, 0, 1},
                {2, INF, INF, 0}
            };

            vector<vector<int>> next(n, vector<int>(n, -1));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[i][j] != INF) {
                        next[i][j] = j;
                    }
                }
            }

            int** dist_array = new int* [n];
            int** next_array = new int* [n];

            for (int i = 0; i < n; ++i) {
                dist_array[i] = new int[n];
                next_array[i] = new int[n];
            }

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    dist_array[i][j] = dist[i][j];
                    next_array[i][j] = next[i][j];
                }
            }

            floydWarshall(dist_array, n, dist_array, next_array);

            Assert::AreEqual(5, dist_array[1][0]);
            Assert::AreEqual(5, dist_array[0][2]);
            Assert::AreEqual(3, dist_array[1][3]);
            Assert::AreEqual(5, dist_array[3][1]);

            for (int i = 0; i < n; ++i) {
                delete[] dist_array[i];
                delete[] next_array[i];
            }
            delete[] dist_array;
            delete[] next_array;
        }
    };
}
