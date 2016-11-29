/* app_lazurite.c - MAC for lazurite
 *
 * Copyright (c) 2015  Lapis Semiconductor Co.,Ltd
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>
 */
 

SUBGHZ_APP app;
static struct {

int rf_init()
{
	int status = STATUS_OK;
	memset(&app,0,sizeof(SUBGHZ_APP));
	app.mac = mac_init();
	if(app.mac == NULL) status = -1;
	return status;
}

int rf_send(uint8_t ch, uint16_t mypanid, uint8_t rate, uint8_t pwr)
{
}
