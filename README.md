
````markdown
# 🔧 Recovery – File Recovery Utility in C

A robust command-line tool written in **C** to recover JPEG files from disk images, developed as part of Harvard’s **CS50** coursework.

---

## 🎯 Project Overview

**Recovery** scans a raw forensic image (e.g., `card.raw`) and retrieves contiguous JPEG files using a standard block-by-block approach (each block: 512 bytes). The tool detects JPEG signatures, handles file boundaries, and outputs recovered images in sequential order (`000.jpg`, `001.jpg`, …).

---

## 🗂️ Repository Contents

- **`recover.c`** – Main program: reads input raw file, locates JPEG headers, writes output images.
- **`helpers.c`** (optional) – Additional routines (if any).
- **`helpers.h`** – Structs and prototypes.
- **`Makefile`** – To compile the project (`make recover`).
- **Sample data** – (e.g., `card.raw`, recovered images directory).

---

## ⚙️ Core Features

1. **Block-based processing**  
   Reads and writes data in 512-byte chunks—the standard block size for FAT file system images.

2. **JPEG Header Detection**  
   Identifies start of JPEGs by checking:
   ```c
   buffer[0] == 0xff &&
   buffer[1] == 0xd8 &&
   buffer[2] == 0xff &&
   (buffer[3] & 0xf0) == 0xe0
````

3. **File Management**

   * On detecting a new JPEG header:

     * Close the current file (if open)
     * Open a new one with filename formatted as `%03i.jpg`
   * Continue writing in 512-byte increments until the next JPEG header.

4. **Sequential Recovery**
   Continues until the input file ends, handling cases where:

   * JPEGs are back-to-back
   * Partial/corrupted images (imperfect boundaries)

5. **Error Handling & Bounds Checking**
   Gracefully manages invalid inputs or I/O errors and reports them with appropriate messages.

---

## 🛠️ Build & Usage

```bash
make recover          # Compiles recover.c to executable 'recover'
./recover card.raw    # Recovers JPEGs from 'card.raw' into the current directory
```

You can specify write directory or change filename formatting inside the code if needed.

---

## 🧠 Technical Highlights

* **Binary File I/O** – `fread` and `fwrite` for raw data handling.
* **Pointer and Buffer Management** – Careful to avoid memory errors.
* **Bitwise Operations** – Uses masks to identify JPEG headers reliably.
* **String Formatting** – `sprintf()` generates sequential filenames.
* **Modular Design** – Main logic separated into helper functions for clarity.

---

## 📚 Lessons Learned

* Understanding low-level **disk image structures** and forensic recovery concepts.
* Translating **file format specifications** into byte-level logic.
* Efficient handling of file streams in a memory-safe manner.
* Practical use of **CS50’s robust testing** framework to validate edge cases.

---

## 📦 Sample Output

Recovered JPEG files appear as:

```
000.jpg
001.jpg
...
```

Use any image viewer to verify that files have been recovered correctly.

---

## 👨‍💻 Author

**Kapish Bhati**
Completed as part of **CS50 – Harvard University** Introduction to Computer Science

