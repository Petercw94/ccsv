# csv-parser

*This repo is still under development.*

## TODO:
1. TypeCheck the file_name attribute on init to ensure it is a string
2. Add get_headers to the init and return an instance variable dict called headers for indexing filters
3. Add a filter method that will take in an index or a header and a search pattern and will search the 
specified column for that pattern. Return a tuple of rows found that match the provided pattern. 
