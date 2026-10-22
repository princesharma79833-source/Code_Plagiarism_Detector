const express = require("express");
const multer = require("multer");
const { execFile } = require("child_process");
const path = require("path");
const fs = require("fs");

const app = express();
const upload = multer({ dest: "uploads/" });
app.use(express.static("public"));

app.post("/compare", upload.array("codeFiles", 2), (req, res) => {
  if (req.files.length !== 2) {
    return res.status(400).json({ error: "Please upload exactly 2 files." });
  }

  const fileA = req.files[0].path;
  const fileB = req.files[1].path;
  const exePath = path.join(__dirname, "algorithm.exe");

  // UI par dikhane ke liye files ka text read kar rahe hain
  const codeA = fs.readFileSync(fileA, "utf8");
  const codeB = fs.readFileSync(fileB, "utf8");

  execFile(exePath, [fileA, fileB], (error, stdout, stderr) => {
    fs.unlinkSync(fileA);
    fs.unlinkSync(fileB);

    if (error) {
      console.error("Error executing C++ program:", error);
      return res.status(500).json({ error: "Algorithm execution failed." });
    }

    try {
      const result = JSON.parse(stdout);
      // Result mein codeA aur codeB add karke frontend ko bhej rahe hain
      result.codeA = codeA;
      result.codeB = codeB;
      res.json(result);
    } catch (parseError) {
      res.status(500).json({ error: "Failed to parse result from algorithm." });
    }
  });
});

app.listen(3000, () => {
  console.log("Server is LIVE! Open http://localhost:3000 in your browser");
});
