#include "datastore.h"
#include "util.h"

class MyDataStore : public DataStore {
public: 
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    User* getUser(std::string username);

private:
    std::vector<Product*> products_;
    std::vector<User*> users_;

};