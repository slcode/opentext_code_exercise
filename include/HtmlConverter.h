#ifndef HTMLCONVERTER_H
#define HTMLCONVERTER_H

#include <memory>
#include <string_view>

#include "tinyxml2.h"

class HtmlConverter
{
public:
    HtmlConverter();
    ~HtmlConverter();

    std::string Convert(std::unique_ptr<tinyxml2::XMLDocument> document, std::string_view childName);
    bool SaveToFile(std::string_view filename, std::string_view content);
};

#endif // HTMLCONVERTER_H
