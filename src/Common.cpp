#include "Common.h"
#include <string>
#include <Category.h>
#include <list>

using namespace std;

Common::Common()
{
    //ctor
}

string Common::removeTabsFromString(string str) {
    string newStr = "";
    for(int i = 0; i < str.size(); i++) {
        if(str[i] != ' ') {
            newStr += str[i];
        }
    }
    return newStr;
}

list<Category> Common::parseStringCategory(string str) {
    list<Category> listCategory;

    string nameCategory = "";
    string spendingCategory = "";

    bool nowSpending = false;

    for(int i = 0; i < str.size(); i++) {
        if(str[i] != '=' && str[i] != ';' && !nowSpending) {
            nameCategory += str[i];
        }
        if(nowSpending) {
            spendingCategory += str[i];
        }
        if(str[i] == '=') {
            nowSpending = true;
        }
        if(str[i] == ';') {
            nowSpending = false;
            Category category(nameCategory, stof(spendingCategory));
            listCategory.push_back(category);
            nameCategory = "";
            spendingCategory = "";
        }
    }
    return listCategory;
}

bool Common::existCategory(list<Category> listCategory, string validateCategory) {
    for(Category item : listCategory) {
        if(item.name == validateCategory) {
            return true;
        }
    }
    return false;
}

Common::~Common()
{
    //dtor
}
