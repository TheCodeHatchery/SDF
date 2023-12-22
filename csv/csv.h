#pragma once

#include <map>
#include <string>
#include <vector>

namespace sdf
{

/*
* I think it makes more sense for it to store things as a table rather than "csv" file.
* However, I think there's such thing as an unofficial csv comment which we maybe want to access, 
* so we can have the CSV class for that extra feature. It should support slicing down to a Table.
* 
* One design problem here, is we want to be able to write out from either a Table or CSV object.
* The CSV object should call the Table method, but insert the comments back.
*/


/*
* CSV read_csv_from_data();
* CSV read_csv_from_stream();
* 
* write_csv_to_data(CSV, data);
* write_csv_to_data(Table, data);
* etc...
* 
* Maybe:
* JSON (whatever we call it, maybe Tree or Object) read_csv_from_data_as_json();
* JSON (whatever we call it, maybe Tree or Object) read_csv_from_stream_as_json();
*/

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

	//void append_row(TableRow row);
	//void append_comment(std::string comment);

	// TODO: do we support accessing by column names? Here or in Table or in TableRow?

	// TODO: insert_row, insert_comment

private:
	bool has_header_row_; // if true, first value of rows_ is the name of every column
	std::vector<CSVRow> rows_;

	// map of comment lines and where they are.
	// TODO: does this really work as far as the CSV being edited?
	std::map<int, std::string> comments_;
};

template<typename Document>
CSV read_csv(Document& document);

CSV read_csv_from_cstr(const char *cstr);

}

#include "parser.inl"
