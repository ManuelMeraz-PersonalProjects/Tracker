#include <algorithm>
#include <iostream>
#include <vector>
#include "food/Food.hpp" // Food
#include "food/Macronutrients.hpp" // Fat, Carbohydrate, Protein
#include <sstream>

int main() {
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
	//Macronutrients macros(Fat(10), Carbohydrate(10, Fiber(10)), Protein(10));
	//Food food(macros, "food name");
	//Food food(macros, "tacos");
	//auto data = food.get_data();

	//std::stringstream ss;
	//ss << "INSERT into " << data["table"] << ", "
		//<< " (name, fat, carbohydrate, fiber, protein) "
		//<< " VALUES "
		//<< " ('" << data["name"] << "', " << data["fat"] << ", " << data["carbohydrate"] << ", " << data["fiber"] << ", " << data["protein"] << ")"
		//<< ";";

	//std::cout << ss.str() << std::endl;
	//sql << ss.str();
	return 0;
}
