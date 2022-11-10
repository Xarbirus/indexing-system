#include "app/src/index_holder/filenames_storage.h"

#include <gtest/gtest.h>

TEST(filenames_storage, one_file)
{
  const std::filesystem::path path{"home/developer/test.txt"};
  const filenames_storage::filename master_value{0, 1, 2};

  filenames_storage storage;
  EXPECT_EQ(master_value, *storage.add_file(path));
  EXPECT_EQ(1, storage.size());
}

TEST(filenames_storage, duplicate_file)
{
  const std::filesystem::path path{"home/developer/test.txt"};
  const filenames_storage::filename master_value{0, 1, 2};

  filenames_storage storage;

  auto first_index = storage.add_file(path);
  EXPECT_EQ(master_value, *first_index);
  EXPECT_EQ(1, storage.size());

  auto second_index = storage.add_file(path);
  EXPECT_EQ(master_value, *second_index);
  EXPECT_EQ(1, storage.size());

  EXPECT_EQ(first_index, second_index);
}

TEST(filenames_storage, same_name)
{
  const std::filesystem::path first_path{"foo/test.txt"};
  const std::filesystem::path second_path{"bar/test.txt"};

  filenames_storage storage;
  EXPECT_EQ(storage.add_file(second_path)->at(1), storage.add_file(first_path)->at(1));
  EXPECT_EQ(2, storage.size());
}

TEST(filenames_storage, same_dir)
{
  const std::filesystem::path first_path{"test/foo.txt"};
  const std::filesystem::path second_path{"test/bar.txt"};

  filenames_storage storage;
  EXPECT_EQ(storage.add_file(second_path)->at(0), storage.add_file(first_path)->at(0));
  EXPECT_EQ(2, storage.size());
}

TEST(filenames_storage, get_file)
{
  const std::filesystem::path path{"foo/bar/test.txt"};

  filenames_storage storage;
  auto indices = storage.add_file(path);
  EXPECT_EQ(1, storage.size());

  const auto returned_path = storage.get_file(indices);
  EXPECT_TRUE(returned_path);
  EXPECT_EQ(*returned_path, path);
}

TEST(filenames_storage, get_short)
{
  const std::filesystem::path path{"foo/bar/test.txt"};

  filenames_storage storage;
  auto indices = storage.add_file(path);
  EXPECT_EQ(1, storage.size());

  const filenames_storage::filename new_indices{indices->begin(), indices->end() - 1};
  const auto returned_path = storage.get_file(&new_indices);
  EXPECT_TRUE(returned_path);
  EXPECT_EQ(*returned_path, path.parent_path());
}

TEST(filenames_storage, nonexistent_file)
{
  filenames_storage storage;
  filenames_storage::filename false_indices;

  auto returned_path = storage.get_file(nullptr);
  EXPECT_FALSE(returned_path);

  returned_path = storage.get_file(&false_indices);
  EXPECT_FALSE(returned_path);

  false_indices = {1, 2, 3};
  returned_path = storage.get_file(&false_indices);
  EXPECT_FALSE(returned_path);

  auto true_indices = storage.add_file("foo/bar/test.txt");
  EXPECT_EQ(1, storage.size());

  false_indices.clear();
  std::transform(true_indices->begin(), true_indices->end(), std::back_inserter(false_indices), [](auto value){ return value * 2; });
  returned_path = storage.get_file(&false_indices);
  EXPECT_FALSE(returned_path);
}