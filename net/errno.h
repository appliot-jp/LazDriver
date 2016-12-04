/* error.h
 *
 * Copyright (c) 2015  Lapis Semiconductor Co.,Ltd.
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

#ifndef	_ERROR_H_
#define _ERROR_H_

#define STATUS_OK	0

#define EIO			5			// hardware error
#define ENOMEM		12			// data size error
#define EFAULT		14			// bad pointer
#define EBUSY		16			// resource busy(CCA)
#define EINVAL		22			// invalid parameters
#define EFBIG		27			// File too large
#define ETIMEDOUT	110			// no ack
#endif
