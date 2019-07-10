// author: Adrian Michałek
// email: devmichalek@gmail.com

0.0 // The proper order for the specified needs is:
    // Compile test.c:
    //    gcc -c test.c
    // Create static library:
    //    ar -cvq libtest.a test.o
    // Compile and create executable:
    //    gcc -o main main.c libtest.a # or
    //    gcc -o main main -L/path/to/current/directory -ltest

0.1 // The proper order for the specified needs is:
    // Compile test.c with -fPIC (Platform Independent Code flag)
    //    gcc -fPIC -c test.c
    // Create dynamic library
    //    gcc -shared test.o -o libtest.so
    // Compile and create executable:
    //    gcc main.c -L/path/to/current/directory -ltest -o main
    // Set $LD_LIBRARY_PATH variable:
    //    LD_LIBRARY_PATH=path/to/current/directory
    //    export LD_LIBRARY_PATH

0.2 // You have to use --whole-archive and --no-whole-archive flag.
    // These flags are linker flags so the use is actually -Wl,<flag>
    // While creating shared library we specify --whole-archive that means take all the objects from static library even these not needed (add2() function is not used in dynamic library but it may be used by dynamic library users). Then turn off this flag by setting --no-whole-archive, this step is crucial to escape infinite loop error.

    // Compile part.c and create static library:
    //    gcc -c part.c
    //    ar -cvq libpart.a part.o
    // Compile test.c and create a shared library:
    //    gcc -fPIC -c test.c
    //    gcc -shared -Wl,--whole-archive libpart.a Wl,--no-whole-archive test.o -o libtest.so
    // Set $LD_LIBRARY_PATH variable:
    //    LD_LIBRARY_PATH=path/to/current/directory
    //    export LD_LIBRARY_PATH
    // Compile and create executable:
    //    gcc main.c libtest.so -o main

0.3 // The only substantial difference is that by default all Windows DLL linker symbols are hidden, whereas in Linux all the dynamic library linker symbols are by default exported.

0.4 // Method I (affecting the whole body of code):
    // -fvisibility compiler flag
    // by passing the -fvisibility=hidden it is possible to make every dynamic library symbos invisible to whoever tries to dynamically link against the dynamic library.
    // Method II (affecting individual symbols only)
    // __attribute__ ((visibility("<default | hidden>")))
    // By decorating the function signature with the attribute property, you instruct the linker to either allow (default) or not allow (hidden) exporting the symbol.
    // Method III (affecting individual symbols or a group of symbols)
    // #pragma GCC visibility [push | pop]
    /* // Some header file may contain:
      #pragma visibility push(hidden)
      void someprivatefunction_1(void);
      void someprivatefunction_2(void);
      ...
      void someprivatefunction_N(void);
      #pragma visibility pop
    */

0.5 // Purpose, Linux Version, Windows Version
    // Library Loading, dlopen(), LoadLibrary()
    // Finding Symbol, dlsym(), GetProcAddress()
    // Library Unloading, dlclose(), FreeLibrary()
    // Error Reporting, dlerror(), GetLastError()