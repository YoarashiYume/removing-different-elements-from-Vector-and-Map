#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "Randomizer.h"
#define DEBUG
void showСontainers(const std::vector<short> & v, const std::map<short, short>& m)
{
    std::cout << "vector =\n";
    for (auto element : v)
        std::cout << element << " ";
    std::cout << std::endl << "map =\n";
    for (auto element : m)
        std::cout << element.second << " ";
    std::cout << std::endl << std::endl;
}
void fillСontainers(std::vector<short>& v, std::map<short, short>& m,const int SIZE, Randomizer & rd)
{
   
    rd.setRange(0, 9);
    for (size_t i = 0; i < SIZE; ++i)
    {
        v.push_back(rd.getRandomValue());
        m.emplace(i, rd.getRandomValue());
    }
}
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Only one argument\n";
        return -1;
    }
    Randomizer random;
    const unsigned int SIZE = std::atoi(argv[1]);
    random.setRange(0, SIZE > 15 ? 15 : SIZE - 1);
    const unsigned int DELETE_FROM_VECTOR = random.getRandomValue();
    const unsigned int DELETE_FROM_MAP = random.getRandomValue();
    std::vector<short> v;
    std::map<short, short> m;
    fillСontainers(v, m, SIZE, random);
#ifdef DEBUG
    std::cout << "filled containers\n";
#endif
    showСontainers(v, m);
    /*removing random elements*/  
    for (size_t i = 0; DELETE_FROM_VECTOR != i; ++i)
        if (DELETE_FROM_VECTOR > i)
        {
            random.setRange(0, v.size() - 1);
            v.erase(v.begin() + random.getRandomValue());
        }
    for (size_t i = 0; DELETE_FROM_MAP != i; ++i)
        if (DELETE_FROM_MAP > i)
        {
            random.setRange(0, m.size() - 1);
            m.erase(random.getRandomValue());
        }
#ifdef DEBUG
    std::cout << "will remove " << DELETE_FROM_VECTOR << " from vector\n";
    std::cout << "will remove " << DELETE_FROM_MAP << " from map\n\n";
    std::cout << "containers after removing random elements\n";
    showСontainers(v, m);
#endif
    /*comparing vector elements with map elements
    and removing missing elements*/
    v.erase(remove_if(v.begin(), v.end(), [&m](short element) {
        return find_if(m.begin(), m.end(), [element](std::pair<short, short> p) {return p.second == element; }) == m.end();
        }),v.end());
    /*comparing map elements with vector elements
    and removing missing elements*/
    for (auto it = m.begin(); it != m.end();)
        if (find_if(v.begin(), v.end(), [it](short el) {return el == (*it).second;}) == v.end())
           it = m.erase(it);
        else
            ++it;
#ifdef DEBUG
    std::cout << "result view\n";
#endif
    showСontainers(v, m);
    return 0;
}