#include "csv.h"
#include "document_reader.h"

namespace sdf
{

CSVRow::CSVRow()
{
	;
}
void CSVRow::clear()
{
	entries_.clear();
}
void CSVRow::append_entry(std::string entry)
{
	entries_.push_back(std::move(entry));
}
bool CSVRow::empty() const
{
	return entries_.empty();
}
const std::string& CSVRow::get_entry(size_t idx) const
{
	return entries_.at(idx);
}



CSV::CSV()
{
	;
}
void CSV::append_row(CSVRow row)
{
	rows_.push_back(std::move(row));
}

const CSVRow& CSV::get_row(size_t idx) const
{
	return rows_.at(idx);
}

void CSV::append_comment(const std::string& comment)
{
	comments_[rows_.size()] += comment;
}

std::string CSV::get_comment(size_t row_idx) const
{
	if (comments_.count(row_idx) == 1)
	{
		return comments_.at(row_idx);
	}
	return "";
}


CSV read_csv_from_cstr(const char* cstr, const CSVParseSettings& settings)
{
	StringDocument reader(cstr);
	return read_csv<StringDocument>(reader, settings);
}

}