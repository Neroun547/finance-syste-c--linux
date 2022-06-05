#include "MainController.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cmath>

using namespace std;

MainController::MainController()
{
}

void MainController::addCategory(string category) {
    ofstream fout;
    string user = getlogin();

    fout.open("/home/"+user+ "/category.txt", ios::app);
    fout << category+"=0;";
    fout.close();
}

string MainController::getAllCategory(string pathToFile) {
    string data;
    ifstream read;

    read.open(pathToFile);
    getline(read, data);
    read.close();

    return data;
}

void MainController::addSpandingToCategory(string category, float sum, list<Category> listCategory) {
    list<Category> newListCategory;

    for(Category item : listCategory) {

        if(item.name == category) {
            item.spending += sum;

            newListCategory.push_back(item);
            break;
        }
        newListCategory.push_back(item);
    }
    string user = getlogin();
    ofstream fout;

    fout.open("/home/"+user+"/category.txt");

    for(Category item : newListCategory) {
        fout << item.name + "=" + to_string(round(item.spending*100)/100) + ";";
    }
    fout.close();
}

void MainController::removeCategory(string category, list<Category> listCategory) {
    list<Category> newListCategory;

    for(Category item : listCategory) {
        if(item.name != category) {
            newListCategory.push_back(item);
        }
    }
    string user = getlogin();
    ofstream fout;

    fout.open("/home/"+user+"/category.txt");

    for(Category item: newListCategory) {
        fout << item.name + "=" + to_string(item.spending) + ";";
    }
    fout.close();
}

void MainController::removeSum(string category, float sum, list<Category> listCategory) {
        list<Category> newListCategory;

    for(Category item : listCategory) {

        if(item.name == category) {
            item.spending -= sum;

            newListCategory.push_back(item);
            break;
        }
        newListCategory.push_back(item);
    }
    string user = getlogin();
    ofstream fout;

    fout.open("/home/"+user+"/category.txt");

    for(Category item : newListCategory) {
        fout << item.name + "=" + to_string(round(item.spending*100)/100) + ";";
    }
    fout.close();
}

MainController::~MainController()
{
    //dtor
}
