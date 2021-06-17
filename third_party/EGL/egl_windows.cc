/*
** Copyright 2013-2020 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0
**
** This header is generated from the Khronos EGL XML API Registry.
** The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   http://www.khronos.org/registry/egl
**
** Khronos $Git commit SHA1: 59522adade $ on $Git commit date: 2021-02-02 11:09:11 -0700 $
*/

#define _GDI32_
#include <stdlib.h>
#include <windows.h>
#include <EGL/egl.h>

#define WGL_PROTOTYPE(type, prototype, parameter, ...) \
extern type (WINAPI* prototype ## Entry) parameter; \
extern "C" type WINAPI prototype parameter \
{ \
    return prototype ## Entry(__VA_ARGS__); \
} \
static type WINAPI prototype ## Trunk parameter \
{ \
    (void*&)prototype ## Entry = GetProcAddress(LoadLibraryA("OpenGL32.dll"), #prototype); \
    if (prototype ## Entry == nullptr) \
    { \
        prototype ## Entry = [] parameter -> type \
        { \
            typedef type returnType; \
            return returnType(); \
        }; \
    } \
    return prototype ## Entry(__VA_ARGS__); \
} \
type (WINAPI* prototype ## Entry) parameter = prototype ## Trunk;

WGL_PROTOTYPE(HGLRC, wglCreateContext, (HDC dc), dc);
WGL_PROTOTYPE(BOOL, wglDeleteContext, (HGLRC glrc), glrc);
WGL_PROTOTYPE(HGLRC, wglGetCurrentContext, (VOID));
WGL_PROTOTYPE(HDC, wglGetCurrentDC, (VOID));
WGL_PROTOTYPE(PROC, wglGetProcAddress, (LPCSTR name), name);
WGL_PROTOTYPE(BOOL, wglMakeCurrent, (HDC dc, HGLRC glrc), dc, glrc);
WGL_PROTOTYPE(BOOL, wglShareLists, (HGLRC share, HGLRC glrc), share, glrc);

void (WINAPI* glShaderSourceDesktop)(int shader, int count, const char* const* string, const int* length);
void WINAPI glShaderSourceMobile(int shader, int count, const char* const* string, const int* length)
{
    char** replace_string = new char* [count];
    for (int i = 0; i < count; ++i)
    {
        char* replace = strdup(string[i]);
        char* line = strstr(replace, "#version 310 es");
        if (line)
        {
            memcpy(line, "#version 430   ", sizeof("#version 430   ") - 1);
        }
        replace_string[i] = line;
    }
    glShaderSourceDesktop(shader, count, replace_string, length);
    for (int i = 0; i < count; ++i)
    {
        free(replace_string[i]);
    }
    delete[] replace_string;
}

EGLBoolean EGLAPIENTRY eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor)
{
    static const PIXELFORMATDESCRIPTOR desc =
    {
        .nSize = sizeof(PIXELFORMATDESCRIPTOR),
        .nVersion = 1,
        .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    };
    SetPixelFormat((HDC)dpy, ChoosePixelFormat((HDC)dpy, &desc), &desc);
    HGLRC ctx = wglCreateContext((HDC)dpy);
    wglMakeCurrent((HDC)dpy, ctx);
    if (major)
        (*major) = 1;
    if (minor)
        (*minor) = 5;
    return EGL_TRUE;
}

EGLBoolean EGLAPIENTRY eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
    (*configs) = 0;
    return EGL_TRUE;
}

EGLBoolean EGLAPIENTRY eglBindAPI(EGLenum api)
{
    return EGL_TRUE;
}

const char * EGLAPIENTRY eglQueryString(EGLDisplay dpy, EGLint name)
{
    switch (name)
    {
    case EGL_CLIENT_APIS:
        return "OpenGL_ES";
    case EGL_VENDOR:
        return "TensorFlow";
    case EGL_VERSION:
        return "1.5";
    default:
        return "";
    }
}

EGLint EGLAPIENTRY eglGetError(void)
{
    return EGL_SUCCESS;
}

__eglMustCastToProperFunctionPointerType EGLAPIENTRY eglGetProcAddress(const char *procname)
{
    PROC proc = wglGetProcAddress(procname);
    if (proc == nullptr)
    {
        proc = (PROC)GetProcAddress(GetModuleHandleA("OpenGL32.dll"), procname);
    }
#if 0
    if (proc == nullptr)
    {
        OutputDebugStringA(procname);
        OutputDebugStringA("\n");
    }
#endif
    if (proc && strcmp(procname, "glShaderSource") == 0)
    {
        (PROC&)glShaderSourceDesktop = proc;
        proc = (PROC)glShaderSourceMobile;
    }
    return (__eglMustCastToProperFunctionPointerType)proc;
}

EGLContext EGLAPIENTRY eglGetCurrentContext(void)
{
    return (EGLContext)wglGetCurrentContext();
}

EGLContext EGLAPIENTRY eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list)
{
    return (EGLContext)wglGetCurrentContext();
}

EGLBoolean EGLAPIENTRY eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
    return wglDeleteContext((HGLRC)ctx) ? EGL_TRUE : EGL_FALSE;
}

EGLBoolean EGLAPIENTRY eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
    return wglMakeCurrent((HDC)dpy, (HGLRC)ctx);
}

EGLDisplay EGLAPIENTRY eglGetCurrentDisplay(void)
{
    return (EGLDisplay)wglGetCurrentDC();
}

EGLDisplay EGLAPIENTRY eglGetDisplay(EGLNativeDisplayType display_id)
{
    if (display_id == EGL_DEFAULT_DISPLAY)
    {
        static HWND window = nullptr;
        static HDC dc = nullptr;
        if (window == nullptr)
        {
            WNDCLASSEXA wc = { sizeof(WNDCLASSEXA), CS_OWNDC, ::DefWindowProcA, 0, 0, ::GetModuleHandleA(nullptr), nullptr, nullptr, nullptr, nullptr, "OpenGL", nullptr };
            ::RegisterClassExA(&wc);
            window = ::CreateWindowA(wc.lpszClassName, "OpenGL", WS_OVERLAPPEDWINDOW, 0, 0, 1, 1, nullptr, nullptr, wc.hInstance, nullptr);
            dc = GetDC(window);
        }
        return dc;
    }
    return (EGLDisplay)display_id;
}

EGLSurface EGLAPIENTRY eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list)
{
    return (EGLSurface)dpy;
}

EGLBoolean EGLAPIENTRY eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
    return EGL_TRUE;
}
