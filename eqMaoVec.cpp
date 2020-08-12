#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <algorithm>
#include <random>
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
void fillСontainers(std::vector<short>& v, std::map<short, short>& m,const int SIZE, std::random_device & rd)
{
    /*just fill containers*/
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distFill(0, 9);
    for (size_t i = 0; i < SIZE; ++i)
    {
        v.push_back(distFill(gen));
        m.emplace(i, distFill(gen));
    }
}
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Only one argument\n";
        return -1;
    }
    std::random_device rd;
    const int SIZE = std::atoi(argv[1]);
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distRemove(0, SIZE > 15 ? 15 : SIZE-1);
    const short DELETE_FROM_VECTOR = distRemove(gen);
    const short DELETE_FROM_MAP = distRemove(gen);
    std::vector<short> v;
    std::map<short, short> m;
    fillСontainers(v, m, SIZE,rd);
#ifdef DEBUG
    std::cout << "filled containers\n";
#endif
    showСontainers(v, m);
    for (size_t i = 0; ; i++)
    {
        /*removing random elements*/
        if (DELETE_FROM_VECTOR > i)
        {
            std::uniform_int_distribution<> removingElement(0, v.size()-1);
            v.erase(v.begin() + removingElement(gen));
        }
        if (DELETE_FROM_MAP > i)
        {
            std::uniform_int_distribution<> removingElement(0, m.size() - 1);
            m.erase(removingElement(gen));
        }
        if (DELETE_FROM_VECTOR <= i && DELETE_FROM_MAP <= i)
            break;
    }
#ifdef DEBUG
    std::cout << "will remove " << DELETE_FROM_VECTOR << " from vector\n";
    std::cout << "will remove " << DELETE_FROM_MAP << " from map\n";
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