//#include <sstream>
#include "book.h"
#include "util.h"
#include <iostream>

using namespace std;

Book::Book(const string category, const string name, double price, int qty, const string isbn, const string author) :
    Product(category, name, price, qty),
    isbn_(isbn),
    author_(author)
{

}

Book::~Book()
{

}

set<string> Book::keywords() const {
    set<string> keywords;
    set<string> name = parseStringToWords(name_);
    set<string> authorWords = parseStringToWords(author_);
    string isbn = isbn_;

    keywords.insert(name.begin(), name.end());
    keywords.insert(authorWords.begin(), authorWords.end());
    keywords.insert(isbn);

    return keywords;
}

string Book::displayString() const {
    stringstream ss;
    ss << name_ << "\n" << "Author: " << author_ << " ISBN: " << isbn_ << "\n" << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Book::dump(ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}
