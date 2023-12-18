#include <gtest/gtest.h>
#include "csv.h"

constexpr static const char *basic_csv_string = R"(abc, de, f
4, 5_ , 6
 7, 8, 9_)";

TEST(CSV_read, from_string) {
	auto csv = sdf::read_csv_from_cstr(basic_csv_string);
	ASSERT_EQ(csv.get_row(0).get_entry(0), "abc");
	ASSERT_EQ(csv.get_row(0).get_entry(1), "de");
	ASSERT_EQ(csv.get_row(0).get_entry(2), "f");
	ASSERT_EQ(csv.get_row(1).get_entry(0), "4");
	ASSERT_EQ(csv.get_row(1).get_entry(1), "5_");
	ASSERT_EQ(csv.get_row(1).get_entry(2), "6");
	ASSERT_EQ(csv.get_row(2).get_entry(0), "7");
	ASSERT_EQ(csv.get_row(2).get_entry(1), "8");
	ASSERT_EQ(csv.get_row(2).get_entry(2), "9_");
}

