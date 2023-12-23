#pragma once

#include <map>
#include <string>
#include <vector>

namespace sdf
{

class CSVRow
{
public:
	CSVRow();

	void clear();
	void append_entry(std::string entry);

	bool empty() const;

	const std::string &get_entry(size_t idx) const;
private:
	std::vector<std::string> entries_;
};

class CSV
{
public:
	// construct an empty csv
	CSV();

	void append_row(CSVRow row);
	const CSVRow& get_row(size_t idx) const;

	void append_comment(const std::string& comment);
	std::string get_comment(size_t row_idx) const;
	//void append_row(TableRow row);
	//void append_comment(std::string comment);

	// TODO: do we support accessing by column names? Here or in Table or in TableRow?

	// TODO: insert_row, insert_comment

private:
	bool has_header_row_; // if true, first value of rows_ is the name of every column
	std::vector<CSVRow> rows_;

	// map of comment lines and what entry they are connected to.
	// So the top comment is at 0, and a comment at the end of the document is at rows_.size()
	std::map<int, std::string> comments_;
};

struct CSVParseSettings
{
	char field_delimiter = ',';
	char comment_prefix = '#';
};

template<typename Document>
CSV read_csv(Document& document, const CSVParseSettings &settings = {});

CSV read_csv_from_cstr(const char *cstr, const CSVParseSettings &settings = {});

}

#include "parser.inl"
