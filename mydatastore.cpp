#include "mydatastore.h"
#include "util.h"
#include <set>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

MyDataStore::MyDataStore()
{
}

MyDataStore::~MyDataStore()
{
    for (Product* product : products_)
    {
        delete product;
    }

    for (User* user : users_)
    {
        delete user;
    }
}

void MyDataStore::addProduct(Product* p)
{
    products_.push_back(p);
}

void MyDataStore::addUser(User* u)
{
    users_.push_back(u);
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
    set<Product*> products;
    if (type == 0)
    {
        for (Product* product : products_) {
            set<string> keywords = product->keywords();
            set<string> termsSet(terms.begin(), terms.end());
            if (setIntersection(keywords, termsSet).size() == termsSet.size()) {
                products.insert(product);
            }
        }
        return vector<Product*>(products.begin(), products.end());
    }
    else if (type == 1)
    {
        for (Product* product : products_) {
            set<string> keywords = product->keywords();
            set<string> termsSet(terms.begin(), terms.end());
            if (setIntersection(keywords, termsSet).size() > 0) {
                products.insert(product);
            }
        }
        return vector<Product*>(products.begin(), products.end());
    }

    return vector<Product*>();
}

void MyDataStore::dump(ostream& ofile)
{
    ofile << "<products>" << endl;
    for (Product* product : products_) {
        product->dump(ofile);
    }
    ofile << "</products>" << endl;

    ofile << "<users>" << endl;
    for (User* user : users_) {
        user->dump(ofile);
    }
    ofile << "</users>" << endl;
}

User* MyDataStore::getUser(string username)
{
    for (User* user : users_) {
        if (user->getName() == username) {
            return user;
        }
    }

    return NULL;
}