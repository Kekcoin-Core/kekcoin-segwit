#!/usr/bin/env python2

import array
import binascii
import zmq
import struct

port = 25555

zmqContext = zmq.Context()
zmqSubSocket = zmqContext.socket(zmq.SUB)
zmqSubSocket.setsockopt(zmq.SUBSCRIBE, "hashblock")
zmqSubSocket.setsockopt(zmq.SUBSCRIBE, "hashtx")
zmqSubSocket.setsockopt(zmq.SUBSCRIBE, "rawblock")
zmqSubSocket.setsockopt(zmq.SUBSCRIBE, "rawtx")
zmqSubSocket.connect("tcp://127.0.0.1:%i" % port)

try:
    while True:
        msg = zmqSubSocket.recv_multipart()
        topic = str(msg[0])
        body = msg[1]
        sequence = "Unknown";
        if len(msg[-1]) == 4:
          msgSequence = struct.unpack('<I', msg[-1])[-1]
          sequence = str(msgSequence)
        if topic == "hashblock":
            print '- HASH BLOCK ('+sequence+') -'
            print binascii.hexlify(body)
        elif topic == "hashtx":
            print '- HASH TX  ('+sequence+') -'
            print binascii.hexlify(body)
        elif topic == "rawblock":
            print '- RAW BLOCK HEADER ('+sequence+') -'
            print binascii.hexlify(body[:80])
        elif topic == "rawtx":
            print '- RAW TX ('+sequence+') -'
            print binascii.hexlify(body)

except KeyboardInterrupt:
    zmqContext.destroy()
