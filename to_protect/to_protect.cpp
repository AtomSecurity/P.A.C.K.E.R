#define UNICODE
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

BOOL ListProcessThreads(DWORD dwOwnerPID)
{
    HANDLE hThreadSnap {INVALID_HANDLE_VALUE};
    THREADENTRY32 te32;

    // Take a snapshot of all running threads
    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnap == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }

    // Fill in the size of the structure before using it.
    te32.dwSize = sizeof(THREADENTRY32);

    // Retrieve information about the first thread,
    // and exit if unsuccessful
    if (!Thread32First(hThreadSnap, &te32))
    {
        std::cout << "Failure!" << std::endl;  // Show cause of failure
        CloseHandle(hThreadSnap);     // Must clean up the snapshot object!
        return FALSE;
    }

    // Now walk the thread list of the system,
    // and display information about each thread
    // associated with the specified process
    do
    {
        if(te32.th32OwnerProcessID == dwOwnerPID)
        {
            printf("\n     THREAD ID      = 0x%08lX", te32.th32ThreadID );
            printf("\n     base priority  = %ld", te32.tpBasePri );
            printf("\n     delta priority = %ld", te32.tpDeltaPri );
        }
    } while (Thread32Next(hThreadSnap, &te32));

    printf("\n");

    // Don't forget to clean up the snapshot object.
    CloseHandle(hThreadSnap);
    return TRUE;
}

int main()
{
    std::cout << "Listing process threads...\n";
    Sleep(1000);
    ListProcessThreads(GetCurrentProcessId());
    std::cout << "Press any button to close the program...";
    std::cin.get();
}