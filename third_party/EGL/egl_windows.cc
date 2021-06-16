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

EGLBoolean eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor)
{
    if (major)
        (*major) = 1;
    if (minor)
        (*major) = 5;
    return EGL_TRUE;
}

EGLBoolean eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
    return EGL_TRUE;
}

EGLBoolean eglBindAPI(EGLenum api)
{
    return EGL_TRUE;
}

const char *eglQueryString(EGLDisplay dpy, EGLint name)
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

EGLint eglGetError(void)
{
    return 0;
}

__eglMustCastToProperFunctionPointerType eglGetProcAddress(const char *procname)
{
    return (__eglMustCastToProperFunctionPointerType)wglGetProcAddress(procname);
}

EGLContext eglGetCurrentContext(void)
{
    return wglGetCurrentContext();
}

EGLContext eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list)
{
    HGLRC ctx = wglCreateContext((HDC)dpy);
    if (ctx && share_context)
        wglShareLists((HGLRC)share_context, ctx);
    return ctx;
}

EGLBoolean eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
    return wglDeleteContext((HGLRC)ctx) ? EGL_TRUE : EGL_FALSE;
}

EGLBoolean eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
    return wglMakeCurrent((HDC)dpy, (HGLRC)ctx);
}

EGLDisplay eglGetCurrentDisplay(void)
{
    return (EGLDisplay)wglGetCurrentDC();
}

EGLDisplay eglGetDisplay(EGLNativeDisplayType display_id)
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

EGLSurface eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list)
{
    static const PIXELFORMATDESCRIPTOR desc =
    {
        .nSize = sizeof(PIXELFORMATDESCRIPTOR),
        .nVersion = 1,
        .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    };
    SetPixelFormat((HDC)dpy, ChoosePixelFormat((HDC)dpy, &desc), &desc);
    return (EGLSurface)dpy;
}

EGLBoolean eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
    return EGL_TRUE;
}
