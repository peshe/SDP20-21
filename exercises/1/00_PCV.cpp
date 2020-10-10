#include <cstddef>
#include <iostream>
#include <vector>

//Using bit operations
void powerSet(const std::string& set)
{
    for (size_t i = 0, sz = 1 << set.size(); i < sz; i++) {
        size_t j = i;
        size_t pos = 0;
        std::cout << "{ ";
        while (j > 0) {
            if (1 & j) {
                std::cout << set[pos];
            }
            j >>= 1;
            pos += 1;
        }
        std::cout << " } ";
    }
    std::cout << std::flush;
}

//Backtracking
void powerSet(const std::string& set, std::string& curr, int pos = -1)
{
    //Print
    std::cout << "{ ";
    std::cout << curr;
    std::cout << " } " << std::flush;

    for (size_t i = pos + 1, sz = set.size(); i < sz; i++) {
        curr.push_back(set[i]);
        powerSet(set, curr, i);
        curr.erase(curr.size() - 1);
    }
}

//Binary Vectors
void powerSet2(const std::string& set, std::string& curr, int pos = 0)
{
    if (size_t(pos) == set.size()) {
        std::cout << curr << " ";
        return;
    }

    curr[pos] = '0';
    powerSet2(set, curr, pos + 1);
    curr[pos] = '1';
    powerSet2(set, curr, pos + 1);
}


void permutations(const std::string& set, std::string& curr, bool used[], size_t pos = 0)
{
    if (pos >= set.size()) {
        std::cout << " " << curr << " ";
        return;
    }

    for (size_t i = 0, sz = set.size(); i < sz; i++) {
        if(!used[i]) {
            curr[pos] = set[i];
            used[i] = 1;
            permutations(set, curr, used, pos + 1);
            used[i] = 0;
        }
    }
}


void variate(const std::string& set, std::string& curr, bool used[], size_t k, size_t pos = 0)
{
    if (pos >= k) {
        std::cout << " " << curr << " ";
        return;
    }

    for (size_t i = 0, sz = set.size(); i < sz; i++) {
        if(!used[i]) {
            curr[pos] = set[i];
            used[i] = 1;
            variate(set, curr, used, k, pos + 1);
            used[i] = 0;
        }
    }
}

void variateWithDuplications(const std::string& set, std::string& curr, size_t k, size_t pos = 0)
{
    if (pos >= k) {
        std::cout << " " << curr << " ";
        return;
    }

    for (size_t i = 0, sz = set.size(); i < sz; i++) {
            curr[pos] = set[i];
            variateWithDuplications(set, curr, k, pos + 1);
    }
}


void combinations(const std::string& set, std::string& curr, size_t k, size_t pos = 0, size_t after = 0)
{

    if (pos >= k) {
        std::cout << " " << curr << " ";
        return;
    }

    for (size_t i = after , sz = set.size(); i < sz; i++) {
        curr[pos] = set[i];
        combinations(set, curr, k, pos + 1, i + 1);
    }
}

void combinationsWithDuplications(const std::string& set, std::string& curr, size_t k, size_t pos = 0, size_t after = 0)
{
    if (pos >= k) {
        std::cout << " " << curr << " ";
        return;
    }

    for (size_t i = after , sz = set.size(); i < sz; i++) {
        curr[pos] = set[i];
        combinationsWithDuplications(set, curr, k, pos + 1, i);
    }
}


void print(const std::string& set, const std::vector<size_t>& index)
{
    std::cout << " ";
    for (size_t i = 1; i < index.size(); ++i){
        std::cout << set[index[i]-1];
    }
    std::cout << " ";
}

void combinationsIterative(const std::string& set, size_t k)
{
    const size_t n = set.size();

    std::vector<size_t> index(k+1);
    for (size_t i = 0; i <= k; ++i)
        index[i] = i;

    while (index[0] == 0) {
        print(set, index);
        size_t pos = k;
        while(index[pos] == n-k+pos) --pos;
        ++index[pos];
        while (pos < k){
            index[pos+1] = index[pos] + 1;
            ++pos;
        }
    }
}

int main()
{
    std::string set{"1234"};
    std::string cur(set.size(), '\0');
    bool used[256] = {false,};

    std::cout << "Power set - iterative:\n";
    powerSet(set);
    std::cout << "\nPower set - recursive:\n";
    powerSet(set, cur);
    std::cout << "\nPower set - recursive: binary vectors:\n";
    powerSet2(set, cur);

    std::cout << "\nPermutations:\n";
    permutations(set, cur, used);

    std::cout << "\nVariations:\n";
    cur.resize(2);
    variate(set, cur, used, 2);

    std::cout << "\nVariations with duplications:\n";
    variateWithDuplications(set, cur, 2);

    std::cout << "\nCombinations:\n";
    cur.resize(3);
    combinations(set, cur, 3);
    std::cout << "\nCombinations iterative:\n";
    combinationsIterative(set, 3);

    std::cout << "\nCombinations with duplications:\n";
    cur.resize(2);
    combinationsWithDuplications(set, cur, 2);
    std::cout << std::endl << std::flush;

    return 0;
}
