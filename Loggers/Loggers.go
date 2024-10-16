package main

import (
    "fmt"
    "log"
    "os"
    "path/filepath"
    "time"
)

// Struct to hold log data
type LogEntry struct {
    Path      string
    Timestamp time.Time
    Message   string
    ErrorType string
}

// Slice to hold all log entries
var logEntries []LogEntry

// Function to check for errors and warnings on each file and directory
func checkPath(path string, info os.FileInfo, err error) error {
    if err != nil {
        logEntries = append(logEntries, LogEntry{
            Path:      path,
            Timestamp: time.Now(),
            Message:   fmt.Sprintf("Error accessing path: %v", err),
            ErrorType: "Error",
        })
        return nil // continue walking the directory tree
    }

    // Check if the file is not readable or has restricted permissions
    if _, err := os.Open(path); err != nil {
        logEntries = append(logEntries, LogEntry{
            Path:      path,
            Timestamp: time.Now(),
            Message:   fmt.Sprintf("Permission issue or file unreadable: %v", err),
            ErrorType: "Warning",
        })
    }

    // Additional checks can be added here as needed (e.g., file format checks, size limits)

    return nil
}

// Function to log all detected errors and warnings
func logResults() {
    if len(logEntries) == 0 {
        fmt.Println("No errors or warnings found.")
        return
    }

    fmt.Println("Errors and Warnings:")
    for _, entry := range logEntries {
        fmt.Printf("[%s] %s: %s - %s\n", entry.Timestamp.Format(time.RFC3339), entry.ErrorType, entry.Path, entry.Message)
    }
}

func main() {
    root := "." // Set root directory to current directory

    fmt.Printf("Scanning directory: %s\n", root)

    // Walk through all directories and subdirectories
    err := filepath.Walk(root, checkPath)
    if err != nil {
        log.Fatalf("Error walking the path: %v\n", err)
    }

    // Output the results
    logResults()
}
