#include <wx/wx.h>
#include <wx/except.h>
#include <wx/evtloop.h>

typedef uint8_t byte;
typedef int32_t int32;
#include "wx.h"

extern "C" void __crosscall(void *M, void *G, void(*fn)(), void *);
static void (*runtime_exitsyscall)();
static void (*runtime_entersyscall)();

void crosscall(Callback const& cb, void *param)
{
    //__crosscall(cb.m, cb.g, runtime_exitsyscall, NULL);
    __crosscall(cb.m, cb.g, cb.fn, param);
    //__crosscall(cb.m, cb.g, runtime_entersyscall, NULL);
}

class wxGoApp: public wxApp {
public:
    wxGoApp(opaque const& param, Callback const& onInitCallback)
        : param_(param), onInitCallback_(onInitCallback) {
        m_mainLoop = new wxEventLoop();
        wxEventLoop::SetActive(m_mainLoop);
    }

    virtual ~wxGoApp() {
        delete m_mainLoop;
    }

    virtual bool OnInit() {
        crosscall(onInitCallback_, &param_);
        return true;
    }

    wxEventLoop* GetMainLoop() const {
        return m_mainLoop;
    }

private:
    opaque param_;
    Callback onInitCallback_; 
};

extern "C" {

void _cgo_wx_initialize(_cgo_wx_initialize_args *args)
{
    args->r = NULL;
    if (!wxApp::GetInstance()) {
        runtime_entersyscall = args->runtime_entersyscall;
        runtime_exitsyscall = args->runtime_exitsyscall;
        new wxGoApp(args->param, args->callback);
        wxEntryStart(args->argc, (char**)args->argv);
        wxInitAllImageHandlers();
    }
    wxTRY {
        if (!wxTheApp->CallOnInit()) {
            return;
        }

        struct CallOnExit { ~CallOnExit() { wxTheApp->OnExit(); } } _;
    }
    wxCATCH_ALL(wxTheApp->OnUnhandledException(); return;)

    args->r = wxApp::GetInstance();
}

void _cgo_wx_pollEvent(_cgo_wx_pollEvent_args *args)
{
    while (!reinterpret_cast<wxGoApp*>(wxTheApp)->GetMainLoop()->Pending()) {
        if (!wxTheApp->ProcessIdle()) {
            args->r = false;
            break;
        }
    }
}

void _cgo_wx_dispatchEvent(_cgo_wx_dispatchEvent_args *args)
{
    args->r = reinterpret_cast<wxGoApp*>(wxTheApp)->GetMainLoop()->Dispatch();
}

void _cgo_wx_uninitialize(void)
{
    if (wxApp::GetInstance()) {
        ::wxEntryCleanup();
    }
}

void _cgo_wx_frame_new(_cgo_wx_frame_new_args *args)
{
    args->r = new wxFrame(reinterpret_cast<wxWindow*>(args->parent),
            args->window_id,
            wxString(reinterpret_cast<wxChar const*>(args->title),
                     args->title_len),
            wxPoint(args->pos.x, args->pos.y),
            wxSize(args->size.w, args->size.h));
}

void _cgo_wx_window_show(_cgo_wx_window_show_args *args)
{
    reinterpret_cast<wxWindow*>(args->wnd)->Show();
}

void _cgo_wx_set_top_window(_cgo_wx_set_top_window_args *args)
{
    wxTheApp->SetTopWindow(reinterpret_cast<wxWindow*>(args->wnd));
}

} // extern "C"
