//
// Copyright (C) 2015 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef UPDATE_ENGINE_COMMON_BOOT_CONTROL_STUB_H_
#define UPDATE_ENGINE_COMMON_BOOT_CONTROL_STUB_H_

#include <memory>
#include <string>

#include "update_engine/common/boot_control_interface.h"
#include "update_engine/common/dynamic_partition_control_interface.h"

namespace chromeos_update_engine {

// An implementation of the BootControlInterface that does nothing,
// typically used when e.g. an underlying HAL implementation cannot be
// loaded or doesn't exist.
//
// You are guaranteed that the implementation of GetNumSlots() method
// always returns 0. This can be used to identify that this
// implementation is in use.
class BootControlStub : public BootControlInterface {
 public:
  BootControlStub();
  ~BootControlStub() = default;

  // BootControlInterface overrides.
  unsigned int GetNumSlots() const override;
  BootControlInterface::Slot GetCurrentSlot() const override;
  bool GetPartitionDevice(const std::string& partition_name,
                          Slot slot,
                          bool not_in_payload,
                          std::string* device,
                          bool* is_dynamic) const override;
  bool GetPartitionDevice(const std::string& partition_name,
                          BootControlInterface::Slot slot,
                          std::string* device) const override;
  std::optional<PartitionDevice> GetPartitionDevice(
      const std::string& partition_name,
      uint32_t slot,
      uint32_t current_slot,
      bool not_in_payload = false) const override;
  bool IsSlotBootable(BootControlInterface::Slot slot) const override;
  bool MarkSlotUnbootable(BootControlInterface::Slot slot) override;
  bool SetActiveBootSlot(BootControlInterface::Slot slot) override;
  Slot GetActiveBootSlot() override { return kInvalidSlot; }
  bool MarkBootSuccessfulAsync(base::Callback<void(bool)> callback) override;
  bool IsSlotMarkedSuccessful(BootControlInterface::Slot slot) const override;
  DynamicPartitionControlInterface* GetDynamicPartitionControl() override;

 private:
  std::unique_ptr<DynamicPartitionControlInterface> dynamic_partition_control_;

  DISALLOW_COPY_AND_ASSIGN(BootControlStub);
};

}  // namespace chromeos_update_engine

#endif  // UPDATE_ENGINE_COMMON_BOOT_CONTROL_STUB_H_
