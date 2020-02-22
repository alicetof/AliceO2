// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// @file   CmpDataFormat.h
/// @author Roberto Preghenella
/// @since  2019-12-18
/// @brief  TOF compressed data format

#ifndef O2_TOF_COMPRESSEDDATAFORMAT
#define O2_TOF_COMPRESSEDDATAFORMAT

#include <cstdint>

namespace o2
{
namespace tof
{
namespace compressed
{

struct Word_t {
  uint32_t undefined : 31;
  uint32_t wordType : 1;
};

struct CrateHeader_t {
  uint32_t bunchID : 12;
  uint32_t slotEnableMask : 11;
  uint32_t undefined : 1;
  uint32_t drmID : 7;
  uint32_t mustBeOne : 1;
};

struct CrateOrbit_t {
  uint32_t orbitID : 32;
};

struct FrameHeader_t {
  uint32_t numberOfHits : 16;
  uint32_t frameID : 8;
  uint32_t trmID : 4;
  uint32_t deltaBC : 3;
  uint32_t mustBeZero : 1;
};

struct PackedHit_t {
  uint32_t tot : 11;
  uint32_t time : 13;
  uint32_t channel : 3;
  uint32_t tdcID : 4;
  uint32_t chain : 1;
};

struct CrateTrailer_t {
  uint32_t numberOfDiagnostics : 4;
  uint32_t eventCounter : 12;
  uint32_t undefined : 15;
  uint32_t mustBeOne : 1;
};

struct Diagnostic_t {
  uint32_t slotID : 4;
  uint32_t faultBits : 28;
};

/** union **/

union Union_t {
  uint32_t data;
  Word_t word;
  CrateHeader_t crateHeader;
  CrateOrbit_t crateOrbit;
  FrameHeader_t frameHeader;
  PackedHit_t packedHit;
  CrateTrailer_t crateTrailer;
};

} // namespace compressed

namespace diagnostic
{

/** DRM diagnostic bits, 12 bits [4-15] **/
enum EDRMDiagnostic_t {
  DRM_HEADER_MISSING = 1 << 4, // start from BIT(4)
  DRM_TRAILER_MISSING = 1 << 5,
  DRM_FEEID_MISMATCH = 1 << 6,
  DRM_ORBIT_MISMATCH = 1 << 7,
  DRM_CRC_MISMATCH = 1 << 8,
  DRM_ENAPARTMASK_DIFFER = 1 << 9,
  DRM_CLOCKSTATUS_WRONG = 1 << 10,
  DRM_FAULTSLOTMASK_NOTZERO = 1 << 11,
  DRM_READOUTTIMEOUT_NOTZERO = 1 << 12,
  DRM_MAXDIAGNOSTIC_BIT = 1 << 16 // end before BIT(16)
};

/** LTM diagnostic bits **/

/** TRM diagnostic bits, 12 bits [4-15] **/
enum ETRMDiagnostic_t {
  TRM_HEADER_MISSING = 1 << 4, // start from BIT(4)
  TRM_TRAILER_MISSING = 1 << 5,
  TRM_CRC_MISMATCH = 1 << 6,
  TRM_HEADER_UNEXPECTED = 1 << 7,
  TRM_EVENTCNT_MISMATCH = 1 << 8,
  TRM_EMPTYBIT_NOTZERO = 1 << 9,
  TRM_LBIT_NOTZERO = 1 << 10,
  TRM_FAULTSLOTBIT_NOTZERO = 1 << 11,
  TRM_MAXDIAGNOSTIC_BIT = 1 << 16 // end before BIT(16)
};

/** TRM Chain diagnostic bits, 8 bits [16-23] chainA [24-31] chainB **/
enum ETRMChainDiagnostic_t {
  TRMCHAIN_HEADER_MISSING = 1 << 16, // start from BIT(16)
  TRMCHAIN_TRAILER_MISSING = 1 << 17,
  TRMCHAIN_STATUS_NOTZERO = 1 << 18,
  TRMCHAIN_EVENTCNT_MISMATCH = 1 << 19,
  TRMCHAIN_TDCERROR_DETECTED = 1 << 20,
  TRMCHAIN_BUNCHCNT_MISMATCH = 1 << 21,
  TRMCHAIN_MAXDIAGNOSTIC_BIT = 1 << 24 // end before BIT(24), BIT(32)
};

} // namespace diagnostic

} // namespace tof
} // namespace o2

#endif /** O2_TOF_CMPDATAFORMAT **/
