#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Whitespace hata kar tokenization karna
string readFile(string path) {
    ifstream file(path);
    string text = "", line;
    while (getline(file, line)) {
        for(char c : line) if(!isspace(c)) text += c;
    }
    return text;
}

// Knuth-Morris-Pratt (KMP) Algorithm
int KMP(string text, string pattern) {
    if(pattern.empty()) return 0;
    int m = pattern.length(), n = text.length(), i = 0, j = 0, matches = 0;
    vector<int> lps(m, 0);
    for(int k = 1, len = 0; k < m;) {
        if(pattern[k] == pattern[len]) lps[k++] = ++len;
        else if(len != 0) len = lps[len - 1];
        else lps[k++] = 0;
    }
    while(i < n) {
        if(pattern[j] == text[i]) { i++; j++; }
        if(j == m) { matches += m; j = lps[j - 1]; }
        else if(i < n && pattern[j] != text[i]) {
            if(j != 0) j = lps[j - 1];
            else i++;
        }
    }
    return matches;
}

// Longest Common Subsequence (LCS) Algorithm
int LCS(string s1, string s2) {
    int m = s1.length(), n = s2.length();
    if(m==0 || n==0) return 0;
    vector<int> prev(n + 1, 0), curr(n + 1, 0);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) curr[j] = 1 + prev[j - 1];
            else curr[j] = max(prev[j], curr[j - 1]);
        }
        prev = curr;
    }
    return prev[n];
}

int main(int argc, char* argv[]) {
    if (argc < 3) { cout << "{\"error\": \"Files missing\"}"; return 1; }
    string fileA = readFile(argv[1]);
    string fileB = readFile(argv[2]);
    if(fileA.empty() || fileB.empty()) { cout << "{\"error\": \"Empty files\"}"; return 1; }

    int lcs_len = LCS(fileA, fileB);
    double lcs_ratio = (double)lcs_len / max(fileA.length(), fileB.length());

    int kmp_matches = 0, chunks = 0;
    for(size_t i = 0; i + 15 < fileA.length(); i += 15) {
        chunks++;
        if(KMP(fileB, fileA.substr(i, 15)) > 0) kmp_matches++;
    }
    double kmp_ratio = chunks == 0 ? 0 : (double)kmp_matches / chunks;

    double score = (lcs_ratio + kmp_ratio) * 50;
    string verdict = score > 70 ? "High Similarity" : (score > 40 ? "Moderate Similarity" : "Low Similarity");

    cout << "{\n";
    cout << "  \"lcs_ratio\": " << lcs_ratio << ",\n";
    cout << "  \"kmp_ratio\": " << kmp_ratio << ",\n";
    cout << "  \"overall_score\": " << score << ",\n";
    cout << "  \"verdict\": \"" << verdict << "\"\n";
    cout << "}\n";
    return 0;
}