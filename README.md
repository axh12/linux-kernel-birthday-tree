# Linux Kernel Birthday Tree

This project contains:
- A **Linux kernel module** that creates and manages a birthday-linked list structure.
- A **user-space C program** that displays the current process tree using system-level traversal.

## 📁 Structure
- `kernel_module/` — Linux kernel module code and Makefile
- `user_program/` — User-space program written in C

## 🛠 Build & Run Instructions

### 🧩 Kernel Module
```bash
cd kernel_module
make
sudo insmod birthday_module.ko
# To check output:
dmesg | tail
sudo rmmod birthday_module
