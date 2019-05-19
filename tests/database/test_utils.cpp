#include "DummyStorable.hpp"
#include "database/utils.hpp"

#include <gtest/gtest.h>

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

TEST_F(Utils, Table)
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

TEST_F(Utils, Count)
{
  size_t count = utils::count_rows<DummyStorable>();
  EXPECT_EQ(count, 0) << "Expected to count 0 rows. count: " << count;

  for (size_t i = 0; i < 100; ++i) {
    auto &storable = utils::make<DummyStorable>("dummy");
    EXPECT_EQ(storable.id(), i + 1)
        << "Expected id: " << i + 1 << " actual: " << storable.id();
  }

  count = utils::count_rows<DummyStorable>();
  EXPECT_EQ(count, 100) << "Expected to count 100 rows. count: " << count;

  auto &all_storables = utils::retrieve_all<DummyStorable>();
  while (!all_storables.empty()) {
    utils::delete_storable(all_storables.back());
  }

  count = utils::count_rows<DummyStorable>();
  EXPECT_EQ(count, 0)
      << "Expected to count 0 rows after deleting everything. count: " << count;
}

auto main(int argc, char **argv) -> int
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
