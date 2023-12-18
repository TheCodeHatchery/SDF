#include "csv.h"


namespace sdf
{

bool is_space(char c)
{
	return c <= 32; // TODO: more precise? Or is this fine?
}




TableRow::TableRow()
{
	;
}
void TableRow::clear()
{
	entries_.clear();
}
void TableRow::append_entry(std::string entry)
{
	entries_.push_back(std::move(entry));
}
const std::string& TableRow::get_entry(size_t idx) const
{
	return entries_.at(idx);
}



Table::Table()
{
	;
}
void Table::append_row(TableRow row)
{
	rows_.push_back(std::move(row));
}
const TableRow& Table::get_row(size_t idx) const
{
	return rows_.at(idx);
}




CSV::CSV()
{
	;
}



enum PARSE_STATE
{
	NOTHING,
	ENTRY,
	ENTRY_PARENTHESIS,
};

CSV read_csv_from_cstr(const char* cstr)
{
	// In the future could be multiple characters, but for the MVP, get anything working
	const char column_delimiter = ',';
	// maybe only accept '\n' or '\r\n' as the unofficial spec wants (CRLF). Make it an option? Even '\n\r' for funzies
	const char row_delimiter = '\n';

	// Giving name to the rows is optional. Maybe default them to @_0_@, @_1_@, @_2_@, etc...
	const bool include_headers = true;

	// TODO: handle double quotes correctly! "" = " somehow...

	PARSE_STATE state = PARSE_STATE::NOTHING;

	CSV csv;

	const char *iter = cstr;
	TableRow current_row;
	std::string entry;
	while (*iter != '\0')
	{
		if (state == NOTHING)
		{
			if (is_space(*iter))
			{
				iter++;
				continue;
			}
			else if(*iter == '"')
			{
				state = PARSE_STATE::ENTRY_PARENTHESIS;
				iter++;
			}
			else
			{
				state = PARSE_STATE::ENTRY;
				// no increment so we get the first char properly
			}
		}
		else if (state == ENTRY)
		{
			if (*iter == row_delimiter)  // newline
			{
				current_row.append_entry(entry);
				entry.clear();

				csv.append_row(current_row);

				current_row.clear();
				state = NOTHING;
			}
			else if (*iter == column_delimiter) // new record finished
			{
				current_row.append_entry(entry);
				entry.clear();
				state = NOTHING;
			}
			else
			{
				entry.push_back(*iter);
			}
			iter++;
		}
		else if (state == ENTRY_PARENTHESIS)
		{
			throw "Nope!"; // TODO
		}
	}

	return csv;
}

}