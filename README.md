BETTING SYSTEM 
A CPP in-terminal app made to bet sports events 
Technologies used 
- C++
- SQLite
- Makefile
IMPORTANT: 
- INCLUDE YOUR FILEPATHS (it is marked in code where to change it)
- To use SQLite3 use files sqlite3.c and sqlite3.h (they are included in repo)
- To compile files use gcc -c sqlite3.c -o sqlite3.o and then g++ *.cpp sqlite3.c -lws2_32 -o out.exe

Project structures:
  -/teams - directory with txt files including teams from various football leagues
  -app - whole app interface with all menus 
  -database- integration with SQLite to store users data, bet history and matches queue 
  -fixtures- all system of matchmaking, reading teams from files. 
  -betsystem - system of betting, managing wins and losses
  -auth- registering, logging into system and method of securing password (for Windows/UNIX)+ saving hashed password to database. 
  -userprofile-simple clas to make new user 
  -wallet- managing your digital wallet, withdrawals, deposits etc. 
  -main() - where everything stays.
  -usermanagmanent - system of managing users like withdrawals limits, bet limits etc (in work)
