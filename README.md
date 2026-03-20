*This project has been created as part
of the 42 curriculum by kghesqui.*

# GET_NEXT_LINE

## DESCRIPTION :

`get_next_line` is a C function that reads and returns one line at a time from a file descriptor. It uses static variables to preserve data between calls and works with any BUFFER_SIZE. The function handles various edge cases like empty files, lines without newlines, and EOF, making it a fundamental tool for file reading in C.

## INSTRUCTIONS : 

To compile this project you will hace to use `cc -Wall -Werror -Wextra -D BUFFER_SIZE=(any number you want)` because GNL works with any buffer size. If you want I have a folder with a main and some .txt files to do some tests. 

## RESOURCES : 

As I started this project a long time ago I don't have all the ressources but here is some that I remembered : The man, https://medium.com/@lannur-s/gnl-c3cff1ee552b, https://harm-smits.github.io/42docs/projects/get_next_line, https://dev.to/aerrfig/get-next-line-a-42-project-to-learn-how-to-deal-with-file-descriptors-and-io-of-system-3652, https://medium.com/@beatrizbazaglia/get-next-line-3872eb3189e6.

Regarding AI, I didn't used it that much in the project itself but I asked claude code to review my function to be sure and to make some tests. I do my own test when I code but when it's finished I ask claude code and run francinette. I also used claude to help me to resolve a memory leak problem cause I didn't understood why I had this problem.

## ALGORITHM OF Get_Next_Line:

The algorithm is based on **buffered reading with static accumulation**. A `static char *tmp` variable persists between calls and stores any leftover data that was read but not yet returned.

Each call to `get_next_line` follows this flow:

1. **Check leftovers first**: Before reading from the file, check if `tmp` already contains a `\n` from a previous read. If yes, extract and return that line immediately — no need to call `read` again.

2. **Read loop**: If no newline is in `tmp`, read `BUFFER_SIZE` bytes at a time from the file descriptor and append each chunk to `tmp` (`ft_check` handles this concatenation). Repeat until a `\n` is found in `tmp` or EOF is reached.

3. **Extract the line**: Once a `\n` is found, `ft_free` splits `tmp` — everything up to and including the `\n` is returned as the line, and `ft_extract` saves the rest back into `tmp` for the next call. On EOF with no newline, whatever remains in `tmp` is returned as the last line.

**Why this approach**: The static variable keeps state between calls without using global variables. The accumulator pattern works with any `BUFFER_SIZE` — small buffers just mean more `read` calls, large buffers mean fewer. The function only reads as much as needed (it stops as soon as a newline is found), and leftover data is never lost.