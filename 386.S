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

/*
 * void crosscall(M *m, G *g, void (*fn)(void), void *arg)
 *
 * Calling into the 8c tool chain, where all registers are caller save.
 * Called from standard x86 ABI, where %ebp, %ebx, %esi,
 * and %edi are callee-save, so they must be saved explicitly.
 */
.globl EXT(__crosscall)
EXT(__crosscall):
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	pushl %esi
	pushl %edi

	movl 8(%ebp), %eax	/* fn */
    push 12(%ebp)
	call *%eax

	popl %edi
	popl %esi
	popl %ebx
	popl %ebp
	ret

