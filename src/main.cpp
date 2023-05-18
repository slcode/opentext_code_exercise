#include <iostream>
#include <memory>
#include "XmlParser.h"
#include "HtmlConverter.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <input filename>  <output filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    auto xmlParser = std::make_shared<XmlParser>();

    if (!xmlParser->LoadFile(filename))
    {
        std::cout << "Failed to load XML file: " << filename << std::endl;
        return 1;
    }

    std::unique_ptr<tinyxml2::XMLDocument> document = xmlParser->GetDocument();
    std::unique_ptr<HtmlConverter> htmlConverter = std::unique_ptr<HtmlConverter>();

    // Convert XML to HTML
    std::string htmlContent = htmlConverter->Convert(std::move(document));
    std::string outputFilename = argv[2];
    if (htmlConverter->SaveToFile(outputFilename, htmlContent))
    {
        std::cout << "HTML saved to: " << outputFilename << std::endl;
    }
    else
    {
        std::cout << "Failed to save HTML to file: " << outputFilename << std::endl;
        return 1;
    }

    return 0;
}
