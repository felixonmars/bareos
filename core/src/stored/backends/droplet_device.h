/*
   BAREOS® - Backup Archiving REcovery Open Sourced

   Copyright (C) 2014-2017 Planets Communications B.V.
   Copyright (C) 2014-2014 Bareos GmbH & Co. KG

   This program is Free Software; you can redistribute it and/or
   modify it under the terms of version three of the GNU Affero General Public
   License as published by the Free Software Foundation, which is
   listed in the file LICENSE.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.
*/
/*
 * Object Storage API device abstraction.
 *
 * Marco van Wieringen, February 2014
 */

#ifndef BAREOS_STORED_BACKENDS_DROPLET_DEVICE_H_
#define BAREOS_STORED_BACKENDS_DROPLET_DEVICE_H_

#include <droplet.h>
#include <droplet/vfs.h>

namespace storagedaemon {

class droplet_device: public chunked_device {
private:
   /*
    * Private Members
    */
   char *configstring_;
   const char *profile_;
   const char *location_;
   const char *canned_acl_;
   const char *storage_class_;
   const char *bucketname_;
   dpl_ctx_t *ctx_;
   dpl_sysmd_t sysmd_;

   /*
    * Private Methods
    */
   bool initialize();

   /*
    * Interface from chunked_device
    */
   bool FlushRemoteChunk(chunk_io_request *request);
   bool ReadRemoteChunk(chunk_io_request *request);
   ssize_t chunked_remote_volume_size();
   bool TruncateRemoteChunkedVolume(DeviceControlRecord *dcr);

public:
   /*
    * Public Methods
    */
   droplet_device();
   ~droplet_device();

   /*
    * Interface from Device
    */
   int d_close(int fd);
   int d_open(const char *pathname, int flags, int mode);
   int d_ioctl(int fd, ioctl_req_t request, char *mt = NULL);
   boffset_t d_lseek(DeviceControlRecord *dcr, boffset_t offset, int whence);
   ssize_t d_read(int fd, void *buffer, size_t count);
   ssize_t d_write(int fd, const void *buffer, size_t count);
   bool d_truncate(DeviceControlRecord *dcr);
};
} /* namespace storagedaemon */
#endif /* OBJECTSTORE_DEVICE_H */
