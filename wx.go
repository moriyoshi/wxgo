package wx

type Window struct {
    uintptr;
}

type App interface {
    OnInit();
}

type CallbackParam struct {
    Type string;
}

type Point struct {
    X int32;
    Y int32;
}

type Size struct {
    W int32;
    H int32;
}

func initialize(app App) bool
func uninitialize()
func pollEvent() bool
func dispatchEvent() bool
func setTopWindow(*Window)
func window_Show(wnd *Window)
func frame_New(parent *Window, windowID int, title string, pos Point, size Size) *Window

func Initialize(app App) bool {
    return initialize(app)
}

func Uninitialize() {
    uninitialize()
}

func PollEvent() bool {
    return pollEvent()
}

func DispatchEvent() bool {
    return dispatchEvent()
}

func SetTopWindow(wnd *Window) {
    setTopWindow(wnd)
}

func (self *Window) Show() {
    window_Show(self)
}

func NewFrame(parent *Window, windowID int, title string, pos Point, size Size) *Window {
    return frame_New(parent, windowID, title, pos, size)
}
