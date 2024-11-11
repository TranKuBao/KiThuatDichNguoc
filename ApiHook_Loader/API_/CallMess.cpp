#include <windows.h>
#include <iostream>

using namespace std;

int CheckPass_Func(int k)
{
    
    int du1=k%20;
    int du2;
    switch (du1)
    {
        
    case 1:
    case 2:
    case 3:
        return 0;
    case 0:
        du2=k%12;
        switch (du2)
        {
            case 1:
            case 2:
                return 0;
            case 0:
                return 1;
            default:
                return 0;
        }
    default:
        return 0;
    }
}

void Call_messBOX_Accept_Func()
{
    MessageBoxA(NULL, "Login Successful !!!", "Application_CheckPass", MB_OK);
}

void Call_messBOX_NotAccept_Func()
{
    MessageBoxA(NULL, "Login Failed :(", "Application_CheckPass", MB_OK);
}

int main()
{
    int n;
    cout<<"Enter Pass: ";
    cin>>n;
    
    // Kiểm tra kết quả
    if (CheckPass_Func(n))
    {
        Call_messBOX_Accept_Func();
    }
    else
    {
        Call_messBOX_NotAccept_Func();
    }

    return 0;
}
