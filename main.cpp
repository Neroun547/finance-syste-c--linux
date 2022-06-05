#include <iostream>
#include <string>
#include <fstream>
#include <MainController.h>
#include <Common.h>
#include <unistd.h>
#include <list>
#include <Category.h>

using namespace std;

const string templateCommand = "(Write /help for view command): ";

string removeTabsInString(string str);

int main(int argc, char * argv[])
{
    MainController mainController;
    Common common;

    system("clear");
    cout << "Hello. It's finance system. You can add category and add spending to this category." << endl;

    while (true) {
        string command;

        cout << templateCommand;
        getline(cin, command);

        if(command == "/help") {
            cout << "Commands: " << endl;
            cout << "-----------------------------------------------------";
            cout << endl;
            cout << "/all_category - get all category" << endl;
            cout << "/remove_category categoryname - remove category" << endl;
            cout << "/add_category categoryname - add new category" << endl;
            cout << "/add_sum 1000 categoryname - add spending in exist category (In this example 1000)" << endl;
            cout << "/remove_sum 1000 categoryname - remove spending in category (In this example 1000)" << endl;
            cout << "/all_spending - view all spending" << endl;
            cout << "/exit - exit on program" << endl;
            cout << endl;
            cout << "-----------------------------------------------------" << endl;
        } else if(command.find("/all_category") != -1) {
            string user = getlogin();
            string category = mainController.getAllCategory("/home/"+user+ "/category.txt");

            if(category.empty()) {
                cout << "You don't have category" << endl;
                continue;
            }
            list<Category> listCategory = common.parseStringCategory(category);

            cout << "-----------------------------------------------------" << endl;
            for(Category item : listCategory) {
                cout << item.name << " spending: " << item.spending << endl;
            };
            cout << "-----------------------------------------------------" << endl;
        } else if (command.find("/exit") != -1) {
            cout << "Bye" << endl;
            return 0;
        } else if (command.find("/add_category") != -1) {
            try {
                int indexNameCategory = command.find("add_category")+13;
                string category = command.substr(indexNameCategory);

                if(category.find("=") != -1) {
                    cout << "Must be string without number or = !" << endl;

                    continue;
                }
                string user = getlogin();
                string validateCategory = common.removeTabsFromString(command.substr(indexNameCategory));
                string stringCategory = mainController.getAllCategory("/home/"+user+ "/category.txt");

                if(stringCategory.empty()) {
                    mainController.addCategory(validateCategory);

                    continue;
                }
                list<Category> listCategory = common.parseStringCategory(stringCategory);

                if(!common.existCategory(listCategory, validateCategory)) {
                    mainController.addCategory(validateCategory);
                } else {
                    cout << "Category with this name already exist !" << endl;
                }
            } catch (...) {
                continue;
            }
        } else if(command.find("/add_sum") != -1) {
            try {
                string user = getlogin();
                string stringCategory = mainController.getAllCategory("/home/"+user+ "/category.txt");

                if(stringCategory.empty()) {
                    cout << "You don't have category" << endl;

                    continue;
                }
                list<Category> listCategory = common.parseStringCategory(stringCategory);

                int indexSumAndCategory = command.find("/add_sum")+9;
                string sumAndCategory = command.substr(indexSumAndCategory);
                string removeTabsSumAndCategory = common.removeTabsFromString(sumAndCategory);

                if(removeTabsSumAndCategory.find("-") != -1) {
                    cout << "Incorrect value !" << endl;

                    continue;
                }

                string sum = "";
                int indexCategoryName = -1;

                for(int i = 0; i < removeTabsSumAndCategory.length(); i++) {
                    try {
                        if(removeTabsSumAndCategory[i] == '.' && i > 0 && sum[sum.length() -1] != '.' && indexCategoryName == -1) {
                            sum += removeTabsSumAndCategory[i];
                            continue;
                        }
                        string tmp_string(1, removeTabsSumAndCategory[i]);
                        stoi(tmp_string);

                        sum += removeTabsSumAndCategory[i];
                    } catch(...) {
                        indexCategoryName = i;
                        break;
                    }
                }
                string categoryName = removeTabsSumAndCategory.substr(indexCategoryName);

                if(!common.existCategory(listCategory, categoryName)) {
                    cout << "Category with this name not exist" << endl;

                    continue;
                }
                mainController.addSpandingToCategory(removeTabsSumAndCategory.substr(indexCategoryName), stof(sum), listCategory);

            } catch (...) {
                continue;
            }
        } else if(command.find("/remove_category") != -1) {
            try {
                string user = getlogin();
                string stringCategory = mainController.getAllCategory("/home/"+user+ "/category.txt");

                if(stringCategory.empty()) {
                    cout << "You don't have category" << endl;

                    continue;
                }
                list<Category> listCategory = common.parseStringCategory(stringCategory);

                int indexNameCategory = command.find("/remove_category")+16;
                string removeTabsCategory = common.removeTabsFromString(command.substr(indexNameCategory));

                if(!common.existCategory(listCategory, removeTabsCategory)) {
                    cout << "Category with this name not exist" << endl;
                    continue;
                }
                mainController.removeCategory(removeTabsCategory, listCategory);
            } catch(...) {
                continue;
            }
        } else if(command.find("/remove_sum") != -1) {
            try {
                string user = getlogin();
                string stringCategory = mainController.getAllCategory("/home/"+user+ "/category.txt");

                if(stringCategory.empty()) {
                    cout << "You don't have category" << endl;

                    continue;
                }
                list<Category> listCategory = common.parseStringCategory(stringCategory);
                int indexSumAndCategory = command.find("/remove_sum")+11;

                string sumAndCategory = command.substr(indexSumAndCategory);
                string removeTabsSumAndCategory = common.removeTabsFromString(sumAndCategory);

                if(removeTabsSumAndCategory.find("-") != -1) {
                    cout << "Incorrect value !" << endl;

                    continue;
                }
                string sum = "";
                int indexCategoryName = -1;

                for(int i = 0; i < removeTabsSumAndCategory.length(); i++) {
                    try {
                        if(removeTabsSumAndCategory[i] == '.' && i > 0 && sum[sum.length() -1] != '.' && indexCategoryName == -1) {
                            sum += removeTabsSumAndCategory[i];
                            continue;
                        }
                        string tmp_string(1, removeTabsSumAndCategory[i]);
                        stoi(tmp_string);

                        sum += removeTabsSumAndCategory[i];
                    } catch(...) {
                        indexCategoryName = i;
                        break;
                    }
                }
                string categoryName = removeTabsSumAndCategory.substr(indexCategoryName);

                if(!common.existCategory(listCategory, categoryName)) {
                    cout << "Category with this name not exist" << endl;

                    continue;
                }
                mainController.removeSum(categoryName, stof(sum), listCategory);
            } catch (...) {
                continue;
            }
        } else if(command.find("/all_spending") != -1) {
            string user = getlogin();
            string stringCategory = mainController.getAllCategory("/home/"+user+ "/category.txt");

            if(stringCategory.empty()) {
                cout << "You don't have category" << endl;

                continue;
            }
            list<Category> listCategory = common.parseStringCategory(stringCategory);
            double sum = 0;

            for(Category item : listCategory) {
                sum += item.spending;
            }
            cout << "All spending: " << sum << endl;
        }
    }
    return 0;
}

