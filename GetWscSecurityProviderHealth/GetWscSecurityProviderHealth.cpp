// GetWscSecurityProviderHealth.cpp : This source contains 'main' function.
// Copyright: 2021 Mitsutoshi Nakano <bkbin005@rinku.zaq.ne.jp>
// SPDX-License-Identifier: MIT

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <wscapi.h>
#include <winerror.h>

/// <summary>
/// Get WSC Providers from commandline arguments.
/// </summary>
/// <param name="argc">main()'s argc.</param>
/// <param name="argv">main()'s argv</param>
/// <returns>Security Providers.</returns>
static unsigned long
GetProviders(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " {WSC_SECURITY_PROVIDER(hex)}\n";
        exit(ERROR_BAD_ARGUMENTS);
    }
    char *endp;
    return strtoul(argv[1], &endp, 16);
}

/// <summary>
/// Print Windows Security Center's Health.
/// </summary>
/// <param name="providers">WSC Security Providers.</param>
/// <param name="health">Health status.</param>
/// <returns>See https://docs.microsoft.com/en-us/windows/win32/api/wscapi/nf-wscapi-wscgetsecurityproviderhealth .</returns>
static HRESULT
PrintHealth(DWORD providers, WSC_SECURITY_PROVIDER_HEALTH *health)
{
    HRESULT result;
    if ((result = WscGetSecurityProviderHealth((DWORD)providers, health)) != S_OK) {
        std::cerr << "Result: " << result << "\n" << "health: " << *health << "\n";
        return result;
    }
    std::cout << "health: " << *health << "\n";
    return S_OK;
}

/// <summary>
/// Print Windows Security Center's status.
/// </summary>
/// <param name="argc">&gt; 2</param>
/// <param name="argv">argv[1]: WSC_SECURITY_PROVIDER(hex),
/// see https://docs.microsoft.com/en-us/windows/win32/api/wscapi/ne-wscapi-wsc_security_provider .</param>
/// <returns>See https://docs.microsoft.com/en-us/windows/win32/debug/system-error-codes </returns>
int
main(int argc, char *argv[])
{
    unsigned long providers = GetProviders(argc, argv);
    WSC_SECURITY_PROVIDER_HEALTH health;
    if (PrintHealth(providers, &health) != S_OK) {
        return ERROR_BAD_ENVIRONMENT;
    }
    return 0;
}
