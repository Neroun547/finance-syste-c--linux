#ifndef CATEGORY_H
#define CATEGORY_H
#include <string>

using namespace std;

class Category
{
    public:
        string name;
        float spending;

        Category(string name, float spending);
        virtual ~Category();

    protected:

    private:
};

#endif // CATEGORY_H
