#include <iostream>
#include <memory>

#include "XmlParser.h"
#include "HtmlConverter.h"

int main(int argc, const char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <input filename>  <output filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    auto xmlParser = std::make_unique<XmlParser>();

    if (!xmlParser->LoadFile(filename))
    {
        std::cout << "Failed to load XML file: " << filename << std::endl;
        return 1;
    }

    std::unique_ptr<HtmlConverter> htmlConverter = std::unique_ptr<HtmlConverter>();

    // Convert XML to HTML
    std::string htmlContent = htmlConverter->Convert(xmlParser->GetDocument(), "CD");
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
