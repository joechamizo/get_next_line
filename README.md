# Get_Next_Line

## 👤 Project Overview and AI Collaboration

To keep the project understandable, maintainable, and aligned with the 42 evaluation process, the development was structured around dynamic reading requirements, a rigorous memory-safe architecture, and an adaptive code review workflow.

- **Memory architecture and structure:** Designed and implemented a custom memory handling mechanism using singly linked lists to safeguard data between execution calls without relying on massive buffer reallocations.
- **Dynamic parsing:** Implemented a runtime delimiter parameter, allowing the function to adapt to any delimiter character without recompiling.
- **Bonus architecture:** Developed a multi-fd tracking system using static arrays, allowing independent reading streams from multiple file descriptors simultaneously without data cross-contamination.

---

## 📝 Description

**Get_Next_Line** is an algorithmic and memory management project written in C. The goal is to write a function that returns a line read from a file descriptor, producing stable and leaks-free execution regardless of the buffer size.

The project focuses on:
- static variables manipulation to preserve tracking state;
- pointer-safe dynamic node movement within linked lists;
- input file stream parsing and error handling;
- heap memory ownership and cleanup;
- structural code optimization under the 42 Norminette constraints.

The program reads from a file descriptor or standard input and returns the next line found, ending with the specified cutting character.

---

## 📐 Technical and Algorithmic Decisions

The project is built around a modular linked list architecture. The input stream is processed in chunks, saved into temporary nodes, and then flattened into a single clean allocation once the delimiter is reached.

### Linked Lists Justification

For this implementation, an algorithm based on Singly Linked Lists was chosen. The main reasons are:
- **Dynamic Flexibility:** The list allows storing read fragments of any size without the need to reallocate and copy the entire string in each iteration, optimizing heap usage.
- **Remainder Management:** The leftover data from a read (what remains after the selected delimiter) is naturally managed when clearing the list, keeping only the necessary node for the next call.
- **Modularity and the Norm:** The use of lists makes it easier to divide the code into short logical functions (under 25 lines), tasked with atomic duties such as node creation and final line extraction.
- **Adaptability:** The list logic facilitates searching for any delimiter character without compromising the structure of the stored data.

---

## 🧠 Core Engineering Principles and Defense Guide

### 1. Static Variables Theory

A static variable in C is stored in the Data Segment (or BSS segment if uninitialized) of the program's memory, rather than on the stack or the heap. This allows it to preserve its value between consecutive function calls and persist throughout the entire execution lifetime of the program.

In this implementation, the static pointer acts as the persistent entry point to our linked list. When get_next_line is called, it checks this static reference to see if there is any leftover data from the previous read stream. 

For the bonus part, instead of a single pointer, we declare an array of static pointers indexed by the file descriptor: `static t_list *stack[OPEN_MAX]`. This ensures that each file descriptor retains its own independent linked list state, allowing interleaved reads from multiple sources without data cross-contamination.

### 2. Buffer Remainder Management

When the read loop detects the selected delimiter character, the list contains the current line plus some trailing remainder data from the last buffer read. Memory safety and efficiency are handled in three synchronized steps:

1. **Line Extraction:** The function calculates the exact length from the start of the list up to the delimiter character, allocates the precise amount of memory on the heap, and flattens the node content into a single clean, null-terminated string to return.
2. **Remainder Isolation:** A dedicated utility function searches for the delimiter inside the last processed node, isolates the leftover data that follows it, and creates a brand-new node specifically to house this remainder.
3. **Heap Cleanup:** All preceding nodes that formed the extracted line are completely freed via `free()`. The static variable is then updated to point exclusively to the new remainder node. This leaves the heap perfectly optimized and ready for the next get_next_line call.

### 3. Edge Cases Handling

To meet the rigorous standards of 42, the codebase explicitly addresses several severe runtime situations:

- **Ultra Large Buffers (e.g., BUFFER_SIZE=10M):** Prevents stack overflow by allocating the read buffer directly on the heap (`malloc`) rather than defining local stack arrays (`char buf[BUFFER_SIZE]`), bypassing kernel limits.
- **Files Lacking a Delimiter / EOF:** If the file ends abruptly without encountering the selected delimiter, the remaining buffer structure is cleanly extracted as the final string, and the static track pointer is set to `NULL` to signify a successful end of stream.
- **Interleaved Errors mid-stream:** If a `read()` operation returns an error (`-1`) midway through execution, the function immediately releases all previously accumulated nodes in the list to fully eliminate memory leaks before returning `NULL`.
- **Empty strings:** The implementation handles empty inputs safely, but it still relies on C strings, so embedded `'\0'` bytes are not supported.

---

## 📊 Performance Targets

According to the project requirements, the program must handle different buffer constraints without crashing or leaking memory:

### Small and Standard Buffers (BUFFER_SIZE=1 to 42)
- Minimum requirement: successful line retrieval without memory leaks.
- Good performance: minimal node allocation overhead.
- Excellent performance: instantaneous reading with precise remainder storage.

### Large Buffers (BUFFER_SIZE=10M)
- Minimum requirement: stack-safe execution without memory allocation failures.
- Good performance: stable memory usage under heavy continuous loads.
- Excellent performance: zero heap fragmentation during large buffer swaps.

---

## 🛠️ Usage

### Requirements
- `cc`, `clang`, or `gcc`
- Unix-based system such as Linux or macOS

### Compilation

Standard compilation (default delimiter is newline):
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

Custom use (example: cut by commas for CSV files processing):
```bash
cc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

Use the default wrapper:
```c
line = get_next_line(fd);
```

Use a custom delimiter at runtime:
```c
line = get_next_line_c(fd, ',');
```

### Running the Binary

Once compiled, you can execute the resulting binary file:
```bash
./a.out
```

---

## ❌ Error Handling

The program handles invalid file descriptors and unexpected runtime events gracefully:
- returns `NULL` on invalid file descriptors (`fd < 0`);
- returns `NULL` on read system call errors (`read() == -1`);
- safely frees all internal allocated list nodes if an error occurs mid-stream;
- behaves stably under non-conventional cutting characters such as spaces;
- expects standard C strings, so embedded null bytes are not supported.

---

## 📚 Resources and Use of AI

### References
- 42 Get_Next_Line subject
- 42 Norminette guidelines
- Documentation for the `read(2)` system call
- General references on static variables scope and linked lists in C

### AI Usage Statement

AI assistance was used as a support tool during the project workflow, mainly for:
- **Refactoring:** Optimizing functions to comply with the Norminette after implementing the runtime delimiter logic.
- **Algorithmic Design:** Adapting the search algorithm to support dynamic delimiter characters passed at runtime.
- **Documentation:** Creating and formatting this README.md file structure.
- **Debugging:** Analyzing edge cases when using unconventional cutting characters (such as spaces or null characters).

All generated suggestions were manually reviewed, adapted, tested, and validated with:
- `norminette`;
- `valgrind` (zero memory leaks verified);
- extreme testing setups using variable buffer sizes from 1 to 10M.

---

## ⚖️ Academic Disclaimer

This repository has been created for purely academic purposes as part of my personal learning journey through the **42 network** curriculum.

* **Use at your own risk:** I do not take any responsibility for how the code in this repository is used, nor for any consequences arising from its duplication, modification, or reuse in your own project submissions.
* **42 Plagiarism Policy:** 42 students are heavily reminded that plagiarism or direct code copying without fully understanding its inner workings violates the school rules and can be severely penalized by both automated testing systems (*Moulinette*) and human peer-evaluators.
* **Purpose:** This codebase is shared with the sole purpose of serving as an engineering reference, technical guide, or inspiration for building advanced custom Makefiles and automated interactive test suites.
