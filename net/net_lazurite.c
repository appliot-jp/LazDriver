
/********************************************************************/
/*! @brief tx in mac high layer
  @param[in]	*dstAddr	64bit distination address
  @param[in]	*payload	start pointer of payload
  @param[in]	size		size of payload
  @param[in]	addrType	address type
	  type | rx_addr | tx_addr | panid_comp | rx panid | tx_panid
	  -----| --------| --------| ---------- | -------- | --------
	  0 | N | N | 0 | N | N
	  1 | N | N | 1 | Y | N
	  2 | N | Y | 0 | N | Y
	  3 | N | Y | 1 | N | N
	  4 | Y | N | 0 | Y | N
	  5 | Y | N | 1 | N | N
	  6 | Y | Y | 0 | Y | N
	  7 | Y | Y | 1 | N | N
  @param[in]	txCallback	callback at end of tx
  @return    0=STATUS_OK, other = error
  @exception  return NULL
 ********************************************************************/
int mach_tx64(uint8_t *dstAddr, uint8_t *payload, uint16_t size,uint8_t addrType,void txCallback(uint8_t rssi, int16_t status))
{
}

