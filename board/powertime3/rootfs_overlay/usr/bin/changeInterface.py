#!/usr/bin/python3
"""
# ==============================================
# Name          : changeInterfaces.py
# Author        : Yves Cestele
# Date          : 01.04.2020
# Description   : Modify the Interfaces file
#                 with the new prm set in
#                 argv
#
# Modifications : -
# ==============================================

    Usage:  changeInterface.py <Interface> <IP> (opt)<Netmask> (opt)<Gateway>
    Example changeInterface.py eth1 192.168.46.3 255.255.0.0 192.168.46.1

    If No value are set the following default value are set:

        IP     : 192.168.46.3
        Netmask: 255.255.0.0
        Gateway: 192.168.46.1
"""

# ==============================================
# Imports
# ----------------------------------------------
import sys
import os

# ==============================================
# Defines:
# ----------------------------------------------
INTERFACES_FILE_PATH = "/etc/network/interfaces"
NETWORK_RESTART_COMMAND = "/etc/init.d/S40network restart"

DEFAULT_IP = "192.168.46.10"
DEFAULT_NETMASK = "255.255.0.0"
DEFAULT_GATEWAY = "192.168.46.1"
DEFAULT_INTERFACE = "eth1"


# ==============================================
# Functions
# ----------------------------------------------
def createStringIfaceStatic(interface, ip, netmask, gateway):
    return " " + interface + "\niface " + interface + " inet static\naddress " + ip + "\nnetmask " + netmask + "\ngateway " + gateway + "\n\n"


def checkIpFormat(toCkeck):
    numbers = toCkeck.split('.')
    if not 4 == len(numbers):
        return False

    for number in numbers:
        if not 0 <= int(number) <= 255:
            return False

    return True

def checkInterfaceFormat(tocheck):
    return "eth" in tocheck


# ==============================================
# Main
# ----------------------------------------------

# --------------------------------------
# Set def value to var:

interfaceToAlter = "eth1"
ipAddressToSet = DEFAULT_IP
netmaskToSet = DEFAULT_NETMASK
gatewayToSet = DEFAULT_GATEWAY

# --------------------------------------
# Check args integrity:

argumentList = sys.argv
numberOfArg = len(argumentList)

if 1 >= numberOfArg:
    print("error -- Please enter at least interface name in parameter")
    sys.exit()

if checkInterfaceFormat(argumentList[1]):
    interfaceToAlter = argumentList[1]
else:
    print("error -- Interface format is not correct -> should be 'eth'[xx]");
    sys.exit()

if 3 <= numberOfArg:
    if checkIpFormat(argumentList[2]):
        ipAddressToSet = argumentList[2]
    else:
        print("warning -- IP Address set to " + DEFAULT_IP + " (default) because data was not coherent")
else:
    print("warning -- IP Address set to " + DEFAULT_IP + " (default) because data was specified")

if 4 <= numberOfArg:
    if checkIpFormat(argumentList[3]):
        netmaskToSet = argumentList[3]
    else:
        print("warning -- Netmask set to " + DEFAULT_NETMASK + " (default) because data was not coherent")
else:
    print("warning -- Netmask set to " + DEFAULT_NETMASK + " (default) because data was not specified")

if 5 <= numberOfArg:
    if checkIpFormat(argumentList[4]):
        gatewayToSet = argumentList[4]
    else:
        print("warning -- Gateway set to " + DEFAULT_GATEWAY + " (default) because data was not coherent")
else:
    print("warning -- Gateway set to " + DEFAULT_GATEWAY + " (default) because data was not specified")

# --------------------------------------
# Open and read current Interfaces file

with open(INTERFACES_FILE_PATH, 'r') as content_file:
    content = content_file.read()

interfacesElement = content.split("auto")

# --------------------------------------
# Find and reconfig interface

newList = []
bInterfaceHasBeenFound = False

for element in interfacesElement:
    if interfaceToAlter in element:
        bInterfaceHasBeenFound = True
        newList.append(createStringIfaceStatic(interface=interfaceToAlter, ip=ipAddressToSet, netmask=netmaskToSet,
                                               gateway=gatewayToSet))
    else:
        newList.append(element)

if not bInterfaceHasBeenFound:  #Create it if doesn't exist:
    newList.append(createStringIfaceStatic(interface=interfaceToAlter, ip=ipAddressToSet, netmask=netmaskToSet,
                                           gateway=gatewayToSet))

# --------------------------------------
# Write file
newFile = open(INTERFACES_FILE_PATH, "w")
for line in newList:
    if len(line) > 2:
        newFile.writelines("auto" + line)

newFile.close()

# --------------------------------------
# Restart Interface:
os.system(NETWORK_RESTART_COMMAND)


