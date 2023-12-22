#pragma once

namespace sdf
{

// The interface is as follows
// char get()
// bool eof()
class StringDocument
{
public:
	// assumes document is a null terminated string
	StringDocument(const char *document);
	char get();
	bool eof();

private:
	const char *document_;
};

}
