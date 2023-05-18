# opentext_code_exercise

# Brief
* I used a third party library tinyxml to parse the input files. While there are many xml parsing libraries, I used tinyxml is small and simple.

* I did not add much validatioin of the input. Schema validation might be needed depends on the use cases.

* "CD" is hard code in the html converter. This could be passed as an argument if needed.

* Missing values are replaced by NULL value.

* Only tested on MacOS because of resource and time constraint. 



# How to use
Under the project folder, where the CMakeLists.txt locates, run below to compile it.

```rm -rf build && mkdir build && cd build && cmake .. && make && cd ..```

Then to run it (note the input file cd_cataglog.xml is not included in this repo)

```./build/xml_to_html cd_catalog.xml output.html```

The output will be in the output.html file.

# TODO
Add unit test.
