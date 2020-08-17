#include <iostream>
#include <fstream>

using namespace std;

int main()
{

    ofstream mWaterMap("water.map");
    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            mWaterMap << 1;
            mWaterMap << ' ';
        }
        mWaterMap << '\n';
    }
    return 0;
}
