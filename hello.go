package main

import "wx"

type App struct {
    handle uintptr;
}

func (self *App) SetHandle(handle uintptr) {
    self.handle = handle
}

func (self *App) OnInit()
{
    frame := wx.NewFrame(nil, -1, "test", wx.Point { 50, 50 }, wx.Size { 320, 240 });
    frame.Show();
    wx.SetTopWindow(frame)
}

func main() {
    app := new(App);
    wx.Initialize(app);
    for wx.PollEvent() && wx.DispatchEvent() {
    }
    wx.Uninitialize()
}
