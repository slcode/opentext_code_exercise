#ifndef HTMLCONVERTER_H
#define HTMLCONVERTER_H

#include <memory>
#include <string>
#include "tinyxml2.h"

class HtmlConverter
{
public:
    HtmlConverter();
    ~HtmlConverter();

    std::string Convert(std::unique_ptr<tinyxml2::XMLDocument> document);
    bool SaveToFile(const std::string &filename, const std::string &content);
};

#endif // HTMLCONVERTER_H
