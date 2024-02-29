import os

# Create the build environment
env = Environment()

# Get all .cpp files in the current directory and subdirectories
cpp_files = Glob('*.cpp') + Glob('**/*.cpp')

# Specify the target executable and its source files
env.Program(target='main', source=cpp_files)
