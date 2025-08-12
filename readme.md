<h1 align="center">
  <a href="https://github.com/reim-developer/zClipboard">
    <img src="/assets/icon.png" width=200 height=200/><br>
  </a>
    zClipboard: A Mordern Clipboard Manager
</h1>

<h4 align="center">Save Your Clipboard History, Fast.</h4>

<div align="center">
    <a href="https://github.com/Reim-developer/zClipboard/actions/workflows/macos.yml"><img src="https://github.com/Reim-developer/zClipboard/actions/workflows/macos.yml/badge.svg?branch=master" /></a>
    <a href="https://github.com/Reim-developer/zClipboard/actions/workflows/linux.yml"><img src="https://github.com/Reim-developer/zClipboard/actions/workflows/linux.yml/badge.svg?branch=master" /></a>
    <a href="https://github.com/Reim-developer/zClipboard/actions/workflows/windows.yml"><img src="https://github.com/Reim-developer/zClipboard/actions/workflows/windows.yml/badge.svg?branch=master" /></a>
</div>

---

## Features
+ Fast and lightweight: ~30–80 MiB RAM when idle (varies when hidden).
+ Cross-platform, reboot-safe clipboard history.
+ Text and image clipboard support with instant preview.
+ Save image directly from clipboard preview.
+ LAN sync with manual device confirmation (secure, no token bullshit).
+ Beautiful, searchable table view with real-time filtering.
+ Pin/unpin entries to keep them on top.
+ Clear history in one click, no background daemon creep.
+ Notification, settings system.

## zClipboard vs another clipboard manager software
| Features                    | zClipboard                                                                | CopyQ                                                      |
|-----------------------------|---------------------------------------------------------------------------|------------------------------------------------------------|
| **RAM usage when idle**     | ~30–80 MiB (lightweight, varies when hidden)                              | Usually higher, can bloat over time                        |
| **Cross-platform support**  | Windows, Linux (official Windows support)                                 | Windows, Linux, macOS                                      |
| **Clipboard history**       | Reboot-safe (persists after restart)                                      | Saves history, but unsure if reboot-safe                   |
| **Image clipboard support** | Yes, with instant preview and direct saving                               | Yes, with preview                                          |
| **LAN sync**                | Yes, manual device confirmation, no tokens                                | Not available or less secure                               |
| **User interface**          | Beautiful, searchable table with real-time filtering                      | Feature-rich GUI but heavier                               |
| **Pin/unpin entries**       | Yes                                                                       | Yes                                                        |
| **Clear history**           | One-click clear, no background daemon creep                               | Has clear function, but daemon runs in background          |
| **Notification system**     | Yes, with deep customization                                              | Yes, but less customizable                                 |
| **Special features**        | Ultra lightweight, no daemon creep, heavy metaprogramming for performance | Feature-packed but increasingly resource-heavy and complex |
| **Languages used in dev**   | C++ (81%), Perl, Python, Shell, PowerShell, CMake                         | Mainly C++ and Qt                                          |
| **Linux installation**      | Build from source or install via AUR (`yay -S zclipboard`)                | Available in many distro repos                             |

## Install:
**For ArchLinux:**
* *Install via AUR:*
```bash
yay -S zclipboard
```
