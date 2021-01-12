#include <iostream>
#include <iomanip>
#include "smurf/core/transmitters/BaseTransmitter.h"

namespace bp = boost::python;
namespace sct = smurf::core::transmitters;

// Custom transmitter class
class MyTransmitter : public sct::BaseTransmitter
{
public:
    // Custom class constructor and destructor
    MyTransmitter() : sct::BaseTransmitter(), debugData(false), debugMeta(false) {};
    ~MyTransmitter() {};

    // This is the virtual method defined in 'BaseTransmitter' which is call whenever a
    // new SMuRF packet is ready.
    void dataTransmit(SmurfPacketROPtr sp)
    {
        // If the debug flag is enabled, print part of the SMuRF Packet
        if (debugData)
        {
            std::size_t numCh      { sp->getHeader()->getNumberChannels() };
            uint64_t    epics_time { sp->getHeader()->getCounter2()       };

            std::cout << "=====================================" << std::endl;
            std::cout << "Packet received" << std::endl;
            std::cout << "=====================================" << std::endl;
            std::cout << std::endl;

            std::cout << "-----------------------" << std::endl;
            std::cout << " HEADER:" << std::endl;
            std::cout << "-----------------------" << std::endl;
            std::cout << "Version                = " << unsigned(sp->getHeader()->getVersion())             << std::endl;
            std::cout << "Crate ID               = " << unsigned(sp->getHeader()->getCrateID())             << std::endl;
            std::cout << "Slot number            = " << unsigned(sp->getHeader()->getSlotNumber())          << std::endl;
            std::cout << "Timing configuration   = " << unsigned(sp->getHeader()->getTimingConfiguration()) << std::endl;
            std::cout << "Number of channels     = " << unsigned(sp->getHeader()->getNumberChannels())      << std::endl;
            std::cout << "Unix time              = " << sp->getHeader()->getUnixTime()                      << std::endl;
            std::cout << "Flux ramp increment    = " << unsigned(sp->getHeader()->getFluxRampIncrement())   << std::endl;
            std::cout << "Flux ramp offset       = " << unsigned(sp->getHeader()->getFluxRampOffset())      << std::endl;
            std::cout << "Counter 0              = " << unsigned(sp->getHeader()->getCounter0())            << std::endl;
            std::cout << "Counter 1              = " << unsigned(sp->getHeader()->getCounter1())            << std::endl;
            std::cout << "Counter 2 (EPICS time) = 0x" \
                                                     << std::hex << std::setfill('0') << std::setw(8) \
                                                     << epics_time \
                                                     << std::dec                                            << std::endl;
            std::cout << "    (to UNIX time)     = " << epicsTime2UnixTime(epics_time)                      << std::endl;
            std::cout << "Average reset bits     = 0x" \
                                                     << std::hex << std::setfill('0') << std::setw(4) \
                                                     << unsigned(sp->getHeader()->getAveragingResetBits()) \
                                                     << std::dec                                            << std::endl;
            std::cout << "Frame counter          = " << unsigned(sp->getHeader()->getFrameCounter())        << std::endl;
            std::cout << "TES relay settings     = " << unsigned(sp->getHeader()->getTESRelaySetting())     << std::endl;
            std::cout << "External time clock    = " << sp->getHeader()->getExternalTimeClock()             << std::endl;
            std::cout << "Control field          = " << unsigned(sp->getHeader()->getControlField())        << std::endl;
            std::cout << "Test parameters        = " << unsigned(sp->getHeader()->getTestParameters())      << std::endl;
            std::cout << "Number of rows         = " << unsigned(sp->getHeader()->getNumberRows())          << std::endl;
            std::cout << "Number of row reported = " << unsigned(sp->getHeader()->getNumberRowsReported())  << std::endl;
            std::cout << "Row length             = " << unsigned(sp->getHeader()->getRowLength())           << std::endl;
            std::cout << "Data rate              = " << unsigned(sp->getHeader()->getDataRate())            << std::endl;
            std::cout << "TES Bias values:" << std::endl;
            for (std::size_t i{0}; i < 16; ++i)
                std::cout << sp->getHeader()->getTESBias(i) << ", ";
            std::cout << std::endl;

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

    // This is the virtual method defined in 'BaseTransmitter' which is call whenever
    // new metadata is ready.
    void metaTransmit(std::string cfg)
    {
        // If the debug flag is enabled, print the metadata
        if (debugMeta)
        {
            std::cout << "=====================================" << std::endl;
            std::cout << "Metadata received" << std::endl;
            std::cout << "=====================================" << std::endl;
            std::cout << cfg << std::endl;
            std::cout << "=====================================" << std::endl;
        }
    }

    // Set/Get the debug flags
    void       setDebugData(bool d) { debugData = d;    };
    void       setDebugMeta(bool d) { debugMeta = d;    };
    const bool getDebugData()       { return debugData; };
    const bool getDebugMeta()       { return debugMeta; };

    static void setup_python()
    {
        bp::class_< MyTransmitter,
                    std::shared_ptr<MyTransmitter>,
                    boost::noncopyable >
                    ("MyTransmitter",bp::init<>())
            .def("setDisable",     &MyTransmitter::setDisable)
            .def("getDisable",     &MyTransmitter::getDisable)
            .def("setDebugData",   &MyTransmitter::setDebugData)
            .def("getDebugData",   &MyTransmitter::getDebugData)
            .def("setDebugMeta",   &MyTransmitter::setDebugMeta)
            .def("getDebugMeta",   &MyTransmitter::getDebugMeta)
            .def("clearCnt",       &MyTransmitter::clearCnt)
            .def("getDataDropCnt", &MyTransmitter::getDataDropCnt)
            .def("getMetaDropCnt", &MyTransmitter::getMetaDropCnt)
            .def("getDataChannel", &MyTransmitter::getDataChannel)
            .def("getMetaChannel", &MyTransmitter::getMetaChannel)
        ;
    };

private:
    bool debugData; // Debug flag, for data
    bool debugMeta; // Debug flag, for metadata

    // Convert the EPICS time to UNIX time
    uint64_t epicsTime2UnixTime(const uint64_t& epics_time)
    {
        // The EPICS time word contains 'seconds' in the higher 32-bit word, and 'nanoseconds' in the lower 32-bit word
        union
        {
            uint64_t u64;
            struct
            {
                uint32_t ns;
                uint32_t s;
            };
        } et { .u64 = epics_time };
        // Convert the EPICS time to nanoseconds, and adjust it to UNIX time.
        // The EPICS epoch is 00:00:00 Jan 1, 1990 UTC, which correspond to 631152000 seconds in UNIX epoch time.
        return( (static_cast<uint64_t>(et.s) + 631152000ul)*1000000000ul + static_cast<uint64_t>(et.ns) );
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
        printf("Failed to load my custom transmitter module. Import rogue first\n");
    }

    printf("Custom transmitter module loaded\n");
};
