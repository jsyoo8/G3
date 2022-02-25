#include <cstdio>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

using namespace std;

// #define USE_TXT

void cppReady() {
#if defined(USE_TXT)
    // ios_base::sync_with_stdio(false); cin.tie(NULL); freopen("TestCases.txt", "r", stdin); freopen("out.txt", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(NULL); freopen("TestCases.txt", "r", stdin);
#else
    ios_base::sync_with_stdio(false); cin.tie(NULL);
#endif
}

int world[100][100];
stack< pair<int, int> > island[10000];

int main(void) {
    cppReady();
    int N;
    cin >> N;

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cin >> world[y][x];
        }
    }

    int islandCnt = 0;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (world[y][x] == 1) {
                islandCnt++;
                world[y][x] = islandCnt + 1;
                stack< pair<int, int> > tempS;
                tempS.push(make_pair(x, y));
                while (!tempS.empty()) {
                    int curX = tempS.top().first;
                    int curY = tempS.top().second;
                    tempS.pop();
                    bool canExtand = false;
                    if (curX != N - 1) {
                        if (world[curY][curX + 1] == 1) {
                            world[curY][curX + 1] = islandCnt + 1;
                            tempS.push(make_pair(curX + 1, curY));
                        }
                        else if (world[curY][curX + 1] == 0) {
                            canExtand = true;
                        }
                    }
                    if (curY != N - 1) {
                        if (world[curY + 1][curX] == 1) {
                            world[curY + 1][curX] = islandCnt + 1;
                            tempS.push(make_pair(curX, curY + 1));
                        }
                        else if (world[curY + 1][curX] == 0) {
                            canExtand = true;
                        }
                    }
                    if (curX != 0) {
                        if (world[curY][curX - 1] == 1) {
                            world[curY][curX - 1] = islandCnt + 1;
                            tempS.push(make_pair(curX - 1, curY));
                        }
                        else if (world[curY][curX - 1] == 0) {
                            canExtand = true;
                        }
                    }
                    if (curY != 0) {
                        if (world[curY - 1][curX] == 1) {
                            world[curY - 1][curX] = islandCnt + 1;
                            tempS.push(make_pair(curX, curY - 1));
                        }
                        else if (world[curY - 1][curX] == 0) {
                            canExtand = true;
                        }
                    }
                    if (canExtand) {
                        island[islandCnt + 1].push(make_pair(curX, curY));
                    }
                }
            }
        }
    }

    int result = 20000;
    int loopCnt = 0;
    bool isFinish = false;
    while (!isFinish) {
        for (int i = 2; i <= islandCnt + 1; i++) {
            stack< pair<int, int> > tempS;
            while (!island[i].empty()) {
                int curX = island[i].top().first;
                int curY = island[i].top().second;
                tempS.push(make_pair(curX, curY));
                island[i].pop();
            }
            while (!tempS.empty()) {
                int curX = tempS.top().first;
                int curY = tempS.top().second;
                tempS.pop();
                int bridge = 20000;
                if (curX != N - 1) {
                    if (world[curY][curX + 1] == 0) {
                        world[curY][curX + 1] = i;
                        island[i].push(make_pair(curX + 1, curY));
                    }
                    else if (world[curY][curX + 1] < i) {
                        bridge = 2 * loopCnt + 1;
                        isFinish = true;
                    }
                    else if (world[curY][curX + 1] > i) {
                        bridge = 2 * loopCnt;
                        isFinish = true;
                    }
                }
                if (curY != N - 1) {
                    if (world[curY + 1][curX] == 0) {
                        world[curY + 1][curX] = i;
                        island[i].push(make_pair(curX, curY + 1));
                    }
                    else if (world[curY + 1][curX] < i) {
                        bridge = 2 * loopCnt + 1;
                        isFinish = true;
                    }
                    else if (world[curY + 1][curX] > i) {
                        bridge = 2 * loopCnt;
                        isFinish = true;
                    }
                }
                if (curX != 0) {
                    if (world[curY][curX - 1] == 0) {
                        world[curY][curX - 1] = i;
                        island[i].push(make_pair(curX - 1, curY));
                    }
                    else if (world[curY][curX - 1] < i) {
                        bridge = 2 * loopCnt + 1;
                        isFinish = true;
                    }
                    else if (world[curY][curX - 1] > i) {
                        bridge = 2 * loopCnt;
                        isFinish = true;
                    }
                }
                if (curY != 0) {
                    if (world[curY - 1][curX] == 0) {
                        world[curY - 1][curX] = i;
                        island[i].push(make_pair(curX, curY - 1));
                    }
                    else if (world[curY - 1][curX] < i) {
                        bridge = 2 * loopCnt + 1;
                        isFinish = true;
                    }
                    else if (world[curY - 1][curX] > i) {
                        bridge = 2 * loopCnt;
                        isFinish = true;
                    }
                }
                if (bridge < result) {
                    result = bridge;
                }
            }
        }
        loopCnt++;
    }
    cout << result;

    return 0;
}