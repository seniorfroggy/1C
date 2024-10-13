#include <algorithm>
#include <cctype>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>


class Solitaire {
public:
    Solitaire(std::vector<std::vector<int>> initialPiles) : piles(initialPiles) {
    }

    Solitaire(std::vector<std::string> initialPiles) {
        for (const auto& str : initialPiles) {
            std::vector<int> temp_pile;
            for (char ch : str) {
                if (std::isdigit(ch)) {
                    temp_pile.push_back(ch - '0');
                }
            }
            piles.push_back(temp_pile);
        }
    }

    int accurateSolution() {
        std::queue<std::pair<std::vector<std::vector<int>>, int>> q;
        std::unordered_map<std::string, bool> visited;
        auto initialState = removeSequence(piles);
        q.push({initialState, 0});

        while (!q.empty()) {
            auto [currentState, actions] = q.front();

            std::string currenStateHash = getStateHash(currentState);
            q.pop();

            visited[currenStateHash] = true;

            if (isSolved(removeSequence(currentState))) {
                return actions;
            }

            for (int i = 0; i < kNumPiles; ++i) {
                for (int j = 0; j < kNumPiles; ++j) {
                    if (i != j) {
                        auto [was_moved, movedState] = moveCard(currentState, i, j);
                        movedState = removeSequence(movedState);
                        std::string movedStateHash = getStateHash(movedState);
                        if (was_moved && visited.find(getStateHash(movedState)) == visited.end()) {
                            q.push({movedState, actions + 1});
                            visited[getStateHash(movedState)] = true;
                        }
                    }
                }
            }
        }
        return -1;
    }

private:
    std::vector<std::vector<int>> piles;
    const static int kCardMin = 1;
    const static int kCardMax = 9;
    const static int kNumPiles = 8;

    std::vector<std::vector<int>> getCurrentState() {
        return piles;
    }

    std::string getPileHash(const std::vector<int>& pile) {
        std::string hash;
        for (int card : pile) {
            hash.push_back(static_cast<char>('0' + card));
        }
        return hash;
    }

    std::string getStateHash(const std::vector<std::vector<int>>& state) {
        std::vector<std::string> hashed_piles;
        for (const auto& pile : state) {
            hashed_piles.push_back(getPileHash(pile));
        }
        std::sort(hashed_piles.begin(), hashed_piles.end());
        std::string joined_hash;
        for (auto hash : hashed_piles) {
            joined_hash += hash + '&';
        }
        return joined_hash;
    }

    bool isSolved(const std::vector<std::vector<int>>& state) {
        for (const auto& pile : state) {
            if (!pile.empty()) return false;
        }
        return true;
    }

    std::vector<std::vector<int>> removeSequence(const std::vector<std::vector<int>>& state) {
        std::vector<std::vector<int>> newState = state;
        for (int i = 0; i < kNumPiles; ++i) {
            if (isCorrectSequence(newState[i])) {
                for (int j = 0; j < kCardMax - kCardMin + 1; ++j) {
                    newState[i].pop_back();
                }
            }
        }
        return newState;
    }

    bool isCorrectSequence(const std::vector<int>& pile) {
        int size = static_cast<int>(pile.size());
        if (size < kCardMax - kCardMin + 1) {
            return false;
        }

        for (int i = kCardMin; i <= kCardMax; ++i) {
            if (pile[size - i] != i) {
                return false;
            }
        }
        return true;
    }

    std::vector<int> removeSingleSequence(const std::vector<int>& pile) {
        auto copy = pile;
        if (isCorrectSequence(pile)) {
            for (int j = 0; j < kCardMax - kCardMin + 1; ++j) {
                copy.pop_back();
            }
        }
        return copy;
    }

    std::pair<bool, std::vector<std::vector<int>>> moveCard(const std::vector<std::vector<int>>& state, int fromIdx, int toIdx) {
        if (state[fromIdx].empty()) {
            return {false, state};
        }

        int card = state[fromIdx].back();
        if (state[toIdx].empty() || card < state[toIdx].back()) {
            std::vector<std::vector<int>> newState = state;
            newState[toIdx].push_back(newState[fromIdx].back());
            newState[fromIdx].pop_back();
            return {true, newState};
        }
        return {false, state};
    }
};

std::vector<std::vector<int>> fromString(std::vector<std::string>& str) {
    std::vector<std::vector<int>> res;
    for (auto st : str) {
        std::vector<int> temp;
        for (char ch : st) {
            if (ch != ' ') {
                temp.push_back(ch - '0');
            }
        }
        res.push_back(temp);
    }
    return res;
}
