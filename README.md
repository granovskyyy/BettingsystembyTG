# BETTING SYSTEM

A terminal-based sports betting application written in **C++** with **SQLite** support.
Designed to run locally on Windows or UNIX systems.

---

## TECHNOLOGIES USED

* **C++**
* **SQLite** (included: `sqlite3.c` & `sqlite3.h`)
* **Makefile** (optional)

---

## PROJECT CLASSES 

```
/teams/            # .txt files with team lists from various football leagues
/app/              # application interface — menus and UI logic
/database/         # SQLite integration: users, bet history, match queue
/fixtures/         # match creation system, reading team lists
/betsystem/        # betting logic: calculating wins/losses
/auth/             # registration & login, password hashing (Windows/UNIX)
/userprofile/      # simple user class
/wallet/           # wallet operations: deposit, withdrawal, balance
/usermanagement/   # user limits, withdrawal limits, bet limits, temp locks
main.cpp           # program entry point
sqlite3.c          #sqlite files 
sqlite3.h
Makefile
README.md
```
## PROJECT STRUCTURE 
```
/src - .cpp files
/include - .h files
/data - database and teams .txtfiles 


> **IMPORTANT:**
> If compilation fails on Windows due to networking libs, keep `-lws2_32` enabled.
> On UNIX systems, remove `-lws2_32` entirely.

---

## COMPILATION 

### 1) **Compile SQLite first**

```bash
gcc -c sqlite/sqlite3.c -o sqlite3.o
```

### 2) **Compile and link the project**

#### Windows:

```bash
g++ src/*.cpp sqlite3.o -Iinclude -lws2_32 -o out.exe
```

#### UNIX / Linux / macOS:

```bash
g++ src/*.cpp sqlite3.o -Iinclude -o out
```



### 3) MAKEFILE (in build)

If a Makefile is provided:

```bash
make
```

---

## ▶️ Running the Application

```bash
# Windows:
./out.exe

# UNIX / Linux / macOS:
./out
```

The program runs entirely inside the terminal.
Use the on-screen menu to navigate through the system.


## Database (SQLite)

The application stores:

* user accounts (with hashed passwords),
* bet history,
* scheduled matches.

**No external SQLite installation is required** — everything is bundled with the project (`sqlite3.c`, `sqlite3.h`).

Make sure the directory where the `.db` file is stored has **read/write permissions**.


## SECURITY

Located in `/auth/`:

* registration and login system
* platform-specific hashing for Windows and UNIX
* hashed password storage in SQLite




