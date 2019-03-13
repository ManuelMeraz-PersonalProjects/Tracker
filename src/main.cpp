#include <algorithm>
#include <iostream>
#include <soci-sqlite3.h>
#include <soci.h>
#include <vector>
#include "food/Food.hpp" // Food
#include "food/Macronutrients.hpp" // Fat, Carbohydrate, Protein

int main() {
  soci::session sql("sqlite3", "db=test.db timeout=2 shared_cache=true");
  //int count;
  //sql << "SELECT count(name) "
      //<< "FROM tracks;",
      //soci::into(count);

  //std::vector<std::string> artists(count);
  //sql << "SELECT name "
      //<< "FROM tracks;",
      //soci::into(artists);

  //const auto printArtist =
      //[](const auto &artist) { std::cout << artist << std::endl; };

  //std::for_each(std::begin(artists), std::end(artists), printArtist);
	//
	Macronutrients macros(Fat(10), Carbohydrate(10), Protein(10));
	Food food(macros, "food name");

}
