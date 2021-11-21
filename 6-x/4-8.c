#include <pwd.h>
#include <stdio.h>

int main(void) 
{
    struct passwd *pw;

    pw = getpwnam("jeong-gyeongjae");
    printf("UID : %d\n", (int)pw->pw_uid);
    printf("Home Directory : %s\n", pw->pw_dir);

    return 0;
}
