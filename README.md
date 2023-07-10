GET_NEXT_LINE
---------------

Get_next_line() reads from an open file descriptor and returns the text read 
until (and including) the first newline char it encounters. On next calls it 
returns the next line, or null if the file has ended or an error has occurred.

---------------
AUXILIARY FUNCTIONS:
---------------
- read_to_str
Takes as parameter the static var left_str (empty on first call) and the fd we
are reading from. Allocates memory with malloc to create the temporary variable
buf, in which is saved what read from the fd on each call; buf is then added 
at the end of left_str, and this is repeated until a newline char is found in
left_str. Memory for buf is freed. 
Returns the static var left_str, including the newline char, which will then 
be split into line (from 0 till the \n) and left_str (what remains after
the current \n and before the previous one).
---------------
-ft_get_line.
Takes as parameter the static var left_str, and returns the line until (and
including) the first \n it encounters.
Memory for the line is allocated with malloc. Left_line is not manipulated as
needed in the next function, to extract and maintain the chars left after \n
---------------
-ft_update_left_str
Takes as parameter the left_str (returned from read_to_str) and returns the 
string left after the \n, to keep it memory for the next call.
