#pragma once

namespace sdf
{

// The interface is as follows
// char get()
// bool eof()
class StringDocumentReader
{
public:
	// assumes document is a null terminated string
	StringDocumentReader(const char *document);
	char get();
	bool eof();

private:
	const char *document_;
};

}
