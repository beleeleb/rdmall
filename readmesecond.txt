1) the folder is an eclipse workspace
*)Go to Preferences->C/C++->New CDT Project Wizard, and under Preferred Toolchains, make sure all the Executable project types are set to MacOSX GCC.

2) in order to avoid unresolved inclusion problem, I need to install CLT for OS X to get the header files:
http://osxdaily.com/2014/02/12/install-command-line-tools-mac-os-x/

3)add to paths & symbols in eclipse the directory to the header files. 

4) in order to resolve linking problem suggest adding:

-Wl,-undefined,dynamic_lookup

http://stackoverflow.com/questions/30228151/can-compile-in-ubuntu-but-not-in-mac-os-x
http://stackoverflow.com/questions/3695234/what-is-the-deal-with-undefined-symbols-in-a-shared-library-or-dylib
https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html#Link-Options
http://stackoverflow.com/questions/25373055/ld-library-path-not-working-under-os-x-10-9