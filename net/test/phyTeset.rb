#! /usr/bin/ruby
# -*- coding: utf-8; mode: ruby -*-
# Function:
#   Lazurite Sub-GHz/Lazurite Pi Gateway Sample program
#   SerialMonitor.rb
require_relative './lib/LazGem'
require 'minitest'
require 'minitest/autorun'
require 'minitest/reporters'

# Halt process when CTRL+C is pushed.
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

MiniTest::Reporters.use!

class TestClass < Minitest::Test
	def setup
		@@laz = LazGem::Device.new
		begin
			p "device close"
			@@laz.remove()
		rescue
		end
	end

	def test_subghz_setup
##		@@laz.init(module_test = 0x3000)
#		@@laz.init(module_test = 0xFF00)
#		@@laz.begin(30,0xabcd,100,20)
#		@@laz.send(0xabcd,0x1234,"hello")
##		@@laz.rxEnable()
#       sleep(3)
#		@@laz.remove()

#		@@laz.init(module_test = 0x3000) #PHY/MACL
		@@laz.init(module_test = 0x1000) #PHY 
#		@@laz.init(module_test = 0x0000)
#		@@laz.init(module_test = 0xFF00)
		@@laz.begin(36,0xabcd,100,20)
        for num in 1..10 do
		    @@laz.send(0xabcd,0x5f6e,"hello")
            sleep(1)
        end
#		@@laz.rxEnable()
		@@laz.remove()
	end
end

