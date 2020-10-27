
#include <iostream>
#include <vector>

int main () 
{
    std::vector<int> v = std::vector<int>();
    v.push_back(5);
    v.push_back(6);
    for(auto i=v.begin(); i != v.end(); i++ )
        std::cout << "VALUE OF i: " << *i << std::endl;
    return 0;
}