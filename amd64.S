// Copyright 2009 The Go Authors.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

/*
 * Apple still insists on underscore prefixes for C function names.
 */
#ifdef __APPLE__
#define EXT(s) _##s
#else
#define EXT(s) s
#endif

// void __crosscall(M *m, G *g, void (*fn)(void*), void *arg)
.globl EXT(__crosscall)
EXT(__crosscall):
	pushq %rbx
	pushq %rbp
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15

	movq %rdi, %r14	/* m */
	movq %rsi, %r15	/* g */
    push %rcx /* [first argument] */
	call *%rdx	/* fn */
    addq $8, %rsp

	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %rbp
	popq %rbx
	ret

