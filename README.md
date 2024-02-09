# ccsv

*This repo is still under development.*

ccsv (C-csv) is a csv parser written for Python in C. Its main purpose was a learning project for myself to understand memory allocation in C as well as familiarize myself with the Python-C api. 

I wanted to write a simple csv parser that let the user interface with Csv files in a quick and intuitive manner. Sometimes when scripting, I would like to quickly read in a csv file, filter it for a specific condition, and quickly examine the results. I don't want to import and rely on Pandas for such a relatively simple task. I wanted the parser to be quick as I often work with relatively large files, which is why I wrote it in C initially. However, as I wrote more of the parser, I realized I wanted it to be easily extendable, which is why I adapted it to the Python-C api.

## TODO:
1. Write a method to read in the entire file into memory. Store as a tuple of tuples. 
