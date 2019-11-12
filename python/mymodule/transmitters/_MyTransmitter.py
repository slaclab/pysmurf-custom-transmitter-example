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

from pysmurf.core.transmitters._BaseTransmitter import BaseTransmitter

class MyTransmitter(BaseTransmitter):
    """
    SMuRF Data MyTransmitter Python Wrapper.
    """
    def __init__(self, name, **kwargs):
        BaseTransmitter.__init__(self, name=name, **kwargs)
        self._transmitter = MyModule.MyTransmitter()

        # Add "Disable" variable
        self.add(pyrogue.LocalVariable(
            name='Debug',
            description='Set the debug mode',
            mode='RW',
            value=False,
            localSet=lambda value: self._transmitter.setDebug(value),
            localGet=self._transmitter.getDebug))

    # Method called by streamConnect, streamTap and streamConnectBiDir to access slave
    def _getStreamSlave(self):
        return self._transmitter

