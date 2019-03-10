#include "soci.h"
#include "soci-sqlite3.h"
#include <exception>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

using namespace soci;
using namespace std;

bool get_name(string &name) {
  cout << "Enter name: ";
	cin >> name;
  return true;
}

int main() {
  try {
    session sql("sqlite3", "db=mydb.sqlite timeout=2 shared_cache=true");

    int count;
    sql << "select count(*) from phonebook", into(count);

    cout << "We have " << count << " entries in the phonebook.\n";

    string name;
    while (get_name(name)) {
      string phone;
      indicator ind;
      sql << "select phone from phonebook where name = :name", into(phone, ind),
          use(name);

      if (ind == i_ok) {
        cout << "The phone number is " << phone << '\n';
      } else {
        cout << "There is no phone for " << name << '\n';
      }
    }
  } catch (exception const &e) {
    cerr << "Error: " << e.what() << '\n';
  }
}
