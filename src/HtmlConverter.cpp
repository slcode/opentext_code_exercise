#include <fstream>
#include <set>
#include <unordered_map>
#include "HtmlConverter.h"

HtmlConverter::HtmlConverter() {}

HtmlConverter::~HtmlConverter() {}

std::string HtmlConverter::Convert(std::unique_ptr<tinyxml2::XMLDocument> document)
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
    for (tinyxml2::XMLElement *cdElement = rootElement->FirstChildElement("CD"); cdElement; cdElement = cdElement->NextSiblingElement("CD"))
    {
        for (tinyxml2::XMLElement *childElement = cdElement->FirstChildElement(); childElement; childElement = childElement->NextSiblingElement())
        {
            std::string tagName = childElement->Value();
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
    for (tinyxml2::XMLElement *cdElement = rootElement->FirstChildElement("CD"); cdElement; cdElement = cdElement->NextSiblingElement("CD"))
    {
        std::unordered_map<std::string, std::string> row;
        for (tinyxml2::XMLElement *childElement = cdElement->FirstChildElement(); childElement; childElement = childElement->NextSiblingElement())
        {
            std::string tagName = childElement->Value();
            std::string value = childElement->GetText();
            row[tagName] = value;
        }

        htmlContent += "  <tr>\n";
        for (const auto &tag : columnTitles)
        {
            htmlContent += "    <td>" + (row[tag] != "" ? row[tag] : "NULL") + "</td>\n";
        }
        htmlContent += "  </tr>\n";
    }

    htmlContent += "</table>\n";

    return htmlContent;
}

bool HtmlConverter::SaveToFile(const std::string &filename, const std::string &content)
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
