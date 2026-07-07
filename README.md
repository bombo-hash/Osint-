# OSINT

A lightweight C++ terminal-based OSINT utility for performing quick lookups on domains, IP addresses, and names.

## Features

- DNS Lookup
- WHOIS Lookup
- HTTP Response Headers
- IP Information
- SSL/TLS Certificate Information
- Reverse DNS Lookup
- Name Search (opens search engine queries)

## Requirements

- C++ compiler (Clang or GCC)
- curl
- Internet connection

### Linux / Termux

Install curl if it isn't already installed.

## Clone


## Build

Compile with:

```bash
clang++ main.cpp -o osint
```

## Run

```bash
./osint
```

On Windows:

```cmd
osint.exe
```

## APIs Used

- https://api.hackertarget.com/
- https://ipinfo.io/

## Disclaimer

This tool is intended for educational purposes, security research, and investigating systems or information you are authorized to examine. Users are responsible for complying with applicable laws, terms of service.
