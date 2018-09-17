/*
   BAREOS® - Backup Archiving REcovery Open Sourced

   Copyright (C) 2018-2018 Bareos GmbH & Co. KG

   This program is Free Software; you can redistribute it and/or
   modify it under the terms of version three of the GNU Affero General Public
   License as published by the Free Software Foundation and included
   in the file LICENSE.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.
*/

#ifndef BAREOS_LIB_TLS_CONF_BASE_H_
#define BAREOS_LIB_TLS_CONF_BASE_H_

struct PskCredentials;

class TlsConfigBase {
public:
   bool enabled;  /*!< Enable TLS */
   bool required; /*!< Require TLS */

   virtual uint32_t GetPolicy() const = 0;

   virtual bool GetAuthenticate() const { return false; }
   virtual bool GetVerifyPeer() const { return false; }
   virtual std::vector<std::string> AllowedCertificateCommonNames() const { return std::vector<std::string>(); }

   typedef enum {
      BNET_TLS_NONE = 0,            /*!< No TLS configured */
      BNET_TLS_ENABLED = 1,         /*!< TLS with certificates is allowed but not required on my end */
      BNET_TLS_REQUIRED = 2,        /*!< TLS with certificates is required */
      BNET_TLS_AUTO = 4,            /*!< TLS with certificates is required */
      BNET_TLS_DENY = 0xFF          /*!< TLS connection not allowed */
   } Policy_e;

protected:
   TlsConfigBase() : enabled(false), required(false) {}
   virtual ~TlsConfigBase() {}
};

#endif /* BAREOS_LIB_TLS_CONF_BASE_H_ */
