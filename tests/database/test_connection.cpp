#include "database/Database.hpp"

#include <gtest/gtest.h>

#include <sstream>

TEST(Database, Connection)
{
  auto &sql_connection = database::Database::get_connection();

  std::string table_name = "test";

  std::stringstream sql_command;
  sql_command << "SELECT name FROM sqlite_master WHERE type='table' AND name='"
              << table_name << "';\n";

  std::string exists;
  try {
    sql_connection << sql_command.str(), soci::into(exists);
  } catch (soci::sqlite3_soci_error const &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << sql_command.str() << std::endl;
    throw std::runtime_error("Attempt to check if table exists failed.");
  }
}

auto main(int argc, char **argv) -> int
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
