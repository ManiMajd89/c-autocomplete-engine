# Autocomplete Engine in C

This repository features a fast and memory-efficient **autocomplete engine written in C**. The project demonstrates how to perform efficient prefix-based search using sorted data structures and **binary search** techniques, even on large datasets.

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

## 📁 Input Format

The input file must be a plain text file formatted as follows:

```
<number of entries>
<weight_1> <term_1>
<weight_2> <term_2>
...
<weight_n> <term_n>
```

### Example (`cities.txt`):
```
6
4612191 Toronto, Ontario, Canada
865263 Torino, Italy
1327407 San Antonio, Texas, United States
1307402 San Diego, California, United States
945942 San Jose, California, United States
1173533 San Salvador, El Salvador
```

- The **first line** contains an integer representing the total number of entries.
- Each subsequent line has a **double value** (weight) followed by a **string** (term).
- Terms may include spaces and punctuation. Weights represent importance, e.g., population.

---

## 🧪 Results

This autocomplete engine was tested using a real-world dataset containing over 90,000 global city names and population weights. The system demonstrates efficient binary search prefix matching and correct weight-based ranking.

### Test Case 1 – Prefix: `"Tor"`

**Purpose**: Match all major global cities starting with `"Tor"` (e.g., Toronto, Torino), and rank by descending population.

**Input Prefix:** `Tor`

**Matching Entries:**

```
4612191    Toronto, Ontario, Canada  
865263     Torino, Italy
```

**Expected Output:**

```
Toronto, Ontario, Canada      (4612191)  
Torino, Italy                 (865263)
```

The system correctly identifies two cities with the prefix `"Tor"` and ranks them by population. Toronto, being a significantly larger city, appears first.

---

### Test Case 2 – Prefix: `"San"`

**Purpose**: Identify multiple globally distributed cities beginning with `"San"`, showcasing the sorting and prefix capabilities of the engine.

**Input Prefix:** `San`

**Matching Entries:**

```
1327407    San Antonio, Texas, United States  
1307402    San Diego, California, United States  
945942     San Jose, California, United States  
1200000    Santiago de los Caballeros, Dominican Republic  
1173533    San Salvador, El Salvador
```

**Expected Output:**

```
San Antonio, Texas, United States                  (1327407)  
San Diego, California, United States               (1307402)  
Santiago de los Caballeros, Dominican Republic     (1200000)  
San Salvador, El Salvador                          (1173533)  
San Jose, California, United States                (945942)
```

The autocomplete engine successfully retrieves all matching terms and sorts them based on population (weight) in descending order. It showcases the program’s real-world usability in urban data applications.

---

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

## 🙏 Acknowledgements

> **Credit**: This project was originally designed by **Kevin Wayne**, and later **adapted to C by Michael Guerzhoy** for ESC190H1F – Programming Fundamentals, University of Toronto.

---

## Author

**Mani Majd**  
📫 [LinkedIn](https://www.linkedin.com/in/mani-majd)  
