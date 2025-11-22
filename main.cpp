#include <iostream>
#include "userprofile.h"
#include "auth.h"
#include "app.h"
#include "database.h"
using namespace std;
int main()
{

    Database db("C:\\Users\\rt04\\Documents\\BettingsystembyTG\\users.db");
    App app(db);
    app.Run();

   


}