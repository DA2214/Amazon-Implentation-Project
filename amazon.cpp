#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>
#include <queue>
#include "product.h"
#include "movie.h"
#include "book.h"
#include "clothing.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"

using namespace std;

struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};

void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[]) {
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    MyDataStore ds;

    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    if (parser.parse(argv[1], ds)) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    map<string, queue<Product*>> userCarts;

    while (!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin, line);
        stringstream ss(line);
        string cmd;

        if ((ss >> cmd)) {
           if (cmd == "AND") {
                string term;
                vector<string> terms;
                while (ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            } 
            else if (cmd == "OR") {
                string term;
                vector<string> terms;
                while (ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }

            else if (cmd == "QUIT") {
                string filename;
                if (ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
            else if (cmd == "ADD") {
                string username;
                unsigned int hitNum;
                if (ss >> username >> hitNum) {
                    username = convToLower(username);

                    if (ds.getUser(username) == nullptr) { 
                        cout << "Invalid request" << endl;
                        continue;
                    }
                    
                    if (hits.empty()) {
                        cout << "Invalid request" << endl;
                    } else if (hitNum < 1 || hitNum > hits.size()) {
                        cout << "Invalid request" << endl;
                    } else {
                        Product* selectedProduct = hits[hitNum - 1];
                        userCarts[username].push(selectedProduct);
                    }
                } else {
                    cout << "Invalid request" << endl;
                }
            }
            else if (cmd == "VIEWCART") {
                string username;
                if (ss >> username) {
                    username = convToLower(username);
                    if (userCarts.find(username) == userCarts.end() || userCarts[username].empty()) {
                        cout << "Invalid username or empty cart" << endl;
                    } else {
                        queue<Product*> tempCart = userCarts[username];
                        int i = 1;
                        while (!tempCart.empty()) {
                            cout << "Item " << i << ":" << endl;
                            cout << tempCart.front()->displayString() << endl;
                            tempCart.pop();
                            i++;
                        }
                    }
                }
            }
            else if (cmd == "BUYCART") {
                string username;
                if (ss >> username) {
                    username = convToLower(username);
                    if (userCarts.find(username) == userCarts.end()) {
                        cout << "Invalid username" << endl;
                    } else {
                        queue<Product*>& cart = userCarts[username];
                        User* user = ds.getUser(username);
                        queue<Product*> tempCart;
                        while (!cart.empty()) {
                            Product* product = cart.front();
                            if (product->getQty() > 0 && product->getPrice() <= user->getBalance()) {
                                user->deductAmount(product->getPrice());
                                product->subtractQty(1);
                            } else {
                                tempCart.push(product);
                            }
                            cart.pop();
                        }
                        cart = tempCart;
                    }
                }
            }
            else {
                cout << "Unknown command" << endl;
            }
        }
    }

    if (hits.empty()) {
    cout << "Invalid request" << endl;
    }

    return 0;
}

void displayProducts(vector<Product*>& hits) {
    int resultNo = 1;
    if (hits.empty()) {
        cout << "No results found!" << endl;
        return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for (auto* product : hits) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << product->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
