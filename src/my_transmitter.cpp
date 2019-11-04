#include <iostream>
#include "smurf/core/transmitters/BaseTransmitter.h"

namespace bp = boost::python;
namespace sct = smurf::core::transmitters;

// Custom transmitter class
class MyTransmitter : public sct::BaseTransmitter
{
public:
    // Custom class constructor and destrcutor
    MyTransmitter() : sct::BaseTransmitter(), debug(false) {};
    ~MyTransmitter() {};

    // This is the virtal method defined in 'BaseTransmitter' which is call whenever a
    // new SMuRF packet is ready.
    void transmit(SmurfPacketROPtr sp)
    {
	// If the debug flag is enabled, print part of the SMuRF Packet
        if (debug)
        {
            std::cout << "=====================================" << std::endl;
            std::cout << "Packet received" << std::endl;
            std::cout << "=====================================" << std::endl;
            std::cout << std::endl;
            std::cout << "-----------------------" << std::endl;
            std::cout << " HEADER:" << std::endl;
            std::cout << "-----------------------" << std::endl;
            std::cout << "-----------------------" << std::endl;
            std::cout << " DATA (first 20 points):" << std::endl;
            std::cout << "-----------------------" << std::endl;
            std::cout << "-----------------------" << std::endl;
            std::cout << std::endl;
            std::cout << "=====================================" << std::endl;
        }
    };

    // Set/Get the debug flag
    void       setDebug(bool d) { debug = d;    };
    const bool getDebug()       { return debug; };

    static void setup_python()
    {
        bp::class_< MyTransmitter, 
	            std::shared_ptr<MyTransmitter>, 
		    bp::bases<ris::Slave>, 
		    boost::noncopyable >("MyTransmitter",bp::init<>())
            .def("setDebug", &MyTransmitter::setDebug)
            .def("getDebug", &MyTransmitter::getDebug)
        ;
        bp::implicitly_convertible<std::shared_ptr<MyTransmitter>, ris::SlavePtr>();
    };

private:
    bool debug = false; // Debug flag

};


BOOST_PYTHON_MODULE(MyModule)
{
  PyEval_InitThreads();

  try
  {
    MyTransmitter::setup_python();
  }
  catch (...)
  {
    printf("Failed to load my processor module. import rogue first\n");
  }

  printf("Custom transmitter module loaded\n");
};
