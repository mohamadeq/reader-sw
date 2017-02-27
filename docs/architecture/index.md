Reader Firmware Architecture
============================

This firmware has several goals:

  - Robustness
  - Maintainability
  - Extensibility
  - Testability

Good software architecture is instrumental in achieving those goals. In order to be extensible and testable the firmware must be modular. In order to be robust, those modules must be watched over and be restartable in case of a problem. In order to be maintainable, internal functioning of those modules must be well-documented, and they must have clearly defined interfaces to the rest of the system.

This firmware is built on top of a [ChibiOS](http://www.chibios.org). ChibiOS provides threading, synchronization primitives and a very feature-rich HAL. Using the threading paradigm simplifies design of modules and helps to isolate them from the rest of the system. It also makes implementing a watchdog to watch over those modules (and restart them ifneedbe) a simple task.

Components and their interaction
--------------------------------

Primary task of the Reader is to obtain user identification data (usually by reading an RFID card), send the identification data to the Controller and inform the user of an authentication result.

Reader is a replaceable component of a larger system. Therefore multiple versions of the Reader may exist. The basic version is only able to read ID of a ISO/IEC 14443-3 (A) compliant card and inform the user of the result using a simplistic user interface consisting of a speaker and two bi-color LEDs. However, in the future, there may be a version of the Reader which authenticates users using fingerprints and a personal code entered on a keyboard, displaying results on a color LCD. Each version with different capabilities will be referred to as a **Reader Type** from now on.

It is presumed that each *Reader Type* will have a fundamentally different business logic and therefore can be uniquely identified by that logic. A code implementing business logic will be referred to as a **Core** from now on. *Cores* are stored in folder `src/cores`.

A Core will use one or more Modules. Module is a piece of code, usually run as a thread that Does One Thing and Does It Well. Modules are stored in folder `src/modules`. Communication with modules will be done using [ChibiOS Mailboxes](http://www.chibios.org/dokuwiki/doku.php?id=chibios:book:kernel_mailboxes). Each *Module* has a single mailbox, (called *Module Inbox*), to which the *Core* can send messages. A *Core* has also its *Core Inbox*, to which each *Module* sends messages. A module can communicate only with the core, not with other modules.

Some modules can implement common **Module Interface** (`/src/module-interfaces`) and therefore can be interchangeable. Therefore there may be more combinations of the same *Core* but different set of *Modules*, compiled for a different hardware board. This combination is called **Reader Flavour**. One *Reader Type* can have different flavours, which provide the same basic functionality but on different hardware. This way a tremendous code reusability can be achieved and all generations of evolving hardware can still be supported.

### Messages

ChibiOS Mailboxes handle messages of type `msg_t`. This type is guaranteed to be compatible with data pointers of the platform the firmware was compiled for. Since messages may carry more information that can fit to `msg_t`, each message is a pointer to a structure with the following header:

```c
typedef struct {
    uint8_t interface_number;
    uint16_t message_type_major;
    uint8_t message_type_minor;
} message_header_t

typedef struct {
    message_header_t header;

    ... message specific fields ...
} some_message_t
```

These messages must come from somewhere, and must have a life-cycle. There are several options:

  - Each module has statically allocated a fixed number of messages.
  - Each module allocates its messages dynamically.
  - There is a central dynamic allocator for messages.

We will be going with the third option. Since dynamic allocation of memory is forbidden for modules and cores, and ChibiOS itself is also not allocating memory dynamically (unless we use features like dynamic threads, which we don't) the only dynamic allocator is the central message allocator.

You can read more about message lifecycle, central message allocator and its usage here:

```eval_rst

.. toctree::
    :maxdepth: 2

    central_message_allocator

```


Reader Types
------------

```eval_rst

.. toctree::
    :maxdepth: 2

    types/basic-isic-reader

```

Module Interfaces
-----------------

A module interface is a header file formally defining and documenting message numbers and message formats that can be used to communicate with the given module. Each module may implement one or more of such interfaces.

Each message is a pointer to the following structure:

```eval_rst

.. toctree::
    :maxdepth: 2

    interfaces/basic-lock-unlock-ui
    interfaces/id-reader
    interfaces/reader-proto

```

Modules
-------
