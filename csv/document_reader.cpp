#include "document_reader.h"

namespace sdf
{

StringDocumentReader::StringDocumentReader(const char* document) : document_(document)
{
}

char StringDocumentReader::get()
{
	char c = *document_;
	document_++;
	return c;
}

bool StringDocumentReader::eof()
{
	return *document_ == '\0';
}

}
