#! /usr/bin/ruby
# -*- coding: utf-8; mode: ruby -*-
# Function:
#   Lazurite Sub-GHz/Lazurite Pi Gateway Sample program
#   SerialMonitor.rb
require_relative './LazGem/lib/LazGem'
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

	def test_drviver
		@@laz.init(module_test = 0xff00)
		cmd = `dmesg | tail -n 3`
		p cmd

		#check ch of 100kbps
		packet = @@laz.getSendMode()
		assert_equal 6, packet.fetch("addr_type")
		assert_equal 7, packet.fetch("sense_time")
		assert_equal 3, packet.fetch("tx_retry")
		assert_equal 7, packet.fetch("tx_interval")
		assert_equal 7, packet.fetch("cca_wait")
		assert_equal 100,@@laz.get_bps()
		assert_equal 36,@@laz.get_ch()
		assert_raises (Errno::EINVAL) {@@laz.set_ch(23)}
		assert_equal 24,@@laz.set_ch(24)
		assert_equal 31,@@laz.set_ch(31)
		assert_raises (Errno::EINVAL) {@@laz.set_ch(32)}
		assert_equal 33,@@laz.set_ch(33)
		assert_equal 60,@@laz.set_ch(60)
		assert_raises (Errno::EINVAL) {@@laz.set_ch(61)}
		assert_equal 60,@@laz.get_ch()

		#check ch of 50kbps
		assert_equal 50,@@laz.set_bps(50)
		assert_raises (Errno::EINVAL) {@@laz.set_ch(23)}
		assert_equal 24,@@laz.set_ch(24)
		assert_equal 31,@@laz.set_ch(31)
		assert_equal 32,@@laz.set_ch(32)
		assert_equal 33,@@laz.set_ch(33)
		assert_equal 61,@@laz.set_ch(61)
		assert_raises (Errno::EINVAL) {@@laz.set_ch(62)}
		assert_equal 61,@@laz.get_ch()

		#check bps
		assert_raises (Errno::EINVAL) {@@laz.set_bps(49)}
		assert_equal 50,@@laz.get_bps()
		assert_equal 100,@@laz.set_bps(100)
		assert_equal 100,@@laz.get_bps()
		assert_raises (Errno::EINVAL) {@@laz.set_bps(101)}
		assert_equal 100,@@laz.get_bps()

		#check pwr
		assert_equal 20,@@laz.get_pwr()
		assert_equal 1,@@laz.set_pwr(1)
		assert_equal 1,@@laz.get_pwr()
		assert_raises (Errno::EINVAL) {@@laz.set_pwr(2)}

		#check my panid
		assert_equal 0xabcd,@@laz.get_my_panid()
		assert_equal 0x55aa,@@laz.set_my_panid(0x55aa)
		assert_equal 0x55aa,@@laz.get_my_panid()
		assert_raises (Errno::EINVAL) {@@laz.set_my_panid(0x80000)}

		#check tx panid
		assert_equal 0xabcd,@@laz.get_tx_panid()
		assert_equal 0xaa55,@@laz.set_tx_panid(0xaa55)
		assert_equal 0xaa55,@@laz.get_tx_panid()
		assert_raises (Errno::EINVAL) {@@laz.set_tx_panid(0x80000)}

		#check address
		#assert_equal 0x2301,@@laz.get_my_addr0()
		#assert_equal 0xac4e,@@laz.get_my_addr0()
		#assert_raises (Errno::EFAULT) {@@laz.get_my_addr1()}
		#assert_raises (Errno::EFAULT) {@@laz.get_my_addr2()}
		#assert_raises (Errno::EFAULT) {@@laz.get_my_addr3()}
		assert_equal 0xffff,@@laz.get_tx_addr0()
		assert_equal 0xffff,@@laz.get_tx_addr1()
		assert_equal 0xffff,@@laz.get_tx_addr2()
		assert_equal 0xffff,@@laz.get_tx_addr3()
		assert_equal 0,@@laz.set_tx_addr0(0)
		assert_equal 0,@@laz.set_tx_addr1(0)
		assert_equal 0,@@laz.set_tx_addr2(0)
		assert_equal 0,@@laz.set_tx_addr3(0)

		#check addr_mode
		assert_equal 6,@@laz.get_addr_type()		#check default
		for i in 0..7 do
			assert_equal i,@@laz.set_addr_type(i)
			assert_equal i,@@laz.get_addr_type()
		end
		assert_raises (Errno::EINVAL) {@@laz.set_addr_type(8)}

		#check drv_mode
		assert_equal 0,@@laz.get_drv_mode()		#check default
		assert_equal 0xffff,@@laz.set_drv_mode(0xffff)		#check default
		assert_equal 0xff,@@laz.set_ch(0xff)		#check default
		assert_equal 0xff,@@laz.set_bps(0xff)		#check default
		assert_equal 0xff,@@laz.set_pwr(0xff)		#check default
		assert_equal 0xff,@@laz.set_my_addr0(0xff)		#check default
		assert_equal 0xff,@@laz.set_addr_type(0xff)		#check default
		#assert_equal 0xff,@@laz.set_addr_size(0xff)		#check default

		@@laz.remove()
	end
end

