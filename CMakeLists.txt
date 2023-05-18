cmake_minimum_required(VERSION 3.12)

project(XmlToHtml)

set(CMAKE_CXX_STANDARD 17)

include_directories(include third-party)

set(SOURCES
    src/main.cpp
    src/XmlParser.cpp
    src/HtmlConverter.cpp
    third-party/tinyxml2.cpp
)

add_executable(xml_to_html ${SOURCES})
