# ✅ Roblox CFG Bypass (Post-Hyperion Patch)

> A working Control Flow Guard (CFG) bypass for Roblox after the latest Hyperion patch.
> 
> ✅ Confirmed working on **Roblox version: `version-ff05edc617954c5b`**

---

## ⚙️ About

This repository demonstrates a **fully functional CFG bypass** that remains effective even after Roblox’s most recent Hyperion security updates.

Whether you’re researching reverse engineering, studying low-level Windows internals, or learning about CFG internals and exploit mitigation bypasses — this code is for educational purposes only.

---

## 🔒 What Changed in Hyperion?

Roblox’s `Hyperion` module introduced new protections, including:
- CFG whitelist verification
- Hash and validation checks
- A tighter cache system for fast CFG lookups

This bypass:
- **Directly patches the CFG bitmap/cache**
- **Avoids `insert_set` entirely**
- **Supports manual mapping DLL injection**
- **Works with or without page hash spoofing**

---

## 📚 Features

- ✅ Working CFG bypass even after Hyperion patch
- ✅ Manual mapping (mmap) compatible
---

## 🧠 Learn More or Need Help?

If you want help implementing this in your injector, or just want to learn more about how CFG whitelisting works in Roblox:

📌 **Join the Community**  
➡️ [https://discord.gg/ZTqQJCvsCg](https://discord.gg/ZTqQJCvsCg)

---

## 📂 Disclaimer

> This project is for **educational and research purposes only**.  
> We do **not condone** malicious usage or violating the terms of service of any platform.

---
