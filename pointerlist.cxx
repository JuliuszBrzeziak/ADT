#include <iostream>
#include <vector>
#include <string>
#include "pointerlist.hxx"

using namespace std;

int main()
{
    PointerList<int> p;
    p.push_front(1);
    p.push_front(2);
    p.push_front(3);
    p.push_front(4);

    int i, j;

    i = p.pop_back();
    j = p.pop_back();
    // i = p.pop_front();
    // j = p.pop_front();
    p.push_back(7);
    p.push_back(5);
    p.push_back(5);
    p.push_back(7);
    cout << p.remove(5) << "<<";

    p.erase(p.insert(p.find(3), 7));

    cout << p.size();

    cout << "fi$$$$$$$nd" << p.test(p.find(7));
    if (p.empty() == false)
    {
        cout << "edlo";
    }
    for (const auto &aa : p)
        std::cout
            << "foreach" << aa << std::endl;

    cout
        << i << "   " << j << endl;
    return 0;
}