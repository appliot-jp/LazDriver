typedef struct {
	struct {
		BUFFER buf;
		void (*callback)(uint8_t *buf, int16_t status, uint8_t rssi);
	}tx;
	struct {
		BUFFER buf;
		void (*callback)(uint8_t *buf, int16_t status, uint8_t rssi);
	}rx;
	MAC_PARAM *macinfo;
}SUBGHZ_APP;


