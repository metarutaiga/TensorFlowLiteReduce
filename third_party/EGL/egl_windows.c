/*
** Copyright 2013-2020 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0
**
** This header is generated from the Khronos EGL XML API Registry.
** The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   http://www.khronos.org/registry/egl
*/

#pragma clang diagnostic ignored "-Wgnu-folding-constant"
#pragma clang diagnostic ignored "-Wmicrosoft-anon-tag"

#define _GDI32_
#include <stdlib.h>
#include <windows.h>
#include <EGL/egl.h>

#define CreateWindowIndirectExA(c) CreateWindowExA((c)->dwExStyle, \
    (c)->lpszClass, (c)->lpszName, (c)->style, (c)->x, (c)->y,     \
    (c)->cx, (c)->cy, (c)->hwndParent, (c)->hMenu, (c)->hInstance, \
    (c)->lpCreateParams)

static HMODULE opengl32_dll = NULL;

#define WGL_PROTOTYPE(type, prototype, parameter, ...) \
static type (WINAPI* prototype ## Entry) parameter; \
extern type WINAPI prototype parameter \
{ \
    return prototype ## Entry(__VA_ARGS__); \
} \
static void* WINAPI prototype ## Dummy parameter \
{ \
    return NULL; \
} \
static type WINAPI prototype ## Trunk parameter \
{ \
    if (opengl32_dll == NULL) \
        opengl32_dll = LoadLibraryA("OpenGL32.dll"); \
    prototype ## Entry = (type (WINAPI*) parameter)GetProcAddress(opengl32_dll, #prototype); \
    if (prototype ## Entry == NULL) \
        prototype ## Entry = (type (WINAPI*) parameter)prototype ## Dummy; \
    return prototype ## Entry(__VA_ARGS__); \
} \
static type (WINAPI* prototype ## Entry) parameter = prototype ## Trunk;

WGL_PROTOTYPE(HGLRC, wglCreateContext, (HDC hDc), hDc);
WGL_PROTOTYPE(BOOL, wglDeleteContext, (HGLRC oldContext), oldContext);
WGL_PROTOTYPE(HGLRC, wglGetCurrentContext, (void));
WGL_PROTOTYPE(HDC, wglGetCurrentDC, (void));
WGL_PROTOTYPE(PROC, wglGetProcAddress, (LPCSTR lpszProc), lpszProc);
WGL_PROTOTYPE(BOOL, wglMakeCurrent, (HDC hDc, HGLRC newContext), hDc, newContext);
WGL_PROTOTYPE(BOOL, wglShareLists, (HGLRC hrcSrvShare, HGLRC hrcSrvSource), hrcSrvShare, hrcSrvSource);

static void (WINAPI* glShaderSourceDesktop)(int shader, int count, char* const* string, const int* length);
static void WINAPI glShaderSourceMobile(int shader, int count, char* const* string, const int* length)
{
    char** replace_string = malloc(sizeof(char*) * count);
    for (int i = 0; i < count; ++i)
    {
        char* replace = strdup(string[i]);
        char* line;
        if ((line = strstr(replace, "#version 100")))
        {
            memcpy(line, "#version 120", sizeof("#version 120") - 1);
        }
        if ((line = strstr(replace, "#version 300 es")) ||
            (line = strstr(replace, "#version 310 es")) ||
            (line = strstr(replace, "#version 320 es")))
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
    free(replace_string);
}

EGLBoolean EGLAPIENTRY eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor)
{
    static const PIXELFORMATDESCRIPTOR desc =
    {
        .nSize = sizeof(PIXELFORMATDESCRIPTOR),
        .nVersion = 1,
        .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    };
    int format = ChoosePixelFormat((HDC)dpy, &desc);
    SetPixelFormat((HDC)dpy, format, &desc);
    HGLRC ctx = wglCreateContext((HDC)dpy);
    wglMakeCurrent((HDC)dpy, ctx);
    if (major)
    {
        (*major) = 1;
    }
    if (minor)
    {
        (*minor) = 5;
    }
    return EGL_TRUE;
}

EGLBoolean EGLAPIENTRY eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
    if (num_config)
    {
        (*num_config) = 1;
    }
    if (configs)
    {
        configs[0] = 0;
    }
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
        return "Windows";
    case EGL_VERSION:
        return "1.5 Windows META-EGL";
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
    if (proc == NULL && strcmp(procname, "glClearDepthf") == 0 && (procname = "glClearDepth"))
    {
        proc = wglGetProcAddress(procname);
    }
    if (proc == NULL && strcmp(procname, "glDepthRangef") == 0 && (procname = "glDepthRange"))
    {
        proc = wglGetProcAddress(procname);
    }
    if (proc == NULL)
    {
        proc = (PROC)GetProcAddress(opengl32_dll, procname);
    }
    if (proc && strcmp(procname, "glShaderSource") == 0)
    {
        glShaderSourceDesktop = (void (WINAPI*)(int, int, char* const*, const int*))proc;
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
    wglMakeCurrent(NULL, NULL);
    HWND window = WindowFromDC((HDC)dpy);
    ReleaseDC(window, (HDC)dpy);
    CloseWindow(window);
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
    if (display_id != EGL_DEFAULT_DISPLAY)
    {
        return (EGLDisplay)display_id;
    }
    WNDCLASSEXA wc =
    {
        .cbSize = sizeof(WNDCLASSEXA),
        .style = CS_OWNDC,
        .lpfnWndProc = DefWindowProcA,
        .hInstance = GetModuleHandleA(NULL),
        .lpszClassName = "EGL",
    };
    CREATESTRUCTA cs =
    {
        .hInstance = wc.hInstance,
        .cy = 1,
        .cx = 1,
        .style = WS_OVERLAPPEDWINDOW,
        .lpszName = wc.lpszClassName,
        .lpszClass = wc.lpszClassName,
    };
    RegisterClassExA(&wc);
    HWND window = CreateWindowIndirectExA(&cs);
    return GetDC(window);
}

EGLSurface EGLAPIENTRY eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list)
{
    return (EGLSurface)dpy;
}

EGLBoolean EGLAPIENTRY eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
    return EGL_TRUE;
}
