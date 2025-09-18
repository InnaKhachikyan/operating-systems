# Differences between the disassembly of main.o, math_utils.o and executable square_prog


After objdump -d math_utils.o we see again file format executable and linkable. Here under the address 000...0000 is the function square, which, again, is the offset of the text segment. We see that both functions (main in main.o and square here) have the same address, however those are relocatable which means in the executable their addresses may (and most probably will) change. 

In the disassembly of the executable file we see that the main function is under address 000..001149 and the square function is under address 000...0001189, printf 000...0001050.
After the main we may see the calls to the other functions with their addresses (square and printf). The text segment starts with the start at address 000...00001060 where the actual main function is called from the libc. The addresses in the executable file are not relocatable anymore. When the program starts, it will have base address let's say 0xFFFF0000, then main will be at address base addr + main offset = 0xFFFF1149, similarly square will be at the address 0xFFFF1189.


# Differences of nm of the three files


nm main.o shows that the main in the text segment, printf in undefined (as it does not know yet where exactly the printf function is), the same for the square.


nm math_utils.o shows only the function square in the text segment.


In nm square_prog there are some segments unfamiliar to me, but what we know is that the main is in the text segment, as well as the square function, printf is still undefined as it will be loaded dynamically, libc start is also undefined, there are also some names in the data and bss segments, but I don't know what they mean. What seemed stranage to me that square and printf are both from outer sources, howver square is in the text segment, but printf is undefined. I assume when we linked the two files together with gcc main.o math_utils.o -o square_prog this way the actual implementation of the function was put in the text segment.


# readelf


readelf -h main.o math_utils.o and square_prog
I don't know many of the lines' meaning here. What I know is that the type of the object files is REL, which means their entry point address may be still changed, it is relocatable, in contrast with the executable file where the entry point address is given 0x1060. Here the type is DYN, pie file. Position independent files have fixed offset of the entry point address (like 0x1060), however, the virtual address (program base virtual address) is given on the run, and may change from one to another execution.
When we have the program base address +0x1060 will be the entry point.


