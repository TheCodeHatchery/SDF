namespace sdf
{

namespace impl {

inline bool is_space(char c)
{
	return c <= 32; // TODO: more precise? Or is this fine?
}

enum PARSE_STATE
{
	NOTHING,
	ENTRY,
	ENTRY_PARENTHESIS,
};

// maybe only accept '\n' or '\r\n' as the unofficial spec wants (CRLF). Make it an option? Even '\n\r' for funzies
const char row_delimiter = '\n';

template<typename Document>
class CSVParser
{
public:
	CSVParser(Document& document, const CSVParseSettings& settings) : document_(document), settings_(settings) {}
	CSV parse()
	{
		// Giving name to the rows is optional. Maybe default them to @_0_@, @_1_@, @_2_@, etc...
		const bool include_headers = true; // TODO

		while (!document_.eof())
		{
			char c = document_.get();

			if (state_ == NOTHING)
			{
				parse_nothing(c);
			}
			else if (state_ == ENTRY)
			{
				parse_entry(c);
			}
			else if (state_ == ENTRY_PARENTHESIS)
			{
				parse_entry_parenthesis(c);
			}
		}

		if (!entry_.empty())
		{
			add_entry();
		}
		if (!current_row_.empty())
		{
			csv_.append_row(current_row_);
		}

		return csv_;
	}

	void add_entry()
	{
		while (!entry_.empty() && is_space(entry_.back()))
		{
			entry_.pop_back();
		}

		current_row_.append_entry(entry_);
		entry_.clear();
	};

	void parse_nothing(char c)
	{
		if (c == '"')
		{
			state_ = ENTRY_PARENTHESIS;
		}
		else if (c == settings_.comment_prefix && entry_.empty() && current_row_.empty())
		{
			std::string comment_text;
			char comment_char;
			while ((comment_char = document_.get()) != '\0')
			{
				comment_text.push_back(comment_char);
				if (comment_char == row_delimiter)
				{
					// intentionally include '\n' so we end up concating multiple comment lines into one comment
					break;
				}
			}
			csv_.append_comment(comment_text);
		}
		else if (is_space(c))
		{
			return;
		}
		else
		{
			state_ = ENTRY;
			parse_entry(c);
		}
	}

	void parse_entry(char c)
	{
		if (c == row_delimiter)  // newline
		{
			add_entry();

			csv_.append_row(current_row_);

			current_row_.clear();
			state_ = NOTHING;
		}
		else if (c == settings_.field_delimiter) // new record finished
		{
			add_entry();
			state_ = NOTHING;
		}
		else
		{
			entry_.push_back(c);
		}
	}

	void parse_entry_parenthesis(char c)
	{
		if (c == '"') // new record finished
		{
			if (document_.eof())
			{
				// edge case. TODO: add test to cover this
				current_row_.append_entry(entry_);
				entry_.clear();
				return;
			}

			char peek = document_.get();
			if (peek == '"')
			{
				// two quotes is how a quote is escaped!
				entry_.push_back(c);
			}
			else
			{
				// add entry_ completely unedited (unlike what add_entry()) does
				current_row_.append_entry(entry_);
				entry_.clear();

				while (!document_.eof())
				{
					// eat until next seperator.
					if (peek == settings_.field_delimiter)
					{
						break;
					}
					if (!is_space(peek))
					{
						throw "whatever";
					}
					peek = document_.get();
				}

				state_ = NOTHING;
			}
		}
		else
		{
			entry_.push_back(c);
		}
	}

private:
	Document& document_;
	const CSVParseSettings& settings_;

	PARSE_STATE state_ = NOTHING;
	CSVRow current_row_;
	std::string entry_;
	CSV csv_;
};

}

template<typename Document>
CSV read_csv(Document& document, const CSVParseSettings &settings)
{
	return impl::CSVParser(document, settings).parse();
}

}
