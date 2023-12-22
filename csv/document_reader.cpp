#include "document_reader.h"

namespace sdf
{

StringDocument::StringDocument(const char* document) : document_(document)
{
}

char StringDocument::get()
{
	char c = *document_;
	document_++;
	return c;
}

bool StringDocument::eof()
{
	return *document_ == '\0';
}

}
