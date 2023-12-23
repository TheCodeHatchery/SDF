#include <gtest/gtest.h>
#include "csv.h"

constexpr static const char* basic_csv_string = R"(abc, de, f
4#, 5_ , 6
 7, 8, 9_)";

constexpr static const char* quote_csv_string = R"("1, 2, 3 ", b, c
d e f, " quote: "" <-" , """This is, a quote""")";

constexpr static const char* comments_csv_string = R"(#This is a test
 #   Of multiple comment lines
a, #
"#Not a comment", #hashtag
# Second comment
b, c
#Final Comment)";

TEST(CSV_parse, basic) {
	auto csv = sdf::read_csv_from_cstr(basic_csv_string);
	ASSERT_EQ(csv.get_row(0).get_entry(0), "abc");
	ASSERT_EQ(csv.get_row(0).get_entry(1), "de");
	ASSERT_EQ(csv.get_row(0).get_entry(2), "f");
	ASSERT_EQ(csv.get_row(1).get_entry(0), "4#");
	ASSERT_EQ(csv.get_row(1).get_entry(1), "5_");
	ASSERT_EQ(csv.get_row(1).get_entry(2), "6");
	ASSERT_EQ(csv.get_row(2).get_entry(0), "7");
	ASSERT_EQ(csv.get_row(2).get_entry(1), "8");
	ASSERT_EQ(csv.get_row(2).get_entry(2), "9_");
}

TEST(CSV_parse, quote) {
	auto csv = sdf::read_csv_from_cstr(quote_csv_string);
	ASSERT_EQ(csv.get_row(0).get_entry(0), "1, 2, 3 ");
	ASSERT_EQ(csv.get_row(0).get_entry(1), "b");
	ASSERT_EQ(csv.get_row(0).get_entry(2), "c");
	ASSERT_EQ(csv.get_row(1).get_entry(0), "d e f");
	ASSERT_EQ(csv.get_row(1).get_entry(1), " quote: \" <-");
	ASSERT_EQ(csv.get_row(1).get_entry(2), "\"This is, a quote\"");
}

TEST(CSV_parse, comment) {
	auto csv = sdf::read_csv_from_cstr(comments_csv_string);
	ASSERT_EQ(csv.get_row(0).get_entry(0), "a");
	ASSERT_EQ(csv.get_row(0).get_entry(1), "#");
	ASSERT_EQ(csv.get_row(1).get_entry(0), "#Not a comment");
	ASSERT_EQ(csv.get_row(1).get_entry(1), "#hashtag");
	ASSERT_EQ(csv.get_row(2).get_entry(0), "b");
	ASSERT_EQ(csv.get_row(2).get_entry(1), "c");

	ASSERT_EQ(csv.get_comment(0), "This is a test\n   Of multiple comment lines\n");
	ASSERT_EQ(csv.get_comment(1), "");
	ASSERT_EQ(csv.get_comment(2), " Second comment\n");
	ASSERT_EQ(csv.get_comment(3), "Final Comment"); // TODO: Do we want this to also end in a \n for constency?
}

