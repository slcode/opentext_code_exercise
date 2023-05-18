#include "XmlParser.h"

XmlParser::XmlParser() : document(std::make_unique<tinyxml2::XMLDocument>()) {}

XmlParser::~XmlParser() {}

bool XmlParser::LoadFile(const std::string &filename)
{
    return document->LoadFile(filename.c_str()) == tinyxml2::XML_SUCCESS;
}

std::unique_ptr<tinyxml2::XMLDocument> XmlParser::GetDocument()
{
    return std::move(document);
}
