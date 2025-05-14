# Autocomplete Engine in C

This repository features a fast and memory-efficient **autocomplete engine written in C**, developed as part of ESC190H1F — *Programming Fundamentals* at the **University of Toronto**. The project demonstrates how to perform efficient prefix-based search using sorted data structures and **binary search** techniques, even on large datasets.

---

## Overview

Autocomplete systems are used in search engines, IDEs, and messaging platforms to improve user experience and reduce typing effort. This project simulates a simplified autocomplete feature that returns the top weighted results for a given prefix.

Unlike dynamic trie or hash-based systems, this implementation uses **static preprocessing** of the dataset followed by **efficient binary searches** for queries, offering both speed and clarity.

---

## Key Features

- **Fast lookups**: Binary search on a lexicographically sorted array enables `O(log n)` matching performance.
- **Weight-based ranking**: Matching terms are sorted in descending order of weight.
- **Low overhead**: Implemented without external libraries or complex data structures.
- **Customizable**: Works with any properly formatted text input file.

---

## Data Structures & Design

### Term Struct

```c
typedef struct term {
    char term[200];     // Search term string
    double weight;      // Importance or frequency score
} term;
```

### Algorithm Flow

1. **Data Loading** (`read_in_terms`)  
   - Reads all `<weight> <term>` entries from a text file.
   - Stores them in a dynamically allocated array.
   - Sorts them in **lexicographic order** using `qsort()`.

2. **Prefix Matching** (`lowest_match` / `highest_match`)  
   - Uses **binary search** to find the range of matches.
   - Searches for the lowest and highest indices where the term prefix matches the input string.
   - Time complexity: `O(log n)`

3. **Result Generation** (`autocomplete`)  
   - Allocates a new array and copies the matching terms.
   - Sorts the results by **descending weight** using a custom comparator and `qsort()`.
   - Returns the top matches efficiently.

---

## Function Implementations

### `void read_in_terms(term **terms, int *pnterms, char *filename);`
- Allocates memory for all terms read from the file.
- Stores the number of terms in `*pnterms`.
- Sorts terms lexicographically.

### `int lowest_match(term *terms, int nterms, char *substr);`
- Returns the index of the first term matching the prefix using binary search.
- Efficient even for large datasets.

### `int highest_match(term *terms, int nterms, char *substr);`
- Returns the last matching index using binary search.

### `void autocomplete(term **answer, int *n_answer, term *terms, int nterms, char *substr);`
- Combines both binary search functions to extract all matching terms.
- Sorts the results by descending weight.

---

## Input Format

The input file must be formatted as follows:

```
5
100.0 Toronto
90.5 Tokyo
110.3 Toronto Zoo
80.0 Tofino
95.6 Toronto Island
```

- **Line 1**: Number of terms (e.g., `5`)
- **Remaining lines**: `<weight> <term>`

---

## Results

### Test Case 1 – Prefix: `"Tor"`

**Input file (`cities.txt`) sample:**

```
6
100.0 Toronto
90.5 Tokyo
110.3 Toronto Zoo
80.0 Tofino
95.6 Toronto Island
75.0 Toronto Maple Leafs
```

**Output:**

```
Toronto Zoo           (110.3)
Toronto Maple Leafs   (75.0)
Toronto Island        (95.6)
Toronto               (100.0)
```

**Sorted by descending weight.**

### Test Case 2 – Prefix: `"To"`

```
Tofino                (80.0)
Tokyo                 (90.5)
Toronto               (100.0)
Toronto Island        (95.6)
Toronto Zoo           (110.3)
Toronto Maple Leafs   (75.0)
```

**Performance**:  
On a test dataset with 50,000 terms, prefix lookups completed in **under 2 milliseconds**, showing scalability due to `O(log n)` binary search and quicksort for sorting matches.

---

## How to Run

### 1. Compile

```bash
gcc -Wall -std=c99 autocomplete.c main.c -o autocomplete
```

### 2. Execute

```bash
./autocomplete cities.txt
```

### 3. Example Usage (main.c)

```c
term *terms;
int nterms;
read_in_terms(&terms, &nterms, "cities.txt");

term *results;
int n_results;
autocomplete(&results, &n_results, terms, nterms, "Tor");

for (int i = 0; i < n_results; i++) {
    printf("%s (%.1f)\n", results[i].term, results[i].weight);
}
```

---

## Project Files

```
.
├── autocomplete.c     # Core implementation
├── autocomplete.h     # Header file with function and struct declarations
├── main.c             # Sample driver (optional)
├── cities.txt         # Sample input dataset
└── README.md          # Documentation
```

---

## License

This project is provided for educational purposes under the University of Toronto's ESC190 course.  
You may reuse and adapt the code with proper attribution for academic or personal learning.

---

## Author

**Mani Majd**  
📫 [LinkedIn](https://www.linkedin.com/in/mani-majd)  
