# FakeFS
A fake filesystem based on FUSE. This "big homework" (大作业) is a part of operating system course in School of Software, South China University of Technology. 

# Build Instructions 
1. Install [DaveGamble/cJSON](https://github.com/DaveGamble/cJSON). 
2. Install [libfuse](https://github.com/libfuse/libfuse). You may do this by using your package manager. 
3. Clone this project. 
4. Make a `build` directory, and run `cmake ..` in it, then, `make`. 

# Usage
1. Make 2 directories: a mount point and a directory to store actual files. 
2. `./ffs_formatter -d <actual_file_path_absolutely>`
3. After instruction #2, you have a `fakefs.json` file. Make sure that this JSON file is in your working directory when invoking `fakefs` executable. 
4. `./fakefs <mount point>`
5. You now successfully mounted this FakeFS. 