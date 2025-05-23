/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2013 Huawei Ltd.
 * Author: Jiang Liu <liuj97@gmail.com>
 *
 * Based on arch/arm/include/asm/jump_label.h
 */
#ifndef __ASM_JUMP_LABEL_H
#define __ASM_JUMP_LABEL_H

#ifndef __ASSEMBLY__

#include <linux/types.h>
#include <asm/insn.h>

#define HAVE_JUMP_LABEL_BATCH
#define JUMP_LABEL_NOP_SIZE		AARCH64_INSN_SIZE

#define JUMP_TABLE_ENTRY(key, label)			\
	".pushsection	__jump_table, \"aw\"\n\t"	\
	".align		3\n\t"				\
	".long		1b - ., " label " - .\n\t"	\
	".quad		" key " - .\n\t"		\
	".popsection\n\t"

/* This macro is also expanded on the Rust side. */
#define ARCH_STATIC_BRANCH_ASM(key, label)		\
	"1:	nop\n\t"				\
	JUMP_TABLE_ENTRY(key, label)

static __always_inline bool arch_static_branch(struct static_key * const key,
					       const bool branch)
{
	char *k = &((char *)key)[branch];

	asm goto(
		ARCH_STATIC_BRANCH_ASM("%c0", "%l[l_yes]")
		:  :  "i"(k) :  : l_yes
		);

	return false;
l_yes:
	return true;
}

static __always_inline bool arch_static_branch_jump(struct static_key * const key,
						    const bool branch)
{
	char *k = &((char *)key)[branch];

	asm goto(
		"1:	b		%l[l_yes]		\n\t"
		JUMP_TABLE_ENTRY("%c0", "%l[l_yes]")
		:  :  "i"(k) :  : l_yes
		);
	return false;
l_yes:
	return true;
}

#endif  /* __ASSEMBLY__ */
#endif	/* __ASM_JUMP_LABEL_H */
