#include "movie.h"
#include "util.h"
#include <sstream>

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating ) :
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{

}

Movie::~Movie()
{

}

set<string> Movie::keywords() const {
    set<string> keywords;
    set<string> name = parseStringToWords(name_);
    set<string> genre = parseStringToWords(genre_);
    string rating = rating_;

    keywords.insert(name.begin(), name.end());
    keywords.insert(genre.begin(), genre.end());
    keywords.insert(rating);

    return keywords;
}


string Movie::displayString() const {
    stringstream ss;
    ss << name_ << "\n" << "Genre: " << genre_ << " Rating: " << rating_ << "\n" << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Movie::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}