with open("SR-16.syx", "rb") as f:
    sr_16_syx_b = f.read()

assert len(sr_16_syx_b) == 3543

packed_b = sr_16_syx_b[6:-1]

unpacked_b = b""

while packed_b:
    b, packed_b = packed_b[:8], packed_b[8:]
    r = 0
    for c in b:
        r = (r << 7) | (c & 0x7f)
    unpacked_b += r.to_bytes(7, "big")

assert len(unpacked_b) == 3094

###########################################################################

unpacked = list(unpacked_b)
unpacked[0xC9] = 0x01 # receive drum in, velocity curve 1
unpacked[0xDD] = 0x01 # MIDI program select on
unpacked[0xE3] = 0x01 # Drumset mode manual
unpacked[0xE7] = 0x01 # Note map 00-09
unpacked_b = bytes(unpacked)

assert len(unpacked_b) == 3094

###########################################################################

with open("gm_drumset", "rb") as f:
    gm_drumset_b = f.read()
assert len(gm_drumset_b) == 360

unpacked_gm_b = b"\x00MIDIPLAN" + unpacked_b[0x009:0x4F8] + gm_drumset_b + unpacked_b[0x660:]

assert len(unpacked_gm_b) == 3094

###########################################################################

r = int.from_bytes(unpacked_gm_b, "big")

packed_b = b""

for i in range(3536):
    b = bytes([r & 0x7F])
    packed_b = b + packed_b
    r = r >> 7

packed_b = b"\xF0\x00\x00\x0E\x05\x00" + packed_b + b"\xF7"
assert len(packed_b) == 3543

with open("SR-16-GM.syx", "wb") as f:
    f.write(packed_b)
