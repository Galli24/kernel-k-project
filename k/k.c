/*
 * Copyright (c) LSE
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY LSE AS IS AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL LSE BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <k/kstd.h>
#include <stdio.h>

#include "gdt.h"
#include "idt.h"
#include "isrs.h"
#include "multiboot.h"
#include "serial.h"


void k_main(unsigned long magic, multiboot_info_t *info)
{
	(void)magic;
	(void)info;

	char star[4] = "|/-\\";
	char *fb = (void *)0xb8000;

	serial_init();
	printf("Serial initialized\r\n");

	gdt_init();
	printf("GDT initialized\r\n");

	idt_init();
	printf("IDT initialized\r\n");

	isrs_init();
	printf("ISRS intialzied\r\n");

	asm volatile("int $0");
	asm volatile("int $1");
	asm volatile("int $2");
	asm volatile("int $3");
	asm volatile("int $4");
	asm volatile("int $5");
	asm volatile("int $6");
	asm volatile("int $7");
	//asm volatile("int $8");
	asm volatile("int $9");
	//asm volatile("int $10");
	//asm volatile("int $11");
	//asm volatile("int $12");
	//asm volatile("int $13");
	//asm volatile("int $14");
	//asm volatile("int $15");
	asm volatile("int $16");
	//asm volatile("int $17");
	asm volatile("int $18");
	asm volatile("int $19");
	asm volatile("int $20");
	asm volatile("int $21");
	asm volatile("int $22");
	asm volatile("int $23");
	asm volatile("int $24");
	asm volatile("int $25");
	asm volatile("int $26");
	asm volatile("int $27");
	asm volatile("int $28");
	asm volatile("int $29");
	asm volatile("int $30");
	asm volatile("int $31");
	asm volatile("int $127");

	for (unsigned i = 0; ; ) {
		*fb = star[i++ % 4];
	}

	for (;;)
		asm volatile ("hlt");
}
