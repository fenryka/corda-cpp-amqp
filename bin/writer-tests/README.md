# Serialization Writer Tests

Simple programs that define a basic serialization scenario, i.e. one
or more classes that we want to serialise, instantiates those classes, 
serializes them, and writes the value to a file. This can then be
checked with any of our tools for inspecting Corda blobs, including
the actual Java blob-inspector found in the tools top level directory

## Writer Test 1

Our most basic test, a single composite with a single primitive
property

```
class {
    int
}
```

## Writer Test 2

A Slight extension to test 1 with multiple primitive properties

```
class {
    int
    int
    int
}
```

## Writer Test 3

Another simple test, however this time with String primitives
instead of integers. (And yes, in C++ strings aren't primitve
types but in AMQP they are so that's how we're treating
them).

```
class {
    String
    String
}
```

## Writer Test 4

Starts adding a layer of complexity by having one composite
contain another, i.e. rather than jsut primitive properties
one composite type contains another as a property

```
class Inner {
    int
    string
}

class Outer {
    Inner
}
```

## Writer Test 5

Add recursive classes, that is where a class has a reference to an instance
of itself. NOTE: this will not support cyclic refernces since the Corda
framework itself doesn't
