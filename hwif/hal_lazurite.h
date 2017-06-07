/* hal_lazurite.h - header flle for Lazurite IDE
 *
 * Copyright (c) 2015  Communication Technology Inc.,
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
 * <http://www.gnu.org/licenses/>.
 */


#ifndef _HAL_LAZURITE_H_
#define _HAL_LAZURITE_H_


#define HAL_STATUS_OK             0
#define HAL_STATUS_ERROR_PARAM   -1
#define HAL_STATUS_ERROR_STATE   -2
#define HAL_STATUS_ERROR_TIMEOUT -3

#define HAL_GPIO_CSB    6
#define HAL_GPIO_RESETN 7
#define HAL_GPIO_DMON   5
#define HAL_GPIO_SINTN  27
#define BP3596A_SINTN_IRQNUM	3

#endif  //_HAL_LAZURIE_H_
