


## Description 


* The point of this project is to write a function that returns a line read from a file descriptor.

* `static variables` is one of the important thing in C to keep the address of a variable in memory even if the function that the variable in is finished.
* File descriptors are an important concept connected with a process. A file descriptor is an index into a file descriptor table maintained by the operating system for each process. This table contains references to open files, sockets, pipes, and other I/O resources. The file descriptor table points to kernel structures that store information about open files, which are connected to the filesystem. This allows the process to read from and write to files using system calls. You can inspect file descriptors of a process in the /proc/<pid>/fd directory.

  ```bash
  Process ->
  File Descriptor Table
      ├── 0 → stdin
      ├── 1 → stdout
      ├── 2 → stderr
      └── 3 → pointer to open file object
  ```
* The fd table entries point to kernel open file objects, not directly to files.

```bash
Process
 └── FD table
      └── points to
           Open File Object (in kernel)
                └── points to
                     inode (actual file metadata)
```
Kernel maintains:
* open file table (system-wide)
* inode table (file metadata)
* filesystem structures
  
This allows:
* multiple processes to open same file
* shared offsets
* permissions control


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

 * [42-cursus](https://42-cursus.gitbook.io/guide/1-rank-01/get_next_line): A very good.
   
