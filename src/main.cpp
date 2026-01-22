#include <iostream>
#include "userprofile.h"
#include "auth.h"
#include "app.h"
#include "database.h"
using namespace std;
int main()
{
    Database db("data/users.db");
    App app(db);
    app.Run();
}