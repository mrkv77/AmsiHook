# AmsiHook


Simple way to bypass AMSI/ETW without patching

By hooking amsi.dll!AmsiScanBuffer we control whether the original amsi.dll!AmsiScanBuffer gets called

Same thing with ntdll.dll!NtTraceEvent

How to compile: Open in visual studio and compile, then inject the DLL in any .NET app (PowerShell.exe etc)

NOTE: Some AVs have custom AMSI for .NET so this isn't 100% effective.


# Before
![image](https://github.com/user-attachments/assets/065408e8-96b5-4c5f-af03-e97a3b67b1be)

# After
![image](https://github.com/user-attachments/assets/34ebf883-9f71-45f9-948b-943d526488b7)
