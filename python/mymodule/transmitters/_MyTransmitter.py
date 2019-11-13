#!/usr/bin/env python
#-----------------------------------------------------------------------------
# Title      : PySMuRF Data Base Transmitter
#-----------------------------------------------------------------------------
# File       : __init__.py
# Created    : 2019-09-30
#-----------------------------------------------------------------------------
# Description:
#    SMuRF Data MyTransmitter Python Package
#-----------------------------------------------------------------------------
# This file is part of the smurf software platform. It is subject to
# the license terms in the LICENSE.txt file found in the top-level directory
# of this distribution and at:
#    https://confluence.slac.stanford.edu/display/ppareg/LICENSE.html.
# No part of the smurf software platform, including this file, may be
# copied, modified, propagated, or distributed except according to the terms
# contained in the LICENSE.txt file.
#-----------------------------------------------------------------------------

import pyrogue
import smurf
import MyModule

class MyTransmitter(pyrogue.Device):
    """
    SMuRF Data MyTransmitter Python Wrapper.
    """
    def __init__(self, name, **kwargs):
        pyrogue.Device.__init__(self, name=name, description='SMuRF Data CustomTransmitter', **kwargs)
        self._transmitter = MyModule.MyTransmitter()

        # Add "Disable" variable
        self.add(pyrogue.LocalVariable(
            name='Disable',
            description='Disable the processing block. Data will just pass thorough to the next slave.',
            mode='RW',
            value=False,
            localSet=lambda value: self._transmitter.setDisable(value),
            localGet=self._transmitter.getDisable))

        # Add the dropped packet counter variable
        self.add(pyrogue.LocalVariable(
            name='PktDropCnt',
            description='Number of dropped packets',
            mode='RO',
            value=0,
            pollInterval=1,
            localGet=self._transmitter.getPktDropCnt))

        # Command to clear all the counters
        self.add(pyrogue.LocalCommand(
            name='clearCnt',
            description='Clear all counters',
            function=self._transmitter.clearCnt))

        # Add a variable for the debugData flag
        self.add(pyrogue.LocalVariable(
            name='DebugData',
            description='Set the debug mode, for the data',
            mode='RW',
            value=False,
            localSet=lambda value: self._transmitter.setDebugData(value),
            localGet=self._transmitter.getDebugData))

        # Add a variable for the debugMeta flag
        self.add(pyrogue.LocalVariable(
            name='DebugMeta',
            description='Set the debug mode, for the metadata',
            mode='RW',
            value=False,
            localSet=lambda value: self._transmitter.setDebugMeta(value),
            localGet=self._transmitter.getDebugMeta))

    def getDataChannel(self):
        return self._transmitter.getDataChannel()

    def getMetaChannel(self):
        return self._transmitter.getMetaChannel()

