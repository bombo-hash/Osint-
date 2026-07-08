#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>

using namespace std;

// --- COLOR CONFIGURATION ---
const string RESET   = "\033[0m";
const string RED     = "\033[31m";
const string GREEN   = "\033[32m";
const string YELLOW  = "\033[33m";
const string BLUE    = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN    = "\033[36m";
const string BOLD    = "\033[1m";

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void banner() {
    // Crisp, highly-readable OSINT ASCII art
    cout << CYAN << BOLD << R"(
  ___  ____ ___ _   _ _____ 
 / _ \/ ___|_ _| \ | |_   _|
| | | \___ \| ||  \| | | |  
| |_| |___) | || |\  | | |  
 \___/|____/___|_| \_| |_|  
)" << RESET;
    cout << MAGENTA << BOLD << "        --> Made by: .blurrrd. <--\n" << RESET;
    cout << BLUE << "----------------------------------------\n" << RESET;
}

void pause() {
    cout << YELLOW << "\n[!] Press Enter to return to menu..." << RESET;
    cin.clear();
    cin.get();
}

// Global execution engine utilizing system-level curl requests
void fetchOSINT(const string& url) {
    cout << GREEN << "\n[*] Sending API request and pulling data...\n" << RESET;
    cout << BLUE << "==================================================\n" << RESET;
    
    // -s hides the curl progress meter so output looks clean
    string cmd = "curl -s \"" + url + "\"";
    system(cmd.c_str());
    
    cout << BLUE << "\n==================================================" << RESET;
    cout << "\n";
}

void personSearch() {
    string name;
    cout << YELLOW << "\n[*] Enter target full name (e.g., John Doe): " << RESET;
    getline(cin, name);

    if (name.empty()) {
        cout << RED << "[-] Error: Name cannot be blank.\n" << RESET;
        return;
    }

    // Format spaces to '+' symbols for URL encoding
    string query = name;
    for (char& c : query) {
        if (c == ' ') c = '+';
    }

    clearScreen();
    banner();
    
    cout << MAGENTA << "[*] Running Digital Footprint Scrape for: " << name << "\n\n" << RESET;
    
    string exactMatch = "https://www.google.com/search?q=%22" + query + "%22";
    string linkedinSearch = "https://www.google.com/search?q=site:linkedin.com/in+%22" + query + "%22";
    string socialSearch = "https://www.google.com/search?q=site:instagram.com+OR+site:twitter.com+OR+site:facebook.com+%22" + query + "%22";

    cout << CYAN << "--- GENERATED OSINT INTEL LINKS ---\n" << RESET;
    cout << GREEN << "[+] Exact Matches:   " << RESET << exactMatch << "\n";
    cout << GREEN << "[+] LinkedIn Spoke:  " << RESET << linkedinSearch << "\n";
    cout << GREEN << "[+] Social Networks: " << RESET << socialSearch << "\n\n";

    cout << YELLOW << "[*] Attempting to auto-launch primary query in your environment...\n" << RESET;
    
#ifdef _WIN32
    string cmd = "start \"\" \"" + exactMatch + "\"";
#elif __APPLE__
    string cmd = "open \"" + exactMatch + "\"";
#else
    // Checks standard linux display environments, defaults to termux-open if on Android
    string cmd = "termux-open \"" + exactMatch + "\" 2>/dev/null || xdg-open \"" + exactMatch + "\" 2>/dev/null";
#endif

    system(cmd.c_str());
}

int main() {
    int choice;
    string input;
    string target;

    while (true) {
        clearScreen();
        banner();

        cout << GREEN << "[1] " << RESET << "DNS Lookup\n";
        cout << GREEN << "[2] " << RESET << "WHOIS Scraping\n";
        cout << GREEN << "[3] " << RESET << "HTTP Response Headers\n";
        cout << GREEN << "[4] " << RESET << "IP Core Information\n";
        cout << GREEN << "[5] " << RESET << "SSL/TLS Certificate Analyzer\n";
        cout << GREEN << "[6] " << RESET << "Reverse DNS Mapping\n";
        cout << MAGENTA << "[7] " << RESET << "Name Search (Web OSINT Browser Launch)\n";
        cout << RED << "[0] " << RESET << "Exit Framework\n\n";

        cout << YELLOW << "Select Option: " << RESET;
        getline(cin, input);

        try {
            choice = stoi(input);
        } catch (...) {
            choice = -1; 
        }

        if (choice == 0) {
            cout << RED << "\n[!] Shutting down framework. Goodbye.\n" << RESET;
            return 0;
        }

        // Handle target collection for network modules
        if (choice >= 1 && choice <= 6) {
            cout << YELLOW << "Enter Target Domain or IP Address: " << RESET;
            getline(cin, target);
            if (target.empty()) {
                cout << RED << "[-] Error: Target vector cannot be blank.\n" << RESET;
                pause();
                continue;
            }
        }

        clearScreen();
        banner();
        
        if (choice >= 1 && choice <= 6) {
            cout << MAGENTA << "INVESTIGATING TARGET: " << target << "\n" << RESET;
        }

        switch (choice) {
            case 1:
                fetchOSINT("https://api.hackertarget.com/dnslookup/?q=" + target);
                break;
            case 2:
                fetchOSINT("https://api.hackertarget.com/whois/?q=" + target);
                break;
            case 3:
                fetchOSINT("https://api.hackertarget.com/httpheaders/?q=" + target);
                break;
            case 4:
                fetchOSINT("https://ipinfo.io/" + target);
                break;
            case 5:
                cout << GREEN << "\n[*] Pulling raw handshake encryption chains...\n" << RESET;
                cout << BLUE << "==================================================\n" << RESET;
                // Grabs the verbose certificate blocks out of an HTTP head request cross-platform
                #define IS_WIN _WIN32
                #ifdef IS_WIN
                    system(("curl -s -v -I https://" + target + " 2>&1 | findstr /I \"ssl cert subject connection\"").c_str());
                #else
                    system(("curl -s -v -I https://" + target + " 2>&1 | grep -i 'ssl\\|cert\\|subject\\|connection'").c_str());
                #endif
                cout << BLUE << "==================================================\n" << RESET;
                break;
            case 6:
                fetchOSINT("https://api.hackertarget.com/reversedns/?q=" + target);
                break;
            case 7:
                personSearch();
                break;
            default:
                cout << RED << "[-] Invalid selection. Pick a value between 0 and 7.\n" << RESET;
        }
        pause();
    }
    return 0;
}
