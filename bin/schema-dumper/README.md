# Schema Dumper

The Schema Dumper can interrogate a Corda AMQP serialised blob and write the schema contained within to the
console. This can be formatted either as "raw" output, where the underlying proton tree structure
is exposed, or an (imperfect) transformation to an AVRO schema can be made

## Usage

```./schema-dumper <file> <mode[raw|avro]>```

For example:

```./schema-dumper ../test-files/_ii_ raw ```