#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include "glad.h"
#include <Windows.h>
#include <iostream>
#include "Application.h"
#include "WinMain.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

application* gApplication = 0;
GLuint gVertexArrayObject = 0;

#if _DEBUG
#pragma comment ( linker, "/subsystem:console" )
    int main(int argc, const char** argv)
    {
        return WinMain(GetModuleHandle(NULL), NULL, GetCommandLineA(), SW_SHOWDEFAULT);
    }
#else
#pragma comment ( linker, "/subsystem:windows" )
#endif
#pragma comment( lib, "opengl32.lib" )

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int*);

typedef const char* (WINAPI* PFNWGLGETEXTENSIONSSTRINGEXTPROC) (void);
typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC) (int);
typedef int (WINAPI* PFNWGLGETSWAPINTERVALEXTPROC) (void);


int WinMain(HINSTANCE HInstance, HINSTANCE HPrevInstance, PSTR SzCmdLine, int ICmdShow)
{
    gApplication = new application();

    WNDCLASSEX wndclass;
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = HInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wndclass.lpszMenuName = 0;
    wndclass.lpszClassName = L"Win32 Game Window";
    RegisterClassEx(&wndclass);

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int clientWidth = 800;
    int clientHeight = 600;

    RECT windowRect;
    SetRect
    (
        &windowRect,
        (screenWidth / 2) - (clientWidth / 2),
        (screenHeight / 2) - (clientHeight / 2),
        (screenWidth / 2) + (clientWidth / 2),
        (screenHeight / 2) + (clientHeight / 2)
    );

    DWORD style = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
    // WS_THICKFRAME to resize
    AdjustWindowRectEx(&windowRect, style, FALSE, 0);
    HWND hwnd = CreateWindowEx(0, wndclass.lpszClassName, L"Game Window", style, windowRect.left, windowRect.top, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, NULL, NULL, HInstance, SzCmdLine);
    HDC hdc = GetDC(hwnd);

    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 32;
    pfd.cStencilBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;
    int pixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pixelFormat, &pfd);

    HGLRC tempRC = wglCreateContext(hdc);
    wglMakeCurrent(hdc, tempRC);
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

    const int attribList[] = 
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_FLAGS_ARB, 0,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    0,
    };

    HGLRC hglrc = wglCreateContextAttribsARB(hdc, 0, attribList);
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(tempRC);
    wglMakeCurrent(hdc, hglrc);

    if (!gladLoadGL())
    {
        std::cout << "Couldnt initialize GLAD!!\n";
    }
    else
    {
        std::cout << "OpenGL Version " << GLVersion.major << "." << GLVersion.minor << "\n";
    }

    PFNWGLGETEXTENSIONSSTRINGEXTPROC _wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)wglGetProcAddress("wglGetExtensionsStringEXT");
    bool swapControlSupported = strstr(_wglGetExtensionsStringEXT(), "WGL_EXT_swap_control") != 0;

    int vsync = 0;
    if (swapControlSupported)
    {
        PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
        PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)wglGetProcAddress("wglGetSwapIntervalEXT");
        if (wglSwapIntervalEXT(1))
        {
            std::cout << "Enabled vSync\n";
            vsync = wglGetSwapIntervalEXT();
        }
        else
        {
            std::cout << "Couldnt enable vSync\n";
        }
    }
    else
    {
        std::cout << "WGL_EXT_swap_control not supported\n";
    }

    glGenVertexArrays(1, &gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    gApplication->initialize();

    //GAME LOOP STARTS
    DWORD lastTick = GetTickCount();
    MSG msg;
    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        // Calculate Tick Interval
        DWORD thisTick = GetTickCount();
        float dt = float(thisTick - lastTick) * 0.001f;
        lastTick = thisTick;
        if (gApplication != 0)
        {
            gApplication->update(dt);
        }
        //Rendering
        if (gApplication != 0)
        {
            RECT clientRect;
            GetClientRect(hwnd, &clientRect);
            clientWidth = clientRect.right - clientRect.left;
            clientHeight = clientRect.bottom - clientRect.top;

            glViewport(0, 0, clientWidth, clientHeight);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glPointSize(5.f);
            glBindVertexArray(gVertexArrayObject);

            glClearColor(0.5f, .6f, .7f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            float aspect = (float)clientWidth / (float)clientHeight;
            gApplication->render(aspect);
        }

        //Backbuffer
        if (gApplication != 0)
        {
            SwapBuffers(hdc);
            if (vsync != 0)
            {
                glFinish();
            }
        }
    }
    // END GAME LOOP

    if (gApplication != 0)
    {
        std::cout << "Expected application to be null on exit\n";
        delete gApplication;
    }

    return (int)msg.wParam;
}
LRESULT CALLBACK WndProc(HWND Hwnd, UINT IMsg, WPARAM WParam, LPARAM LParam)
{
    switch (IMsg)
    {
    case WM_CLOSE:
        if (gApplication != 0)
        {
            gApplication->shutdown();
            delete gApplication;
            gApplication = 0;
            DestroyWindow(Hwnd);
        }
        else
        {
            std::cout << "Already shut down!\n";
        }
        break;
    case WM_DESTROY:
        if (gVertexArrayObject != 0)
        {
            HDC hdc = GetDC(Hwnd);
            HGLRC hglrc = wglGetCurrentContext();

            glBindVertexArray(0);
            glDeleteVertexArrays(1, &gVertexArrayObject);
            gVertexArrayObject = 0;

            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(hglrc);
            ReleaseDC(Hwnd, hdc);

            PostQuitMessage(0);
        }
        else
        {
            std::cout << "Multiple destroy messages.\n";
        }
        break;
    case WM_PAINT:
    case WM_ERASEBKGND:
        return 0;
    }

    return DefWindowProc(Hwnd, IMsg, WParam, LParam);
}