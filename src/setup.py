from distutils.core import setup, Extension

module1 = Extension('ccsv', sources=['ccsv_types.c'])

setup (name = 'ccsv',
        version = '1.0',
        description = 'Query csv files with sql-like methods.',
        ext_modules = [module1])


