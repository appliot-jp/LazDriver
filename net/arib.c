
static struct {
	unsigned long start_time;
	unsigned long last_send_time;
	unsigned long total_send_bytes;
} arib = {0,0x80000000,0};


void arib_init(void)
{
	arib.start_time = HAL_millis();
}

void arib_tx_end(uint8_t pages,uint16_t size)
{
}

bool arib_tx_check(uint8_t pages,uint16_t size)
{
	int status;
	uint32_t current_time;
	uint32_t duration;
	// check total send bytes in an hours -- an hours
	current_time = HAL_millis();
	duration = current_time - arib.start_time;
	if(duration > 3600000L)
	{
		arib.total_send_bytes = 0;
		arib.start_time = current_time;
	}
	
	// check total send bytes in an hours -- calcurate total send bytes
	tmp_ttl_byte = arib.total_send_bytes;
	switch(subghz_param.rate)
	{
#define SUBGHZ_HEADER_SIZE	11
	case SUBGHZ_50KBPS:
		tmp_ttl_byte += len + SUBGHZ_HEADER_SIZE;
	case SUBGHZ_100KBPS:
		tmp_ttl_byte += len + SUBGHZ_HEADER_SIZE;
		if(tmp_ttl_byte>45000000)
		{
			msg = SUBGHZ_TTL_SEND_OVR;
			goto error_not_send;
		}
		break;
	default:
		msg = SUBGHZ_SETUP_FAIL;
		goto error_not_send;
		break;
	}
	
	// CHECK ARIB condition -- interval --
	duration = current_time - arib.last_send_time;
	
	if((subghz_param.ch >= 24)&&(subghz_param.ch<=32))
	{
		if(duration < 50)
		{
			HAL_sleep(50-duration);
		}
	}
	

	return status;
}
