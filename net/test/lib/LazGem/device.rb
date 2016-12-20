# -*- coding: utf-8; mode: ruby -*-
#
# Function:
#   Lazurite Pi Gateway SubGHz library

#################################################################
######
######	Do not forget to change path of libraries
######			require and insmod
######
################################################################
class LazGem::Device
	##
	# func   : Read the data from the receiving pipe
	# input  : Receive pipe fp
	# return : Receive data
	##

	@@device_rd=nil
	@@device_wr=nil

	def init(module_test=0x0000)
		cmd = "sudo insmod /home/pi/driver/LazDriver/net/lib/lazdriver.ko module_test="+module_test.to_s
		p cmd
		result = system(cmd)
		lzgw_dev = "/dev/lzgw"
		sleep(0.1)
		result = system("sudo chmod 777 "+lzgw_dev)
#		p result
		sleep(0.1)
		@@device_rd = open(lzgw_dev,"rb")
		@@device_wr = open(lzgw_dev,"wb")
		@@device_wr.sync = true
		@@device_rd.sync = true
		result = system("tail -n -4 /var/log/messages")
		print("\n")
#		p result
		print("Success to load SubGHz module\n")
	end

# LAZURITE.close()
# function
#	close device deriver
# parameter
#	none
# return
#	none
	def remove()
		begin
			@@device_rd.close
		rescue Exception => e
			p e
		end
		begin
		@@device_wr.close
		rescue Exception => e
			p e
		end
		@@devie_rd = nil
		@@device_wr = nil
		cmd = "sudo rmmod lazdriver"
		system(cmd)
		p cmd
	end

	def available()
		size = 2
		len = @@device_rd.read(size)
    	if ((len == "") || (len == nil)) then # read result is empty
      		return 0
		end
    	size =  len.unpack("S*")[0]
		return size
	end

	def read()
		size = 2
		len = @@device_rd.read(size)
    	if ((len == "") || (len == nil)) then # read result is empty
      		return 0
    	end
    	size =  len.unpack("S*")[0]

    	# The received data is read
    	raw = @@device_rd.read(size)
    	if ((raw == "") || (raw == nil)) then # read result is empty
      		return -1
		end
		
		len = raw.length
		header = raw.unpack("S*")[0]

		rx_addr_type = (header>>14) & 0x03
		frame_ver = (header >> 12) & 0x03
		tx_addr_type = (header >> 10) & 0x03
		ielist = (header >> 9) & 0x01
		seq_comp = (header >> 8) & 0x01
		panid_comp = (header >> 6) & 0x01
		ack_req = (header >> 5) & 0x01
		pending = (header >> 4) & 0x01
		sec_enb = (header >> 3) & 0x01
		frame_type = (header >> 0) & 0x07

		offset = 2

		if seq_comp == 0 then
			seq_num = raw[offset..offset+1].unpack("C")[0]
			offset = offset + 1
		end

		if rx_addr_type == 0 && tx_addr_type == 0 && panid_comp == 0 then
			addr_type = 0
			rx_panid = nil
			tx_panid = nil
		elsif rx_addr_type == 0 && tx_addr_type == 0 && panid_comp != 0 then
			addr_type = 1
			rx_panid = raw[offset..offset+2].unpack("S*")[0]
			offset = offset + 2
			tx_panid = nil
		elsif rx_addr_type == 0 && tx_addr_type != 0 && panid_comp == 0 then
			addr_type = 2
			rx_panid = nil
			tx_panid = raw[offset..offset+2].unpack("S*")[0]
			offset = offset + 2
		elsif rx_addr_type == 0 && tx_addr_type != 0 && panid_comp != 0 then
			addr_type = 3
			rx_panid = nil
			tx_panid = nil
		elsif rx_addr_type != 0 && tx_addr_type == 0 && panid_comp == 0 then
			addr_type = 4
			rx_panid = raw[offset..offset+2].unpack("S*")[0]
			offset = offset + 2
			tx_panid = nil
		elsif rx_addr_type != 0 && tx_addr_type == 0 && panid_comp != 0 then
			addr_type = 5
			rx_panid = nil
			tx_panid = nil
		elsif rx_addr_type != 0 && tx_addr_type != 0 && panid_comp == 0 then
			addr_type = 6
			rx_panid = raw[offset..offset+2].unpack("S*")[0]
			offset = offset + 2
			tx_panid = nil
		elsif rx_addr_type != 0 && tx_addr_type != 0 && panid_comp != 0 then
			addr_type = 7
			rx_panid = nil
			tx_panid = nil
		end

		if rx_addr_type == 1 then
			rx_addr = raw[offset..offset+1].unpack("C")[0]
			offset = offset+1
		elsif rx_addr_type == 2 then
			rx_addr = raw[offset..offset+2].unpack("S*")[0]
			offset = offset+2
		else
			rx_addr = raw[offset..offset+8].unpack("H*")[0]
			offset = offset+8
		end

		if tx_addr_type == 1 then
			tx_addr = raw[offset..offset+1].unpack("C")[0]
			offset = offset+1
		elsif tx_addr_type == 2 then
			tx_addr = raw[offset..offset+2].unpack("S")[0]
			offset = offset+2
		else
			tx_addr = raw[offset..offset+8].unpack("H*")[0]
			offset = offset+8
		end

		payload = raw[offset..len-1].unpack("Z*")[0]

		rcv = Hash.new()

		rcv["header"] = header
		rcv["rx_addr_type"] = rx_addr_type
		rcv["frame_ver"] = frame_ver
		rcv["tx_addr_type"] = tx_addr_type
		rcv["ielist"] = ielist
		rcv["seq_comp"] = seq_comp
		rcv["panid_comp"] = panid_comp
		rcv["ack_req"] = ack_req
		rcv["pending"] = pending
		rcv["sec_enb"] = sec_enb
		rcv["frame_type"] = frame_type
		rcv["addr_type"] = addr_type
		rcv["rx_panid"] = rx_panid
		rcv["tx_panid"] = tx_panid
		rcv["rx_addr"] = rx_addr
		rcv["tx_addr"] = tx_addr
		rcv["seq_num"] = seq_num
		rcv["payload"] = payload
		sec,nsec = get_rx_time()
		rcv["sec"]=sec
		rcv["nsec"]=nsec
		rcv["rssi"]=get_rx_rssi()
			
    	return rcv
	end
	def send(panid,addr,payload)
		set_tx_panid(panid)
		set_tx_addr0(addr)
		@@device_wr.write(payload)
		sleep 0.001
	end
end
