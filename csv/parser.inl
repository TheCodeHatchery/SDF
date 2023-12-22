namespace sdf
{

namespace impl {

inline bool is_space(char c)
{
	return c <= 32; // TODO: more precise? Or is this fine?
}

}

template<typename Document>
CSV read_csv(Document& document)
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

	CSVRow current_row;
	std::string entry;

	auto add_entry = [&current_row, &entry]()
	{
		while (impl::is_space(entry.back()))
		{
			entry.pop_back();
		}
		current_row.append_entry(entry);
		entry.clear();
	};

	char old_c = '\0';
	while (!document.eof())
	{
		char c = (old_c == '\0' ? document.get() : old_c);
		old_c = '\0';
		if (state == NOTHING)
		{
			if (impl::is_space(c))
			{
				continue;
			}
			else if (c == '"')
			{
				state = PARSE_STATE::ENTRY_PARENTHESIS;
			}
			else
			{
				state = PARSE_STATE::ENTRY;
				// no increment so we get the first char properly
				old_c = c;
			}
		}
		else if (state == ENTRY)
		{
			if (c == row_delimiter)  // newline
			{
				add_entry();

				csv.append_row(current_row);

				current_row.clear();
				state = NOTHING;
			}
			else if (c == column_delimiter) // new record finished
			{
				add_entry();
				state = NOTHING;
			}
			else
			{
				entry.push_back(c);
			}
		}
		else if (state == ENTRY_PARENTHESIS)
		{
			throw "Nope!"; // TODO
		}
	}

	if (!entry.empty())
	{
		add_entry();
	}
	if (!current_row.empty())
	{
		csv.append_row(current_row);
	}

	return csv;
}

}
