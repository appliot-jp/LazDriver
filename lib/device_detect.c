#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

static const char* dev_name = "/dev/i2c-1";


/*! I2Cスレーブデバイスからデータを読み込む.
 * @param[in] dev_addr デバイスアドレス.
 * @param[in] reg_addr レジスタアドレス.
 * @param[out] data 読み込むデータの格納場所を指すポインタ.
 * @param[in] length 読み込むデータの長さ.
 */
int8_t i2c_write_read(
    uint8_t dev_addr, uint8_t* wdata, uint16_t wlen, uint8_t* rdata, uint16_t rlen) {
  /* I2Cデバイスをオープンする. */
  int32_t fd = open(dev_name, O_RDWR);
  if (fd == -1) {
    fprintf(stderr, "i2c_read: failed to open: %s\n", strerror(errno));
    return -1;
  }

  /* I2C-Readメッセージを作成する. */
  struct i2c_msg messages[] = {
      { dev_addr, 0, wlen, wdata },         /* レジスタアドレスをセット. */
      { dev_addr, I2C_M_RD, rlen, rdata },  /* dataにlengthバイト読み込む. */
  };
  struct i2c_rdwr_ioctl_data ioctl_data = { messages, 2 };

  /* I2C-Readを行う. */
  if (ioctl(fd, I2C_RDWR, &ioctl_data) != 2) {
    fprintf(stderr, "i2c_read: failed to ioctl: %s\n", strerror(errno));
    close(fd);
    return -1;
  }

  close(fd);
  return 0;
}

const uint8_t rohm_mac_address[] = {0x00,0x1d,0x12,0x90,0x00,0x03};
const uint8_t lapis_mac_address[] = {0x00,0x1d,0x12,0xd0};
const uint8_t allf[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
int main(void) {
	uint8_t wdata[2];
	uint8_t mac_address[8];
	int status;
	wdata[0] = 0x20;
	status = i2c_write_read(0x50,wdata,1,mac_address,8);
	if( status == -1) {
		return status;
	}
	if(memcmp(mac_address,rohm_mac_address,sizeof(rohm_mac_address)) == 0) {
		printf("BP3596A\n");
	} else if(memcmp(mac_address,allf,sizeof(allf)) == 0) {
		wdata[0] = 0x00;
		wdata[1] = 0x20;
		status = i2c_write_read(0x50,wdata,2,mac_address,8);
		if(memcmp(mac_address,lapis_mac_address,sizeof(lapis_mac_address)) == 0) {
			uint8_t device;
			wdata[1] = 0xA0;
			status = i2c_write_read(0x50,wdata,2,&device,1);
			if(device == 0x0A) {
				printf("MK74040\n");
			} else {
				fprintf(stderr, "unsupported device %02x %02x %02x %02x  %02x %02x %02x %02x\n",
						mac_address[7],
						mac_address[6],
						mac_address[5],
						mac_address[4],
						mac_address[3],
						mac_address[2],
						mac_address[1],
						mac_address[0]
						);
			}
		}
	}
	return 0;
}
