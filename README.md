# Table Of Contents

<!-- ts -->
* [C++ Corda Serialiser](#c-corda-serialiser)
    * [Initial Aim](#initial-aim)
    * [Aims](#aims)
* [The State of Play](#the-state-of-play)
    * [Currently Working](#currently-working)
    * [Fututre Work](#fututre-work)
    * [Dependencies](#dependencies)
    * [Setup](#setup)
        * [MacOS](#macos)
        * [Linux, Ubuntu](#linux-ubuntu)
<!-- te -->

> NOTE: ToC generated using https://github.com/fenryka/TOC-Generator

# C++ Corda Serialiser

This project started out as a best effort attempt at a C++ implementation of the CORDA
serialization framework in a non JVM language. Why?, well, I did the majority of the
final implementation of that Framework leading up to the release of Corda OS 1.0 and 
all the way through to full wire stability in Corda OS/ENT 3.0. It was a fun piece of
work, but obviously limited by decisions outside my control as is inevitable when
you're working as a commercial Software Engineer. 

However, it's all open source, and in my spare time I get to do things unconstrained
by commercial reality, thus this project was born. Kotlin is great!. However, under
the hood it's still targeting the JVM and thus still irritates me intensely. My one true
love will always be C++ and I needed a project to keep my hand and eye in with that
language, especially as the majority of my day-job these days is spent in meetings and 
architectural discussions, not deep down hacking away at the code. 

## Initial Aim

The initial target is a working "blob inspector", that is an exe that could take a
serialised blob from a vault (or other) and decode it using C++. Essentially, replicate
the original Kotlin Corda blob-inspector.

> Its worth noting the current (at time of writing) blob-inspector packaged with
Corda is a second version of that software that works slightly differently. The first
operated in a similar manner to this version in that it was built from first
principles, understanding the blob **only** by using what information was provided
by the blob. Essentially unpacking the schema and building readers to give
meaning to the payload.
>
> The second version eschewed that to simply use the classpath and load serialisers
using the actual Serialization framework. Both valid approaches, but he latter whilst
much less code is reliant on the blob being well formed, whilst the former can
partially unpack it and find actual bit errors.

Blob inspection is pretty much done (see later for a discussion on what tools this
library makes available). As such, the aims have widened.

## Current Goal

The ability to create C++ classes that can be serialized and deserialized in and out
of this format.

## Future Goals

A fully interoperable serialization format that works with Java / Kotlin 
classes

# Bundled Utilities

There are presently 3 completed utilities that expose various parts of the code-base
to provide usful command line tooling.

1. The Data Dumper
1. The Schema Dumper
1. The Blob Inspector

The following is a simple summary of each, mote information can be found within
the respective README files in ``/bin/<<utilitiy>>``

## The Data Dumper

Usage is simple, ```./data-dumper <<file>>```, where ```<<file>>``` should be a binary
dump of a serialized Corda blob. The output will be a JSON representation of the
blobs payload. That is, the actual data contained by the serialized classes. 

It is important to note that no attempt is made to understand the data stored within
the payload portion of the Corda blob. The data dumper simply walks the QPID/Proton 
graph and dumps the contents to the terminal (with some transformation applied
for legibility).

## The Schema Dumper

Again, usage is simple, ```./schema-dumper <<file>> <<mode>>```. File must contain a Corda 
blob. ```<<mode>>``` should be either

* raw
* avro
* amqp (not currently implemented)

The purpose is to allow a user to visualise what types are included within the blob.

### Raw Mode

In raw mode, the underlying QPID/Proton structure of the schema will be dumped to
the console in string form. This is fairly verbose as the proton graph can
get very deep for complex types.

### AVRO Mode

Attempts a best-effort translation from the encoded schema in the blob to an AVRO
schema. It's important to note this translation isn't perfect because the manner
in which we dump elements out, that is to say we don't attempt to translate them
into an intermediate representation; we simply walk the AMQP schema and try
our best to convert it to AVRO. This effectively means occasionally there
are trailing ','s where there shouldn't be and other small issues that cold
be eliminated by first parsing the schema fully. However, this feature
isn't intended to create perfect schemas, only aid in understanding for potential
future translations.

### AMQP Mode

Currently not implemented, but when I get around to it should dump out the 
schema in AMQP XML form 

## The Blob Inspector

Usage ```./blob-inspector <<file>>```. Similar constraints on the contents of "file"
apply as they do for the other utilities.

The blob-inspector takes a Corda blob, reads the schema section and constructs
_readers_ able to parse the payload section for each type it contains. Then uses
those _readers_ to ingest the payload applying semantic meaning as it goes along.

The output is a JSON representation of each element within the blob.

# Serialization

The _Work in Progress_ portion of this project. Currently working on the ability
to make C++ classes serializable, that is to instantiate a class and call
``.serialize()`` on it and get a blob back.

# Test Files

Example files created using the Corda serialization library can be found in

```
/bin/test-files
```

The naming convention for these is composite types (classes) are wrapped
by the '_' character. so:

* ``_i_`` - is a composite type continaing an integer
* ``__s__`` - is a composite type containing a composite type containing a string
* ``_Ai_`` - is a composite type containing an array of integers

# Project Requirements

> NOTE: I'm sure this could be made to work on Windows, especially using WSL2, but
> to me windows development is a country I've never visited and aren't
> interested in addressing that shortcoming. How you install libraries, find dependencies,
> actually build the code... I'm sure if you're keen you'll figure it out.

## Dependencies

 * qpid-proton
 * C++17
 * gtest
 * cmake

## Setup

### MacOS

 * brew install cmake
 * brew install qpid-proton

Google Test

 * git clone https://github.com/google/googletest
 * cd googletest
 * mkdir build
 * cd build
 * cmake ..
 * make
 * make install

### Linux, Ubuntu

 * sudo apt-get install cmake
 * sudo apt-get install libqpid-proton8-dev
 * sudo apt-get install libgtest-dev

 And now because that installer only pulls down the sources
 * cd /usr/src/googletest
 * sudo cmake .
 * sudo cmake --build . --target install

 ### Windows

 You're on your own. I have no idea how Windows works or how one builds code for it.
