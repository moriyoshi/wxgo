typedef struct M M;
typedef struct G G;

typedef struct App {
    void *app;
} App;

typedef struct Window {
    void *wnd;
} Window;

typedef struct Callback {
    M* m;
    G* g;
    void (*fn)(void);
} Callback;

typedef struct Point {
    int32 x;
    int32 y;
} Point;

typedef struct Size {
    int32 w;
    int32 h;
} Size;

typedef struct opaque {
    void *_[2];
} opaque;

typedef struct _cgo_wx_initialize_args {
    opaque param;
    Callback callback;
    void (*runtime_entersyscall)(void);
    void (*runtime_exitsyscall)(void);
    int32 argc;
    byte **argv;
    bool r;
} _cgo_wx_initialize_args;

typedef struct _cgo_wx_pollEvent_args {
    bool r;
} _cgo_wx_pollEvent_args;

typedef struct _cgo_wx_dispatchEvent_args {
    bool r;
} _cgo_wx_dispatchEvent_args;

typedef struct _cgo_wx_frame_new_args {
    void *parent;
    int32 window_id;
    byte *title;
    int32 title_len;
    Point pos;
    Size size;
    void *r;
} _cgo_wx_frame_new_args;

typedef struct _cgo_wx_window_show_args {
    void *wnd;
} _cgo_wx_window_show_args;

typedef struct _cgo_wx_set_top_window_args {
    void *wnd;
} _cgo_wx_set_top_window_args;

