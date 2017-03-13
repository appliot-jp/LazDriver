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

	def test_phy
		@@laz.init(module_test = 0x3000) #MACH:0x4000, MACH:0x2000, PHY:0x1000
		printf("%016x\n",@@laz.getMyAddr64())
		@@laz.begin(24,0xabcd,100,20)
		@@laz.send64(0xabcd,0x0011223344556677,"LAPIS Lazurite RF system")
		@@laz.send64(0xfffe,0x8899aabbccddeeff,"LAPIS Lazurite RF system")
		@@laz.remove()
	end
end

