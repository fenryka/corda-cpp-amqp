#Corda Blob Inspection

This is my pet project to write a C++ version of the Corda serialization framework. Currently... it doesn't work, so don't use it. It will print out some of the schema elements of a serialized blob, then crash, because it doesn't
cope with the transforms schema in the Envelope.

It's using the C version of the proton AMQP library because there isn'ta C++ version that's easily available for
MacOS.

If I've got time, this might get better!.


