#include "Category.h"
#include <string>

using namespace std;

Category::Category(string name, float spending)
{
    this -> name = name;
    this -> spending = spending;
}

Category::~Category()
{
    //dtor
}
