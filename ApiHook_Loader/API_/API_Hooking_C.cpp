#include <windows.h>
#include <iostream>

typedef int (WINAPI* MessageBoxA_t)(HWND, LPCSTR, LPCSTR, UINT);
MessageBoxA_t OriginalMessageBoxA = nullptr; // Con trỏ tới hàm gốc

// Hàm tùy chỉnh của chúng ta
int WINAPI HookedMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) {
    // Thay đổi nội dung thông báo
    lpText = "Đây là thông báo đã được Hook!";
    lpCaption = "Thông báo Hooked!";
    
    // Gọi lại hàm gốc nếu cần, hoặc trả về giá trị tùy chỉnh
    return OriginalMessageBoxA(hWnd, lpText, lpCaption, uType);
}

// Hàm để thiết lập Inline Hook
void SetInlineHook() {
    // Lấy địa chỉ của MessageBoxA từ user32.dll
    HMODULE hUser32 = GetModuleHandle("user32.dll");
    OriginalMessageBoxA = (MessageBoxA_t)GetProcAddress(hUser32, "MessageBoxA");
    
    //std::cout<<OriginalMessageBoxA<<std::endl;
    if (OriginalMessageBoxA) {
        DWORD oldProtect;

        // Đổi quyền bộ nhớ thành PAGE_EXECUTE_READWRITE để cho phép ghi vào vùng nhớ của MessageBoxA
        VirtualProtect((LPVOID)OriginalMessageBoxA, 5, PAGE_EXECUTE_READWRITE, &oldProtect);

        // Tạo một lệnh JMP (jmp hook) để chuyển hướng từ MessageBoxA đến HookedMessageBoxA
        BYTE jump[5] = { 0xE9 }; // Lệnh JMP
        *(DWORD*)(jump + 1) = (DWORD)((LPBYTE)HookedMessageBoxA - (LPBYTE)OriginalMessageBoxA - 5);

        // Ghi đè lên đầu của hàm MessageBoxA bằng lệnh JMP
        memcpy((LPVOID)OriginalMessageBoxA, jump, 5);

        // Khôi phục lại quyền bộ nhớ
        VirtualProtect((LPVOID)OriginalMessageBoxA, 5, oldProtect, &oldProtect);
    }
}

int main() {
    // Thiết lập Hook cho MessageBoxA
    SetInlineHook();

    // Gọi MessageBoxA, nhưng vì đã được hook, nó sẽ chuyển đến HookedMessageBoxA
    MessageBoxA(NULL, "This is Main MESS", "Main_Title", MB_OK);

    return 0;
}
