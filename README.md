# vishal_workspace

========================================================================================================================================
1-->
Constructors
Writing conventional operations, such as a copy and a destructor, can be tedious and error-prone, so
the compiler can generate them for us as needed. By default, a class provides:
• A default constructor: X()
• A copy constructor: X(const X&)
• A copy assignment: X& operator=(const X&)
• A move constructor: X(X&&)
• A move assignment: X& operator=(X&&)
• A destructor: ˜X()
518 Construction, Cleanup, Copy, and Move Chapter 17
By default, the compiler generates each of these operations if a program uses it. However, if the
programmer takes control by defining one or more of those operations, the generation of related
operations is suppressed:
• If the programmer declares any constructor for a class, the default constructor is not generated
for that class.
• If the programmer declares a copy operation, a move operation, or a destructor for a class,
no copy operation, move operation, or destructor is generated for that class.
Unfortunately, the second rule is only incompletely enforced: for backward compatibility, copy
constructors and copy assignments are generated even if a destructor is defined. However, that generation
is deprecated in the ISO standard (§iso.D), and you should expect a modern compiler to
warn against it.
If necessary, we can be explicit about which functions are generated (§17.6.1) and which are no
==============================================================================================================================================
