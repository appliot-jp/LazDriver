#! /usr/bin/ruby
# -*- coding: utf-8; mode: ruby -*-
# Function:
#   Lazurite Sub-GHz/Lazurite Pi Gateway Sample program
#   SerialMonitor.rb
require_relative './lib/LazGem'

laz = LazGem::Device.new

# Halt process when CTRL+C is pushed.
finish_flag=0
Signal.trap(:INT){
	finish_flag=1
}
# open device deriver
# 
# LAZURITE.open(ch=36,panid=0xabcd,pwr=20,rate=100),mode=2)
# parameter
#  ch:		frequency 24-61. 36 is in default
#  panid:	pan id
#  pwr:		tx power
#  rate:	bit rate  50 or 100
#  pwr:		tx power  1 or 20
#  mode:	must be 2
laz.init()
laz.begin(24,0xABCD,100,20)
print(sprintf("myAddress=0x%04x\n",laz.getMyAddr64()))
laz.rxEnable()

# printing header of receiving log
print(sprintf("time\t\t\t\t\t[ns]\trxPanid\trxAddr\ttxAddr\trssi\tpayload\n"))
print(sprintf("------------------------------------------------------------------------------------------\n"))

# main routine
while finish_flag == 0 do
	if laz.available() <= 0
		next
	end
	rcv = laz.read()
	# printing data
	p rcv
	'''
	print(sprintf("%s\t%d\t%04x\t%04x\t%04x\t%d\t%s\n",
		Time.at(rcv["sec"]),
		rcv["nsec"],
		rcv["rx_panid"],
		rcv["rx_addr"],
		rcv["tx_addr"],
		rcv["rssi"],
		rcv["payload"]));
	'''
end

# finishing process
laz.remove()


