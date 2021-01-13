// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// @file   EntropyEncoderSpec.h
/// @brief  Convert PHOS data to CTF (EncodedBlocks)

#ifndef O2_PHOS_ENTROPYENCODER_SPEC
#define O2_PHOS_ENTROPYENCODER_SPEC

#include "Framework/DataProcessorSpec.h"
#include "Framework/Task.h"
#include <TStopwatch.h>
#include "PHOSReconstruction/CTFCoder.h"

namespace o2
{
namespace phos
{

class EntropyEncoderSpec : public o2::framework::Task
{
 public:
  EntropyEncoderSpec();
  ~EntropyEncoderSpec() override = default;
  void run(o2::framework::ProcessingContext& pc) final;
  void init(o2::framework::InitContext& ic) final;
  void endOfStream(o2::framework::EndOfStreamContext& ec) final;

 private:
  o2::phos::CTFCoder mCTFCoder;
  TStopwatch mTimer;
};

/// create a processor spec
framework::DataProcessorSpec getEntropyEncoderSpec();

} // namespace phos
} // namespace o2

#endif
