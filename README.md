
* *This activity has been created as part of
the 42 curriculum by* aqoraan.


## Description 

* The point of this project is to write a function that returns a line read from a file descriptor.
## Instruction 

*  To compile the project, include the source files in your program compilation command. For example:
```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o obj
```

* Run your compiled program and provide a file as input:
```bash
./a.out file.txt
```

* The program should display the file content **line by line**, calling `get_next_line()` repeatedly until it returns `NULL`.

 * `BUFFER_SIZE` can be defined during compilation:
 ```bash
 cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c
 ```

**The function must:**
- return the next line including the newline `\n`.
- return `NULL` on EOF or error.
- work with any valid file descriptor.
- handle multiple FDs if required by your project version.


## Resources

### **Documentation & References**

- `man read`
- Memory management in C:
    - [GeeksForGeeks](https://www.geeksforgeeks.org/c/static-variables-in-c/)
- File descriptor concepts:
    - [Linux Documentation](https://docs.kernel.org/filesystems/files.html) – File Descriptors Overview
    - [42-cursus_gitbook](https://42-cursus.gitbook.io/guide/1-rank-01/get_next_line/open-and-read).