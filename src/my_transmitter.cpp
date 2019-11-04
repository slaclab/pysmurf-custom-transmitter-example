#include <iostream>
#include "smurf/core/transmitters/BaseTransmitter.h"

namespace bp = boost::python;
namespace sct = smurf::core::transmitters;

class MyTransmitter : public sct::BaseTransmitter
{
public:
    void transmit(SmurfPacketROPtr sp)
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
    };

    static void setup_python()
      {
        bp::class_<MyTransmitter, std::shared_ptr<MyTransmitter>, bp::bases<ris::Slave>, boost::noncopyable >("MyTransmitter",bp::init<>())
        ;

        bp::implicitly_convertible<std::shared_ptr<MyTransmitter>, ris::SlavePtr>();
      };
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
