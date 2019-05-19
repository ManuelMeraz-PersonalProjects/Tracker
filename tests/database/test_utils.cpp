#include "DummyStorable.hpp"
#include "database/Data.hpp"
#include "database/utils.hpp"

#include <gtest/gtest.h>
#include <range/v3/all.hpp>

#include <vector>

namespace utils = database::utils;

namespace {

class Utils : public ::testing::Test {
protected:
  void SetUp() override
  {
    utils::drop_table<DummyStorable>();
  }

  void TearDown() override
  {
    utils::drop_table<DummyStorable>();
  }
};

} // namespace

TEST_F(Utils, CreateAndDropTable)
{
  EXPECT_EQ(utils::table_exists<DummyStorable>(), false)
      << "Table should not exist at beginning of test.";

  auto &storable = utils::make<DummyStorable>("dummy");
  EXPECT_EQ(utils::table_exists<DummyStorable>(), true)
      << "Storable made and table does not exist.";

  EXPECT_EQ(storable.id(), 1) << "First storable must have an id of 1.";
  EXPECT_EQ(storable.name(), "dummy") << "First storable must have an id of 1.";
  EXPECT_EQ(utils::retrieve_all<DummyStorable>().front().id(), 1)
      << "First storable must have an id of 1.";

  utils::drop_table<DummyStorable>();
  EXPECT_EQ(utils::table_exists<DummyStorable>(), false)
      << "Table dropped and still exists.";
}

TEST_F(Utils, BinaryFind)
{
  std::vector<int> nums = {1, 2, 3};

  auto const compare = [](int lhs, int rhs) { return lhs < rhs; };

  auto found = utils::binary_find(begin(nums), end(nums), 2, compare);
  EXPECT_EQ(*found, 2) << "Binary find failed to find a value";

  found = utils::binary_find(begin(nums), end(nums), 50, compare);
  EXPECT_EQ(found, end(nums))
      << "Binary find should not have found non existing value";

  nums = {};

  found = utils::binary_find(begin(nums), end(nums), 2, compare);
  EXPECT_EQ(found, end(nums)) << "Binary find failed to find a value";
}

TEST_F(Utils, CountDelete)
{
  size_t count = utils::count_rows<DummyStorable>();
  EXPECT_EQ(count, 0) << "Expected to count 0 rows. count: " << count;

  for (size_t i = 0; i < 20; ++i) {
    auto &storable = utils::make<DummyStorable>("dummy");
    EXPECT_EQ(storable.id(), i + 1)
        << "Expected id: " << i + 1 << " actual: " << storable.id();
  }

  count = utils::count_rows<DummyStorable>();
  EXPECT_EQ(count, 20) << "Expected to count 20 rows. count: " << count;

  auto &all_storables = utils::retrieve_all<DummyStorable>();
  while (!all_storables.empty()) {
    utils::delete_storable(all_storables.back());
  }

  count = utils::count_rows<DummyStorable>();
  EXPECT_EQ(count, 0)
      << "Expected to count 0 rows after deleting everything. count: " << count;
}

TEST_F(Utils, Count)
{
  size_t count = utils::count_rows<DummyStorable>();
  EXPECT_EQ(count, 0) << "Expected to count 0 rows. count: " << count;

  for (size_t i = 0; i < 20; ++i) {
    auto &storable = utils::make<DummyStorable>("dummy");
    EXPECT_EQ(storable.id(), i + 1)
        << "Expected id: " << i + 1 << " actual: " << storable.id();
  }

  count = utils::count_rows<DummyStorable>();
  EXPECT_EQ(count, 20) << "Expected to count 20 rows. count: " << count;

  auto &all_storables = utils::retrieve_all<DummyStorable>();
  while (!all_storables.empty()) {
    utils::delete_storable(all_storables.back());
  }

  count = utils::count_rows<DummyStorable>();
  EXPECT_EQ(count, 0)
      << "Expected to count 0 rows after deleting everything. count: " << count;
}

TEST_F(Utils, Enums)
{
  std::vector<std::string_view> enum_strings = {
      utils::enum_to_string(database::DataType::REAL),
      utils::enum_to_string(database::DataType::INTEGER),
      utils::enum_to_string(database::DataType::TEXT),
      utils::enum_to_string(database::DataType::NULL_),
      utils::enum_to_string(database::DataType::BLOB),
      utils::enum_to_string(database::Constraint::PRIMARY_KEY),
      utils::enum_to_string(database::Constraint::UNIQUE),
      utils::enum_to_string(database::Constraint::NOT_NULL),
      utils::enum_to_string(database::Constraint::CHECK),
  };

  std::vector<std::string_view> expected_values = {
      "REAL",        "INTEGER", "TEXT",     "NULL", "BLOB",
      "PRIMARY KEY", "UNIQUE",  "NOT NULL", "CHECK"};

  for (auto const &[enum_string, expected] :
       ranges::view::zip(enum_strings, expected_values)) {
    EXPECT_EQ(enum_string, expected)
        << "expected: " << expected << " enum string: " << enum_string;
  }
}

TEST_F(Utils, TypeToString)
{
  std::string type_string = utils::type_to_string<DummyStorable>();
  EXPECT_EQ(type_string, "DummyStorable")
      << "expected: DummyStorable type_to_string: " << type_string;
}

TEST_F(Utils, Update)
{
  auto &all_storables = utils::retrieve_all<DummyStorable>();
  for (size_t i = 0; i < 20; ++i) {
    utils::make<DummyStorable>("dummy");
  }

  for (auto &storable : all_storables) {
    storable.set_name("updated");
  }

  all_storables = utils::retrieve_all<DummyStorable>();
  for (auto &storable : all_storables) {
    std::string const name = storable.name();
    EXPECT_EQ(name, "updated") << "expected: updated  actual: " << name;
  }
}

auto main(int argc, char **argv) -> int
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
