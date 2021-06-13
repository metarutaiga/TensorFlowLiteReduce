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

#include <windows.h>
#include <EGL/egl.h>

#define EGL_PROTOTYPE(type, prototype, parameter, ...) \
extern type (EGLAPIENTRYP prototype ## Entry) parameter; \
extern "C" type EGLAPIENTRY prototype parameter \
{ \
    return prototype ## Entry(__VA_ARGS__); \
} \
static type EGLAPIENTRY prototype ## Trunk parameter \
{ \
    (void*&)prototype ## Entry = GetProcAddress(LoadLibraryA("libEGL.dll"), #prototype); \
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
type (EGLAPIENTRYP prototype ## Entry) parameter = prototype ## Trunk;

#if EGL_VERSION_1_0
EGL_PROTOTYPE(EGLBoolean, eglChooseConfig, (EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config), dpy, attrib_list, configs, config_size, num_config);
EGL_PROTOTYPE(EGLBoolean, eglCopyBuffers, (EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target), dpy, surface, target);
EGL_PROTOTYPE(EGLContext, eglCreateContext, (EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list), dpy, config, share_context, attrib_list);
EGL_PROTOTYPE(EGLSurface, eglCreatePbufferSurface, (EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list), dpy, config, attrib_list);
EGL_PROTOTYPE(EGLSurface, eglCreatePixmapSurface, (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint *attrib_list), dpy, config, pixmap, attrib_list);
EGL_PROTOTYPE(EGLSurface, eglCreateWindowSurface ,(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list), dpy, config, win, attrib_list);
EGL_PROTOTYPE(EGLBoolean, eglDestroyContext, (EGLDisplay dpy, EGLContext ctx), dpy, ctx);
EGL_PROTOTYPE(EGLBoolean, eglDestroySurface, (EGLDisplay dpy, EGLSurface surface), dpy, surface);
EGL_PROTOTYPE(EGLBoolean, eglGetConfigAttrib, (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value), dpy, config, attribute, value);
EGL_PROTOTYPE(EGLBoolean, eglGetConfigs, (EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config), dpy, configs, config_size, num_config);
EGL_PROTOTYPE(EGLDisplay, eglGetCurrentDisplay, (void));
EGL_PROTOTYPE(EGLSurface, eglGetCurrentSurface, (EGLint readdraw), readdraw);
EGL_PROTOTYPE(EGLDisplay, eglGetDisplay, (EGLNativeDisplayType display_id), display_id);
EGL_PROTOTYPE(EGLint, eglGetError, (void));
EGL_PROTOTYPE(__eglMustCastToProperFunctionPointerType, eglGetProcAddress, (const char *procname), procname);
EGL_PROTOTYPE(EGLBoolean, eglInitialize, (EGLDisplay dpy, EGLint *major, EGLint *minor), dpy, major, minor);
EGL_PROTOTYPE(EGLBoolean, eglMakeCurrent, (EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx), dpy, draw, read, ctx);
EGL_PROTOTYPE(EGLBoolean, eglQueryContext, (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value), dpy, ctx, attribute, value);
EGL_PROTOTYPE(const char *, eglQueryString, (EGLDisplay dpy, EGLint name), dpy, name);
EGL_PROTOTYPE(EGLBoolean, eglQuerySurface, (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value), dpy, surface, attribute, value);
EGL_PROTOTYPE(EGLBoolean, eglSwapBuffers, (EGLDisplay dpy, EGLSurface surface), dpy, surface);
EGL_PROTOTYPE(EGLBoolean, eglTerminate, (EGLDisplay dpy), dpy);
EGL_PROTOTYPE(EGLBoolean, eglWaitGL, (void));
EGL_PROTOTYPE(EGLBoolean, eglWaitNative, (EGLint engine), engine);
#endif /* EGL_VERSION_1_0 */

#if EGL_VERSION_1_1
EGL_PROTOTYPE(EGLBoolean, eglBindTexImage, (EGLDisplay dpy, EGLSurface surface, EGLint buffer), dpy, surface, buffer);
EGL_PROTOTYPE(EGLBoolean, eglReleaseTexImage, (EGLDisplay dpy, EGLSurface surface, EGLint buffer), dpy, surface, buffer);
EGL_PROTOTYPE(EGLBoolean, eglSurfaceAttrib, (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value), dpy, surface, attribute, value);
EGL_PROTOTYPE(EGLBoolean, eglSwapInterval, (EGLDisplay dpy, EGLint interval), dpy, interval);
#endif /* EGL_VERSION_1_1 */

#if EGL_VERSION_1_2
EGL_PROTOTYPE(EGLBoolean, eglBindAPI, (EGLenum api), api);
EGL_PROTOTYPE(EGLenum, eglQueryAPI, (void));
EGL_PROTOTYPE(EGLSurface, eglCreatePbufferFromClientBuffer, (EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list), dpy, buftype, buffer, config, attrib_list);
EGL_PROTOTYPE(EGLBoolean, eglReleaseThread, (void));
EGL_PROTOTYPE(EGLBoolean, eglWaitClient, (void));
#endif /* EGL_VERSION_1_2 */

#if EGL_VERSION_1_4
EGL_PROTOTYPE(EGLContext, eglGetCurrentContext, (void));
#endif /* EGL_VERSION_1_4 */

#if EGL_VERSION_1_5
EGL_PROTOTYPE(EGLSync, eglCreateSync, (EGLDisplay dpy, EGLenum type, const EGLAttrib *attrib_list), dpy, type, attrib_list);
EGL_PROTOTYPE(EGLBoolean, eglDestroySync, (EGLDisplay dpy, EGLSync sync), dpy, sync);
EGL_PROTOTYPE(EGLint, eglClientWaitSync, (EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout), dpy, sync, flags, timeout);
EGL_PROTOTYPE(EGLBoolean, eglGetSyncAttrib, (EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib *value), dpy, sync, attribute, value);
EGL_PROTOTYPE(EGLImage, eglCreateImage, (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLAttrib *attrib_list), dpy, ctx, target, buffer, attrib_list);
EGL_PROTOTYPE(EGLBoolean, eglDestroyImage, (EGLDisplay dpy, EGLImage image), dpy, image);
EGL_PROTOTYPE(EGLDisplay, eglGetPlatformDisplay, (EGLenum platform, void *native_display, const EGLAttrib *attrib_list), platform, native_display, attrib_list);
EGL_PROTOTYPE(EGLSurface, eglCreatePlatformWindowSurface, (EGLDisplay dpy, EGLConfig config, void *native_window, const EGLAttrib *attrib_list), dpy, config, native_window, attrib_list);
EGL_PROTOTYPE(EGLSurface, eglCreatePlatformPixmapSurface, (EGLDisplay dpy, EGLConfig config, void *native_pixmap, const EGLAttrib *attrib_list), dpy, config, native_pixmap, attrib_list);
EGL_PROTOTYPE(EGLBoolean, eglWaitSync, (EGLDisplay dpy, EGLSync sync, EGLint flags), dpy, sync, flags);
#endif /* EGL_VERSION_1_5 */
