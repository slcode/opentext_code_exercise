#include <fstream>
#include <set>
#include <unordered_map>
#include <exception>
#include <iostream>

#include "HtmlConverter.h"

HtmlConverter::HtmlConverter() {}

HtmlConverter::~HtmlConverter() {}

std::string HtmlConverter::Convert(std::unique_ptr<tinyxml2::XMLDocument> document, std::string_view childName)
{
    std::string htmlContent = "<table>\n";
    std::set<std::string> columnTitles;

    // Try get the root element of the XML document
    tinyxml2::XMLElement *rootElement = document->RootElement();
    if (!rootElement)
    {
        return "";
    }

    // Iterate over elements to get the column titles
    for (tinyxml2::XMLElement *cdElement = rootElement->FirstChildElement(childName.data()); cdElement; cdElement = cdElement->NextSiblingElement(childName.data()))
    {
        for (tinyxml2::XMLElement *childElement = cdElement->FirstChildElement(); childElement; childElement = childElement->NextSiblingElement())
        {
            const char *tagName = childElement->Value();
            columnTitles.insert(tagName);
        }
    }

    htmlContent += "  <tr>\n";
    for (const std::string &columnTitle : columnTitles)
    {
        htmlContent += "    <th>" + columnTitle + "</th>\n";
    }
    htmlContent += "  </tr>\n";

    // Get the values, repalce missing with NULL.
    for (tinyxml2::XMLElement *cdElement = rootElement->FirstChildElement(childName.data()); cdElement; cdElement = cdElement->NextSiblingElement(childName.data()))
    {
        std::unordered_map<std::string, std::string> row;
        for (tinyxml2::XMLElement *childElement = cdElement->FirstChildElement(); childElement; childElement = childElement->NextSiblingElement())
        {
            const char *tagName = childElement->Value();
            const char *value = childElement->GetText();
            if (value != nullptr)
            {
                row[tagName] = value;
            }
        }

        htmlContent += "  <tr>\n";
        for (const std::string &tag : columnTitles)
        {
            htmlContent += "    <td>" + (row[tag] != "" ? row[tag] : "NULL") + "</td>\n";
        }
        htmlContent += "  </tr>\n";
    }

    htmlContent += "</table>\n";

    return htmlContent;
}

bool HtmlConverter::SaveToFile(std::string_view filename, std::string_view content)
{
    std::ofstream outputFile(filename);
    if (!outputFile)
    {
        return false;
    }

    outputFile << content;

    outputFile.close();

    return true;
}
