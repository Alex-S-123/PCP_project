"""
import matplotlib.pyplot as plt
import numpy as np
from skyfield.api import load, Topos, EarthSatellite

TLE_FILE = "https://celestrak.org/NORAD/elements/gp.php?GROUP=active&FORMAT=tle" # DB file to download

SAT_NAME = "ISS (ZARYA)"
satellites = load.tle(TLE_FILE)
location = Topos('55.9494 N', '37.5019 E')

sats = {sat.name: sat for sat in satellites.values()}
satellite = sats[SAT_NAME]
tsm = []
ts = load.timescale()
#время по Гринвичу
for j in range(8, 9):
    for i in range(3600):
        a = ts.tt(2025, 4, 12, j, i // 60, i%60)
        tsm.append(a)
c = 0
alts, azs = [], []
for t in tsm:
    difference = satellite - location
    topocentric = difference.at(t)

    alt, az, distance = topocentric.altaz()

    if alt.degrees > 30:
        #print(az.degrees, alt.degrees, t.utc)
        alts.append(alt.degrees)
        azs.append(az.degrees)

gralt = np.gradient(alts)
plt.plot(gralt)
plt.show()
graz = np.gradient(azs)
plt.plot(graz)
plt.show()
"""
"""
difference = satellite - location
topocentric = difference.at(ts.now())

alt, az, distance = topocentric.altaz()

print(alt, az, ts.now().utc)

#для проверки точности, при сбое удалить файл gp.php
"""

import socket

sock = socket.socket()

host = "192.168.1.1"  # ESP32 IP in local network
port = 80  # ESP32 Server Port

sock.connect((host, port))

while True:
    message = str(input())
    if message == "0":
        sock.close()
        exit(0)
    sock.send(message.encode())


