#include <algorithm>
#include <iostream>
#include <soci-sqlite3.h>
#include <soci.h>
#include <vector>
#include "food/food.hpp" // Food
#include "food/macronutrients.hpp" // Fat, Carbohydrate, Protein

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
	food::Food food(food::Fat(10), food::Carbohydrate(10), food::Protein(10));

}
