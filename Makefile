.PHONY: all
all:
	g++ -o prog main.cxx Envelope.cxx AMQPDescriptor.cxx proton_wrapper.cxx AMQPDescriptorRegistory.cxx -lqpid-proton -std=c++14
