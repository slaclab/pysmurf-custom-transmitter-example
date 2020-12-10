[![CD](https://github.com/slaclab/pysmurf-custom-transmitter-example/workflows/CD/badge.svg)](https://github.com/slaclab/pysmurf-custom-transmitter-example/actions?query=workflow%3ACD)

# Custom pysmurf data transmitter example

Example of how to write an example custom data transmitter class for [pysmurf](https://github.com/slaclab/pysmurf), and how to use it.

## Description

This example's transmitter class defines a `CustomTransmitter` device which is added to the pysmurf's `SmurfProcessor` device (for more details see [here](https://github.com/slaclab/pysmurf/blob/pre-release/README.SmurfProcessor.md)). The `CustomTransmitter` device has a variable called `Debug`; when set to `True`, the custom class will print some word of the header and some data points from the SmurfPacket every time a new packet is received.

## How to write a custom transmitter

To write a custom transmitter, which is described in the pysmurf repository [here](https://github.com/slaclab/pysmurf/blob/pre-release/README.CustomDataTransmitter.md), you would:
- Write a C++ class which inherits from the pysmurf's [BaseTransmitter class](https://github.com/slaclab/pysmurf/blob/pre-release/include/smurf/core/transmitters/BaseTransmitter.h). In that class you should override the [transmit method](https://github.com/slaclab/pysmurf/blob/pre-release/include/smurf/core/transmitters/BaseTransmitter.h#L74) to process every new SMuRF packet according to your requirements. You can take a look in this repository to [my_transmitter.cpp](src/my_transmitter.cpp) as an example.
  - In your new C++ class you can add new variable and methods (as the `debug` flag, and the `setDebug` and `getDebug` in this example),
  - In you new C++ class you can expose methods to python if you want to expose then in the pysmurf's pysmurf tree (this example expose the `setDebug` and `getDebug` methods),
- Write a python wrapper for your C++ class (see [MyTransmitter.py](python/mymodule/transmitters/_MyTransmitter.py) as an example),
- Configure cmake to find Rogue, smurf and all other needed libraries (see [CMakeLists.txt](CMakeLists.txt) as an example),
- Write a startup script where you call the appropriate pysmurf root device, attaching your new module (see [cmb_eth.py](server_scripts/cmb_eth.py) and [dev_board_eth.py](server_scripts/dev_board_eth.py) as examples, which use the [Common.py](https://github.com/slaclab/pysmurf/blob/main/python/pysmurf/core/server_scripts/Common.py) common scripts provided by pysmurf).
- Finally, write a launcher script to start you server application (see [start_example_server.sh](scripts/start_example_server.sh) as an example, which uses the common functions from [server_common.sh](https://github.com/slaclab/pysmurf/blob/main/docker/server/scripts/server_common.sh) provided by pysmurf).

## Docker image

This example provides a [Dockerfile](Dockerfile) as well as a [script](build_docker.sh) to build a docker image with this code. An docker image is also automatically build and push to this [Dockerhub repository](https://hub.docker.com/r/tidair/pysmurf-custom-transmitter-example) for every tagged released of this repository, using GitHub Actions. The `Dockerfile` defines as its `entrypoint` the example [startup script](scripts/start_example_server.sh).

For more information about how to run pysmurf in docker container take a look [here](https://github.com/slaclab/pysmurf/blob/pre-release/README.Docker.md).
