# Code Similarity & Plagiarism Detector

An algorithm-driven web application to detect copied and AI-generated source code using classical algorithm design techniques[cite: 3, 7].

## 🧠 Core Algorithms

- **Longest Common Subsequence (LCS):** Implemented using space-optimized Dynamic Programming to measure structural similarity and detect modified/reordered code[cite: 4, 8]. Time Complexity: $O(m \times n)$[cite: 4, 8].
- **Knuth-Morris-Pratt (KMP):** String matching algorithm utilizing an LPS (Longest Prefix Suffix) array to instantly detect exact copy-pasted code blocks without backtracking[cite: 4, 8]. Time Complexity: $O(m + n)$[cite: 4, 8].

## 🛠️ Technology Stack

- **Core Logic:** C/C++[cite: 5, 9]
- **Backend:** Node.js (Express & Multer)[cite: 5]
- **Frontend:** HTML, CSS, JavaScript[cite: 5]
- **UI Libraries:** diff2html (Side-by-side code comparison) & highlight.js (C/C++ Syntax highlighting)[cite: 5]

## 🚀 How to Run the Project

1. **Clone the repository:**
   `git clone <your-repo-link>`
2. **Compile the C++ Engine:**
   `g++ algorithm.cpp -o algorithm.exe`
3. **Install Node.js Dependencies:**
   `npm install express multer`
4. **Start the Server:**
   `node server.js`
5. Open `http://localhost:3000` in your web browser and upload two `.c` or `.cpp` files to test.
