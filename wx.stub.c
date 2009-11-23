#include "runtime.h"
#include "type.h"
#include "cgocall.h"
#include "wx.h"

#define PRAGMA #pragma
#define IMPORT_FUNC(func) void(*func)(void*); PRAGMA dynld func func WRAP_SO

#pragma dynld initcgo initcgo "/home/moriyoshi/src/go/pkg/linux_amd64/libcgo.so"
#pragma dynld libcgo_thread_start libcgo_thread_start "/home/moriyoshi/src/go/pkg/linux_amd64/libcgo.so"
#pragma dynld _cgo_malloc _cgo_malloc "/home/moriyoshi/src/go/pkg/linux_amd64/libcgo.so"
#pragma dynld _cgo_free free "/home/moriyoshi/src/go/pkg/linux_amd64/libcgo.so"

extern void runtime·entersyscall(void);
extern void runtime·exitsyscall(void);

extern Slice os·Args;

struct Itab {
    InterfaceType *inter;
    Type* type;
    Itab *link;
    int32 bad;
    int32 unused;
    void (*fun[])(void);
};

void onInitCallback(Iface *param)
{
    ((void(*)(void*))param->tab->fun[0])(param->data);
} 

IMPORT_FUNC(_cgo_wx_initialize)
void wx·initialize(Iface iface, bool retval)
{
    uint8 **argv;
    int32 i;

    argv = malloc(os·Args.len * sizeof(*argv));
    for (i = 0; i < os·Args.len; i++) {
        String *arg = &((String*)os·Args.array)[i];
        byte *p = cmalloc(arg->len + 1);
        mcpy((byte *)p, arg->str, arg->len);
        p[arg->len] = '\0';
        argv[i] = p;
    }

    {
        _cgo_wx_initialize_args args = {
            *(opaque*)&iface,
            { m, g, (void(*)(void))onInitCallback },
            runtime·entersyscall,
            runtime·exitsyscall,
            os·Args.len,
            argv,
            false
        };
        cgocall(_cgo_wx_initialize, &args);
        retval = args.r;
    }
    for (i = 0; i < os·Args.len; i++) {
        cfree(argv[i]);
    }
	FLUSH(&retval);
}

IMPORT_FUNC (_cgo_wx_uninitialize) 
void wx·uninitialize()
{
    cgocall(_cgo_wx_uninitialize, nil);
}

IMPORT_FUNC(_cgo_wx_pollEvent)
void wx·pollEvent(bool retval)
{
    _cgo_wx_pollEvent_args args = { retval };
    cgocall(_cgo_wx_pollEvent, &args);
	FLUSH(&retval);
}

IMPORT_FUNC(_cgo_wx_dispatchEvent)
void wx·dispatchEvent(bool retval)
{
    _cgo_wx_dispatchEvent_args args = { retval };
    cgocall(_cgo_wx_dispatchEvent, &args);
	FLUSH(&retval);
}

IMPORT_FUNC(_cgo_wx_set_top_window)
void wx·setTopWindow(Window *wnd)
{
    _cgo_wx_set_top_window_args args = { wnd->wnd };
    cgocall(_cgo_wx_set_top_window, &args);
}

IMPORT_FUNC(_cgo_wx_window_show)
void wx·window_Show(Window *wnd)
{
    _cgo_wx_window_show_args args = { wnd->wnd };
    cgocall(_cgo_wx_window_show, &args);
}

IMPORT_FUNC(_cgo_wx_frame_new)
void wx·frame_New(Window *parent, int32 windowID, String title, Point pos, Size size, Window *retval)
{
    retval = mal(sizeof(Window));
    {
        _cgo_wx_frame_new_args args = { parent, windowID, title.str, title.len, pos, size, nil };
        cgocall(_cgo_wx_frame_new, &args);
        retval->wnd = args.r;
    }
    FLUSH(&retval);
}
