#ifndef ENTRY_H
#define ENTRY_H

#include <stdint.h>
#include <vector>
#include <stdexcept>
#include "../option/option.h"

namespace ara
{
    namespace com
    {
        /// @brief Communication message entry
        namespace entry
        {
            /// @brief Message entry type
            enum class EntryType : uint8_t
            {
                Finding = 0x00,      ///!< Service finding
                Offering = 0x01,     ///!< Service start/stop offering
                Subscribing = 0x06,  ///!< Event start/stop subscribing
                Acknowledging = 0x07 ///!< Event subscribe positive/negative acknowledging
            };

            /// @brief Communication message abstract entry
            class Entry
            {
            private:
                EntryType mType;
                std::vector<option::Option*> mFirstOptions;
                std::vector<option::Option*> mSecondOptions;
                uint16_t mServiceId;
                uint16_t mInstanceId;
                uint8_t mMajorVersion;
                uint32_t mTTL;

            protected:
                /// @brief Any service major version
                static const uint8_t cAnyMajorVersion = 0xff;

                /// @brief Constructor
                /// @param type Entry type
                /// @param serviceId Service in interest ID
                /// @param instanceId Service in interest instance ID
                /// @param ttl Entry time to live
                /// @param majorVersion Service in interest major version
                Entry(EntryType type,
                      uint16_t serviceId,
                      uint16_t instanceId,
                      uint32_t ttl,
                      uint8_t majorVersion = cAnyMajorVersion) noexcept;

                /// @brief Validate an option for adding
                /// @param option Option of interest
                /// @returns True if the option is valid; otherwise false
                virtual bool ValidateOption(const option::Option* option) const noexcept;

                /// @brief Indicate whether the entry contains a specific option type or not
                /// @param optionType Option type of interest
                /// @returns True if the entry contains the option; otherwise false
                bool ContainsOption(option::OptionType optionType) const noexcept;

            public:
                virtual ~Entry() noexcept;

                /// @brief Get entry type
                /// @returns Entry type
                EntryType Type() const noexcept;

                /// @brief Get service ID
                /// @returns Entry service in interest ID
                uint16_t ServiceId() const noexcept;

                /// @brief Get instance ID
                /// @returns Entry service in interest instance ID
                uint16_t InstanceId() const noexcept;

                /// @brief Get major version
                /// @returns Entry service in interest major version
                uint8_t MajorVersion() const noexcept;

                /// @brief Get TTL
                /// @returns Entry time to live in seconds
                uint32_t TTL() const noexcept;

                /// @brief Get first (general) options
                /// @returns Exisiting first options
                std::vector<option::Option*> FirstOptions() const noexcept;

                /// @brief Add a first (general) option
                /// @param firstOption First option to be added
                void AddFirstOption(option::Option* firstOption);

                /// @brief Get second (specific) options
                /// @returns Exisiting second options
                std::vector<option::Option*> SecondOptions() const noexcept;

                /// @brief Add a second (specific) option
                /// @param secondOption Second option to be added
                void AddSecondOption(option::Option* secondOption);

                /// @brief Get entity payload
                /// @param optionIndex Index of the last added option
                /// @returns Byte array
                virtual std::vector<uint8_t> Payload(uint8_t &optionIndex);
            };
        }
    }
}

#endif