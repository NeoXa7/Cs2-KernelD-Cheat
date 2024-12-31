#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <Utils/Console.hpp>
#include <Utils/Overlay.h>

namespace Driver
{
    static HANDLE Handle;
    namespace IOCTL_Codes
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

        constexpr ULONG move_mouse =
            CTL_CODE(FILE_DEVICE_UNKNOWN, 0x699, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
    }

    // This struct is accessible in both user-mode and kernel-mode.
    struct Request {
        HANDLE process_Id;

        PVOID target;
        PVOID buffer;

        SIZE_T size;
        SIZE_T return_size;
    };

    struct MouseRequest {
        ULONG x;
        ULONG y;
    };

    inline VOID SearchForHandle() // Delta or Synapse
    {
        std::string loaded_driver;

        Driver::Handle = INVALID_HANDLE_VALUE;

        // First try (Delta)
        if (Driver::Handle == INVALID_HANDLE_VALUE)
        {
            Driver::Handle = CreateFile(L"\\\\.\\Delta", GENERIC_READ, 0, nullptr, OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL, nullptr);

            if (Driver::Handle != INVALID_HANDLE_VALUE)
            {
                loaded_driver = "Delta Driver : 0x";
                console.SetConsoleTextColor(DARK_CYAN);
                std::cout << std::endl;
                std::cout << " [+] Found and Loaded " << loaded_driver << std::uppercase <<  std::hex << Driver::Handle << '\n';
                std::cout << std::endl;
                console.SetConsoleTextColor(WHITE);
            }
        }

        // Second try (Synapse)
        if (Driver::Handle == INVALID_HANDLE_VALUE)
        {
            Driver::Handle = CreateFile(L"\\\\.\\Synapse", GENERIC_READ, 0, nullptr, OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL, nullptr);

            if (Driver::Handle != INVALID_HANDLE_VALUE)
            {
                loaded_driver = "Synapse Driver : 0x";
                console.SetConsoleTextColor(DARK_CYAN);
                std::cout << std::endl;
                std::cout << " [+] Found and Loaded " << loaded_driver << std::uppercase << std::hex << Driver::Handle << '\n';
                std::cout << std::endl;
                console.SetConsoleTextColor(WHITE);
            }
        }

        // Finnally No Driver was Found (Delta or Synapse)
        if (Driver::Handle == INVALID_HANDLE_VALUE)
        {
            console.SetConsoleTextColor(WHITE);
            std::cout << "Failed to create driver handle.\n";
            std::cout << "Please ensure you have loaded the required driver: Delta.sys or Synapse.sys.\n";
            ShowErrorBox(L"Failed to create driver handle.\nPlease ensure you have loaded the required driver: Delta.sys or Synapse.sys.\n", L"Driver Error");
            std::cin.get();
        }
    }

    inline bool Attach(HANDLE driver_handle, const DWORD pid) {
        Request req;
        req.process_Id = reinterpret_cast<HANDLE>(pid);

        return DeviceIoControl(driver_handle, IOCTL_Codes::attach, &req, sizeof(req), &req, sizeof(req), nullptr, nullptr);
    }

    template <class type>
    type RPM(const std::uintptr_t addr) {
        type temp = {};

        Request req;
        req.target = reinterpret_cast<PVOID>(addr);
        req.buffer = &temp;
        req.size = sizeof(type);

        DeviceIoControl(Handle, IOCTL_Codes::read, &req, sizeof(req), &req, sizeof(req), nullptr, nullptr);

        return temp;
    }

    template <typename type>
    type RPM_Array(const std::uintptr_t address, type* buffer, size_t size) {
        Request req;
        req.target = reinterpret_cast<PVOID>(address);
        req.buffer = buffer;
        req.size = sizeof(type) * size;

        return DeviceIoControl(Handle, IOCTL_Codes::read, &req, sizeof(req), &req, sizeof(req), nullptr, nullptr);
    }


    template <class type>
    bool WPM(const std::uintptr_t addr, const type& value) {
        Request r;
        r.target = reinterpret_cast<PVOID>(addr);
        r.buffer = (PVOID)&value;
        r.size = sizeof(type);

        return DeviceIoControl(Handle, IOCTL_Codes::write, &r, sizeof(r), &r, sizeof(r), nullptr, nullptr);
    }

    inline VOID CheckMemoryProtection(uintptr_t address_to_check)
    {
        MEMORY_BASIC_INFORMATION mbi;
        if (VirtualQuery(reinterpret_cast<void*>(address_to_check), &mbi, sizeof(mbi))) {
            std::cout << "BaseAddress: " << mbi.BaseAddress
                << ", RegionSize: " << mbi.RegionSize
                << ", Protect: " << mbi.Protect << '\n';
        }
        else {
            std::cout << "VirtualQuery failed.\n";
        }
    }
}