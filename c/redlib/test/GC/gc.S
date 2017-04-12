	.file	"gc.c"
	.file 1 "gc.c"
	.section	.debug_abbrev
.Ldebug_abbrev0:
	.section	.text
.Ltext0:
	.section	.debug_info
.Ldebug_info0:
	.section	.debug_line
.Ldebug_line0:
	.text
	.align 16
.globl function
	.type	function,@function
function:
.LFB1:
	.loc 1 43 0
	pushl	%ebp
.LCFI0:
	movl	%esp, %ebp
.LCFI1:
	.loc 1 44 0
	movl	12(%ebp), %eax
	addl	8(%ebp), %eax
	addl	16(%ebp), %eax
	.loc 1 45 0
	popl	%ebp
	ret
.LFE1:
.Lfe1:
	.size	function,.Lfe1-function
	.align 16
.globl main
	.type	main,@function
main:
.LFB2:
	.loc 1 51 0
	pushl	%ebp
.LCFI2:
	movl	%esp, %ebp
.LCFI3:
	subl	$8, %esp
.LCFI4:
	andl	$-16, %esp
.LBB2:
	.loc 1 52 0
	subl	$4, %esp
	pushl	$3
	pushl	$2
	pushl	$1
.LCFI5:
	call	function
	addl	$16, %esp
	movl	%eax, -4(%ebp)
	.loc 1 56 0
	movl	$0, %eax
.LBE2:
	.loc 1 57 0
	movl	%ebp, %esp
	popl	%ebp
	ret
.LFE2:
.Lfe2:
	.size	main,.Lfe2-main
	.section	.text
.Letext0:
	.section	.debug_info
	.long	0xfc
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.Ldebug_line0
	.long	.Letext0
	.long	.Ltext0
	.string	"gc.c"
	.string	"/home/redhat/devel/c/redlib/test"
	.string	"GNU C 3.0.1"
	.byte	0x1
	.uleb128 0x2
	.long	0x8f
	.byte	0x1
	.string	"function"
	.byte	0x1
	.byte	0x2b
	.long	0x8f
	.long	.LFB1
	.long	.LFE1
	.byte	0x1
	.byte	0x55
	.uleb128 0x3
	.string	"x"
	.byte	0x1
	.byte	0x28
	.long	0x8f
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x3
	.string	"y"
	.byte	0x1
	.byte	0x29
	.long	0x8f
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x3
	.string	"z"
	.byte	0x1
	.byte	0x2a
	.long	0x8f
	.byte	0x2
	.byte	0x91
	.sleb128 16
	.byte	0x0
	.uleb128 0x4
	.string	"int"
	.byte	0x4
	.byte	0x5
	.uleb128 0x2
	.long	0xeb
	.byte	0x1
	.string	"main"
	.byte	0x1
	.byte	0x33
	.long	0x8f
	.long	.LFB2
	.long	.LFE2
	.byte	0x1
	.byte	0x55
	.uleb128 0x3
	.string	"argc"
	.byte	0x1
	.byte	0x30
	.long	0x8f
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x3
	.string	"argv"
	.byte	0x1
	.byte	0x31
	.long	0xeb
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x3
	.string	"envp"
	.byte	0x1
	.byte	0x32
	.long	0xeb
	.byte	0x2
	.byte	0x91
	.sleb128 16
	.uleb128 0x5
	.string	"i"
	.byte	0x1
	.byte	0x34
	.long	0x8f
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0x0
	.uleb128 0x6
	.byte	0x4
	.long	0xf1
	.uleb128 0x6
	.byte	0x4
	.long	0xf7
	.uleb128 0x4
	.string	"char"
	.byte	0x1
	.byte	0x6
	.byte	0x0
	.section	.debug_abbrev
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x10
	.uleb128 0x6
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1b
	.uleb128 0x8
	.uleb128 0x25
	.uleb128 0x8
	.uleb128 0x13
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames
	.long	0x24
	.value	0x2
	.long	.Ldebug_info0
	.long	0x100
	.long	0x4b
	.string	"function"
	.long	0x96
	.string	"main"
	.long	0x0
	.section	.debug_aranges
	.long	0x1c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0x0
	.value	0x0
	.value	0x0
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	0x0
	.long	0x0
	.data
	.ident	"GCC: (GNU) 3.0.1"
