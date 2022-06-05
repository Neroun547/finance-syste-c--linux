#include <string>
#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <list>
#include <Category.h>

using namespace std;

class MainController
{
    public:
        void addCategory(string category);
        string getAllCategory(string pathToFile);
        void addSpandingToCategory(string category, float sum, list<Category> listCategory);
        void removeCategory(string category, list<Category> listCategory);
        void removeSum(string category, float sum, list<Category> listCategory);

        MainController();
        virtual ~MainController();

    protected:

    private:
};

#endif // MAINCONTROLLER_H
