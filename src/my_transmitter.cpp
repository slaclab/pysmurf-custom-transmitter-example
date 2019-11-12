#include <iostream>
#include "smurf/core/transmitters/BaseTransmitter.h"

namespace bp = boost::python;
namespace sct = smurf::core::transmitters;

// Custom transmitter class
class MyTransmitter : public sct::BaseTransmitter
{
public:
    // Custom class constructor and destructor
    MyTransmitter() : sct::BaseTransmitter(), debug(false) {};
    ~MyTransmitter() {};

    // This is the virtual method defined in 'BaseTransmitter' which is call whenever a
    // new SMuRF packet is ready.
    void transmit(SmurfPacketROPtr sp)
    {
        // If the debug flag is enabled, print part of the SMuRF Packet
        if (debug)
        {
            std::size_t numCh {sp->getHeader()->getNumberChannels()};

            std::cout << "=====================================" << std::endl;
            std::cout << "Packet received" << std::endl;
            std::cout << "=====================================" << std::endl;
            std::cout << std::endl;

            std::cout << "-----------------------" << std::endl;
            std::cout << " HEADER:" << std::endl;
            std::cout << "-----------------------" << std::endl;
            std::cout << "Version            = " << unsigned(sp->getHeader()->getVersion()) << std::endl;
            std::cout << "Crate ID           = " << unsigned(sp->getHeader()->getCrateID()) << std::endl;
            std::cout << "Slot number        = " << unsigned(sp->getHeader()->getSlotNumber()) << std::endl;
            std::cout << "Number of channels = " << unsigned(numCh) << std::endl;
            std::cout << "Unix time          = " << unsigned(sp->getHeader()->getUnixTime()) << std::endl;
            std::cout << "Frame counter      = " << unsigned(sp->getHeader()->getFrameCounter()) << std::endl;
            std::cout << std::endl;

            std::cout << "-----------------------" << std::endl;
            std::cout << " DATA (up to the first 20 points):" << std::endl;
            std::cout << "-----------------------" << std::endl;

        std::size_t n{20};
        if (numCh < n)
            n = numCh;

        for (std::size_t i(0); i < n; ++i)
                std::cout << "Data[" << i << "] = " << sp->getData(i) << std::endl;

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
                    boost::noncopyable >
                    ("MyTransmitter",bp::init<>())
            .def("setDebug", &MyTransmitter::setDebug)
            .def("getDebug", &MyTransmitter::getDebug)
        ;
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
        printf("Failed to load my custom transmitter module. Import rogue first\n");
    }

    printf("Custom transmitter module loaded\n");
};
