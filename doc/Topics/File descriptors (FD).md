

process
  └── fd (int)
       └── per-process fd table entry
            └── system-wide open file description
                 └── inode (actual file)



### What is a File Descriptor ?

A file descriptor is an `int` variable that uniquely identifies an open file.

### Terminology

Before going further with the explanation, I have to describe some terms that I will use on this page.

<table><thead><tr><th width="281">Term</th><th>Description</th></tr></thead><tbody><tr><td>File Descriptor</td><td>This is the index of the File Table Entry in the file descriptor table.</td></tr><tr><td>File Descriptor Table</td><td>This is an array of File Table Entry, each process gets its own File Descriptor Table.</td></tr><tr><td>File Table Entry</td><td>A File Table Entry is a structure that contains informations about a file.</td></tr><tr><td>Global File Table</td><td>This is a system wide table containing all files.<br>(It can't contain all files at once but the operating system will automatically update the table if you request a file that's not in this table).</td></tr></tbody></table>

# What happened internally

* Now for every process it has it's own `fd` table.
* A `fd` is an index that points to an entry in the global (system-wide) file table.
* Each entry in the system-wide file table has information about any file opened or default (terminal) in it.
	* Like (Offset, permission, mode, inode, ....)
* ![[WhatsApp Image 2026-01-07 at 5.28.42 PM.jpeg]]

![[WhatsApp Image 2026-01-07 at 5.28.42 PM(1).jpeg]]

* So as in the second picture when I run `./test &` for example, which is a C file that runs in the background, now a new process has been made, you can see it's files and content and it's `fd` in `/proc/<pid>/fd`.
	* By default I have `0(input),1(output) and 2(error)`.
	* 
	>[!note] you can see the pid for any process by `pidof` or `echo $!` (pid for last process).


When you use a file descriptor, with the `read(2)` function for example, the following will happen :

1. Search for the file in the Global file table
   2. If the file is found, go to next step.
   3. If the file is not found, the operating system will update the Global file table to make the requested file available, then go back to step 1.
4. Create a File table entry in the File descriptor table for the requested file.
5. Assign the first unused File descriptor to the created file table entry.


### Standard file descriptors

In C, like in most Unix systems, there are 3 standards file descriptors that are automatically added to the file descriptor table. These file descriptors are the standard input/output file descriptor and always have these values :

* 0 : this file descriptor represents the stdin (=> standard input, the terminal). This is the file descriptor used when reading user input from the terminal.
* 1 : this file descriptor represents the stdout (=> standard output, the terminal). This is the file descriptor used when writing to the terminal.
* 2 : this file descriptor represents the stderr (=> standard error output, the terminal). This is the file descriptor used when writing an error to the terminal, the information is written the same way, but a program which logs errors to a file can redirect everything written to the stderr file descriptor to a file. It's managed in another way by the operating system.

### Examples

When you use the `write(2)` function, you're actually using a file descriptor.

The prototype of the `write(2)` function is as follows :

```c
 size_t write(int fd, const void *buf, size_t count);
```

As you can see, the first parameter to this function is an `int` called fd, sounds familiar right ?

You can specify in which file to write with the first parameter, I'll make a quick example to show you how it could be used.


```c
// Including the unistd header for the write(2) function
#include <unistd.h>
// Including the fcntl header for the open(2) function
#include <fcntl.h>

// Prototypes of the functions declared under the main function
void ft_putchar_terminal(char c);
void ft_putchar_test_file(char c);

// main function
int main(void)
{
    // calling the ft_putchar_terminal function with character T
    ft_putchar_terminal("T");
    // calling the ft_putchar_test_file function with character F
    ft_putchar_test_file("F");
    return (0);
}

/* This function will simply write one character to the terminal on the 
 * standard output. As explained above, the fd for stdout is 1, so we put
 * 1 as a first parameter to the write(2) function.
 */
void ft_putchar_terminal(char c)
{
    write(1, &c, 1);
}

/* This function will open a file called "test.txt" with the open(2) function.
 * Once the file is opened, store the file descriptor in the fd variable.
 * I then check if there was an error opening the file.
 * If no error, I write the character F in the file test.txt
 * If there is an error, I write an error message to the standard error output.
 */
void ft_putchar_test_file(char c)
{
    int fd;
    
    /* Opening the test.txt file in Read/Write mode with open(2) function
     * then assigning the returned file descriptor value to the fd variable.
     */
    fd = open("test.txt", O_RDWR);
    /* Checking if the file was correctly opened.
     * The open function returns -1 if there is an error opening the file.
     */
    if (fd > 0)
        /* Writing the F character to the test.txt file by passing
         * its file descriptor as first parameter to the write(2) function.
         */
        write(fd, &c, 1);
    else
        /* If there was an error opening the file, the value of fd will be -1
         * thus it won't go inside the previous condition so I write an error
         * message to the stderr by passing the fd descriptor 2 as first parameter
         * to the write(2) function.
         */
        write(2, "test.txt not found.\n", 20);
}
```



### How it works

When you read bytes from a file descriptor, it remembers where in the file it was last time.

This means, if you read 20 bytes from a file, next time you'll read from the same file descriptor, it will start reading from byte 21. Take a look at the example below.



```c
// Including the unistd header for the write(2) & read(2) function
#include <unistd.h>
// Including the fcntl header for the open(2) function
#include <fcntl.h>

// Prototypes of the functions declared under the main function
void ft_putchar_terminal(char c);
void ft_putchar_test_file(char c);

// main function
int main(void)
{
    // calling the ft_putchar_terminal function with character T
    ft_putchar_terminal("T");
    // calling the ft_putchar_test_file function with character F
    ft_putchar_test_file("F");
    return (0);
}

/* This function will simply write one character to the terminal on the 
 * standard output. As explained above, the fd for stdout is 1, so we put
 * 1 as a first parameter to the write(2) function.
 */
void ft_putchar_terminal(char c)
{
    write(1, &c, 1);
}

/* This function will open a file called "test.txt" with the open(2) function.
 * Once the file is opened, store the file descriptor in the fd variable.
 * I then check if there was an error opening the file.
 * If no error, I write the character F in the file test.txt
 * If there is an error, I write an error message to the standard error output.
 */
void ft_putchar_test_file(char c)
{
    int fd;
    
    /* Opening the test.txt file in Read/Write mode with open(2) function
     * then assigning the returned file descriptor value to the fd variable.
     */
    fd = open("test.txt", O_RDWR);
    /* Checking if the file was correctly opened.
     * The open function returns -1 if there is an error opening the file.
     */
    if (fd > 0)
        /* Writing the F character to the test.txt file by passing
         * its file descriptor as first parameter to the write(2) function.
         */
        write(fd, &c, 1);
    else
        /* If there was an error opening the file, the value of fd will be -1
         * thus it won't go inside the previous condition so I write an error
         * message to the stderr by passing the fd descriptor 2 as first parameter
         * to the write(2) function.
         */
        write(2, "test.txt not found.\n", 20);
}
```


