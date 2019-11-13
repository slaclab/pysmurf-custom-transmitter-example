FROM tidair/pysmurf-server-base:v4.0.0-rc6

WORKDIR /usr/local/src
RUN git clone https://github.com/slaclab/pysmurf-custom-transmitter-example.git
WORKDIR pysmurf-custom-transmitter-example
RUN mkdir build
WORKDIR build
RUN cmake -DCMAKE_BUILD_TYPE=Release .. && make
WORKDIR ..
ENV PYTHONPATH /usr/local/src/pysmurf-custom-transmitter-example/lib:${PYTHONPATH}
ENV PYTHONPATH /usr/local/src/pysmurf-custom-transmitter-example/python:${PYTHONPATH}
ENV PYTHONPATH /usr/local/src/pysmurf/server_scripts:${PYTHONPATH}
