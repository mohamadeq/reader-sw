Basic ISIC/ITIC Reader
======================

Uses `basic-isic-reader` core (`src/cores/basic-isic-reader`).

Uses modules implementing the following interfaces:

  - `id-reader` for reading numeric IDs
  - `reader-proto`. Reader <-> Controller communication protocol.
  - `basic-lock-unlock-ui`. Basic user interface informing user of door states.

Available in the following flavours:

  - `basic-isic-reader-revA` for the `reader-revA` board. Uses
      + `iso14443-3-uid-reader` as `id-reader`
      + `reader-proto-v1` as `reader-proto`
      + `reader-revA-ui` as `basic-lock-unlock-ui`.

Primary task of this *Reader Type* is to constantly scan for cards. When a card is found its UID is read and the Controller is informed. Controller can, at any time, tell the Reader that the door is unlocked by Readers request, that the unlock request failed, that the door is permanently unlocked or that the door is permanently locked. Upon reception of such message the Reader in turn informs the user of the situation.

It also implements self-checks and can inform the controller of an error condition.
