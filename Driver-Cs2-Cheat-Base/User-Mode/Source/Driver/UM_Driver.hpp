#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <Driver/Process.hpp>
#include <Globals/Globals.hpp>

namespace Driver
{
    static HANDLE driver_handle;
    namespace IOCTLCodes
    {
        // This is used to initialize the driver.
        constexpr ULONG attach =
            CTL_CODE(FILE_DEVICE_UNKNOWN, 0x696, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);

        // Read Process Memory from a user-mode Application 
        constexpr ULONG read =
            CTL_CODE(FILE_DEVICE_UNKNOWN, 0x697, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);

        // Write Process Memory from a user-mode Application 
        constexpr ULONG write =
            CTL_CODE(FILE_DEVICE_UNKNOWN, 0x698, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
    }

    // This struct is accessible in both user-mode and kernel-mode.
    struct Request {
        HANDLE process_Id;

        PVOID target;
        PVOID buffer;

        SIZE_T size;
        SIZE_T return_size;
    };

    bool attach_to_process(HANDLE driver_handle, const DWORD pid) {
        Request req;
        req.process_Id = reinterpret_cast<HANDLE>(pid);

        return DeviceIoControl(driver_handle, IOCTLCodes::attach, &req, sizeof(req), &req, sizeof(req), nullptr, nullptr);
    }

    template <class type>
    type read_memory(const std::uintptr_t addr) {
        type temp = {};

        Request req;
        req.target = reinterpret_cast<PVOID>(addr);
        req.buffer = &temp;
        req.size = sizeof(type);

        DeviceIoControl(driver_handle, IOCTLCodes::read, &req, sizeof(req), &req, sizeof(req), nullptr, nullptr);

        return temp;
    }

    template <class type>
    void write_memory(const std::uintptr_t addr, const type& value) {
        Request r;
        r.target = reinterpret_cast<PVOID>(addr);
        r.buffer = (PVOID)&value;
        r.size = sizeof(type);

        DeviceIoControl(driver_handle, IOCTLCodes::write, &r, sizeof(r), &r, sizeof(r), nullptr, nullptr);
    }
}
