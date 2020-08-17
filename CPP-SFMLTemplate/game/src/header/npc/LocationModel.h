#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class LocationModel
{

private:
    Vector2i mPosition;

public:
    LocationModel(Vector2i mPositionN)
    {
		mPosition = mPositionN;
    }

    ~LocationModel()
    {

    }

    Vector2i getPosition()
    {
        return mPosition;
    }

};

