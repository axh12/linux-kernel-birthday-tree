#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x9931d80, "module_layout" },
	{ 0x6663f577, "single_release" },
	{ 0x20236789, "seq_lseek" },
	{ 0xfec2686f, "seq_read" },
	{ 0x37a0cba, "kfree" },
	{ 0xc5b2e28c, "remove_proc_entry" },
	{ 0x5204ad50, "proc_create" },
	{ 0x92997ed8, "_printk" },
	{ 0x986e99b, "kmem_cache_alloc_trace" },
	{ 0x6404c07a, "kmalloc_caches" },
	{ 0x9f9fb316, "seq_printf" },
	{ 0x6a238606, "single_open" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "8639F11C1160AD4F9737742");
