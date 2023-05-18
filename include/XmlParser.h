#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <memory>
#include <string>
#include "tinyxml2.h"

class XmlParser
{
public:
    XmlParser();
    ~XmlParser();

    bool LoadFile(const std::string &filename);
    std::unique_ptr<tinyxml2::XMLDocument> GetDocument();

private:
    std::unique_ptr<tinyxml2::XMLDocument> document;
};

#endif // XMLPARSER_H
