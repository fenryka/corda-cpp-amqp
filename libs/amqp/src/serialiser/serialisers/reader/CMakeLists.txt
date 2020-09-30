target_sources (amqp
    PRIVATE
        Reader.cxx
        CompositeReader.cxx
        property-readers/IntPropertyReader.cxx
        property-readers/LongPropertyReader.cxx
        property-readers/BoolPropertyReader.cxx
        property-readers/DoublePropertyReader.cxx
        property-readers/StringPropertyReader.cxx
        restricted-readers/MapReader.cxx
        restricted-readers/ListReader.cxx
        restricted-readers/ArrayReader.cxx
        restricted-readers/EnumReader.cxx
)