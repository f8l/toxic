/*  device.h
 *
 *
 *  Copyright (C) 2014 Toxic All Rights Reserved.
 *
 *  This file is part of Toxic.
 *
 *  Toxic is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Toxic is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Toxic.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*
 * You can have multiple sources (Input devices) but only one output device.
 * Pass buffers to output device via write(); 
 * Read from running input device(s) via select()/callback combo.
 */

#ifndef _device_h
#define _device_h

#define MAX_DEVICES 32
#include <inttypes.h>
#include "windows.h"

#define _True 1
#define _False 0

typedef enum DeviceType {
    input,
    output,
} DeviceType;

typedef enum DeviceError {
    de_None,
    de_InternalError = -1,
    de_InvalidSelection = -2,
    de_FailedStart = -3,
    de_Busy = -4,
    de_AllDevicesBusy = -5,
    de_DeviceNotActive = -6,
    de_BufferError = -7,
    de_AlError = -8,
} DeviceError;

typedef void (*DataHandleCallback) (const int16_t*, uint32_t size, void* data);


DeviceError init_devices(ToxAv* av);
DeviceError terminate_devices();

/* Callback handles ready data from INPUT device */
DeviceError register_device_callback(int32_t call_idx, uint32_t device_idx, DataHandleCallback callback, void* data, _Bool enable_VAD);
void* get_device_callback_data(uint32_t device_idx);

/* toggle device mute */
DeviceError device_mute(DeviceType type, uint32_t device_idx);

DeviceError device_set_VAD_treshold(uint32_t device_idx, float value);

DeviceError set_primary_device(DeviceType type, int32_t selection);
DeviceError open_primary_device(DeviceType type, uint32_t* device_idx);
/* Start device */
DeviceError open_device(DeviceType type, int32_t selection, uint32_t* device_idx);
/* Stop device */
DeviceError close_device(DeviceType type, uint32_t device_idx);

/* Write data to device */
DeviceError write_out(uint32_t device_idx, int16_t* data, uint32_t lenght, uint8_t channels);

void print_devices(ToxWindow* self, DeviceType type);

DeviceError selection_valid(DeviceType type, int32_t selection);
#endif /* _device_h */