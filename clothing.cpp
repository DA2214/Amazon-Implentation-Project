#include "clothing.h"
#include "util.h"


using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand ) :
    Product(category, name, price, qty),
    size_(size),
    brand_(brand)
{

}

Clothing::~Clothing()
{

}

set<string> Clothing::keywords() const {
    set<string> keywords;
    set<string> name = parseStringToWords(name_);
    set<string> brand = parseStringToWords(brand_);
    string size = size_;

    keywords.insert(name.begin(), name.end());
    keywords.insert(brand.begin(), brand.end());
    keywords.insert(size);

    return keywords;
}


string Clothing::displayString() const {
    stringstream ss;
    ss << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n" << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Clothing::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}