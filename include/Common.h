#ifndef COMMON_H
#define COMMON_H
#include <string>
#include <Category.h>
#include <list>

using namespace std;

class Common
{
    public:
        string removeTabsFromString(string str);
        list<Category> parseStringCategory(string str);
        bool existCategory(list<Category> listCategory, string validateCategory);

        Common();
        virtual ~Common();

    protected:

    private:
};

#endif // COMMON_H
