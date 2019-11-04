# Custom pysmurf data transmitter example

Example of how to write an example custom data transmitter class for [pysmurf](https://github.com/slaclab/pysmurf), and how to use it.

This example's transmitter class defines a `CustomTransmitter` device which is added to the pysmurf's `SmurfProcessor` device (for more details see [here](https://github.com/slaclab/pysmurf/blob/pre-release/README.SmurfProcessor.md)). The `CustomTransmitter` device has a variable called `Debug`; when set to `True`, the custom class will print some word of the header and some data points from the SmurfPacket every time a new packet is received.