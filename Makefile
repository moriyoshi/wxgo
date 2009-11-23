include $(GOROOT)/src/Make.$(GOARCH)

TARG=wx
STUB_GOFILES=wx.go
GOFILES+=$(STUB_GOFILES)
CLEANFILES+=hello
OFILES+=wx.stub.$O
CGO_CFLAGS=$(shell wx-config --cflags) -finput-charset=UTF-8
CGO_LDFLAGS=$(shell wx-config --libs) crosscall.o

%.stub.$O: %.stub.c
	$(CC) -p $(CFLAGS) $(RUNTIME_CFLAGS) -DWRAP_SO=\"$(pkgdir)/$(dir)/$(elem)_$(patsubst %.stub.$O,%,$@).so\" $<

%.cgo4.o: %.wrap.c  crosscall.o
	gcc -g $(_CGO_CFLAGS_$(GOARCH)) -fPIC -O2 -o $@ -c $(CGO_CFLAGS) $<

%.cgo4.o: %.wrap.cpp crosscall.o
	g++ -g $(_CGO_CFLAGS_$(GOARCH)) -fPIC -O2 -o $@ -c $(CGO_CFLAGS) $<

PREREQ += $(patsubst %.go,$(pkgdir)/$(dir)/$(elem)_%.so,$(STUB_GOFILES))
include $(GOROOT)/src/Make.pkg

crosscall.o: $(GOARCH).S
	gcc -fPIC $(_CGO_CFLAGS_$(GOARCH)) $(CGO_CFLAGS) -c -o $@ $<

%: install %.go
	$(GC) $*.go
	$(LD) -o $@ $*.$O
